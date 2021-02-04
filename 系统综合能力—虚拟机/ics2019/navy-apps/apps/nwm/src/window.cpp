#include <nwm.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void Window::StateMachine::reset() {
  state = WAIT_ESC;
  x = y = 0; px = 0;
}

bool Window::StateMachine::feed(uint8_t ch) {
  // frequent branches
  if (state == WAIT_B1) { px |= ch; state = WAIT_B2; return false; }
  if (state == WAIT_B2) { px |= ch << 8; state = WAIT_B3; return false; }
  if (state == WAIT_B3) { px |= ch << 16; state = WAIT_B4; return false; }
  if (state == WAIT_B4) { state = WAIT_NXT; return true; }
  if (state == WAIT_NXT && ch == ';') { px = 0; state = WAIT_B1; x ++; return false; }

  if (state == WAIT_ESC && ch == '\033') { state = WAIT_BRK; return false; }
  if (state == WAIT_BRK && ch == '[') { state = WAIT_X; return false; }
  if (state == WAIT_X && ch == 'X') { state = X; return false; }
  if (state == X && ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; return false; }
  if (state == X && ch == ';') { state = Y; return false; }
  if (state == Y && ch >= '0' && ch <= '9') { y = y * 10 + ch - '0'; return false; }
  if (state == Y && ch == ';') { state = WAIT_B1; return false; }
  if (state == Y && ch == 's') { assert(win); win->resize(x, y); state = WAIT_ESC; return false; }
  reset();
  return false;
}

void Window::draw_raw_px(int x, int y, uint32_t color) {
  if (x >= 0 && y >= 0 && x < w && y < h) {
    wm->mark_dirty(this->x + x, this->y + y);
    canvas[x + y * w] = color;
  }
}

void Window::draw_px(int x, int y, uint32_t color) {
  draw_raw_px(x + dx, y + dy, color);
}

void Window::draw_ch(Font *font, int x, int y, char ch, uint32_t color) {
  uint32_t *bm = font->font[ch];
  if (!bm) return;
  for (int j = 0; j < font->h; j ++)
    for (int i = 0; i < font->w; i ++)
      if ((bm && ((bm[j] >> i) & 1))) {
        draw_px(x + i, y + j, color);
      }
}

void Window::draw_raw_ch(Font *font, int x, int y, char ch, uint32_t color) {
  uint32_t *bm = font->font[ch];
  if (!bm) return;
  for (int j = 0; j < font->h; j ++)
    for (int i = 0; i < font->w; i ++)
      if ((bm && ((bm[j] >> i) & 1))) {
        draw_raw_px(x + i, y + j, color);
      }
}

void Window::draw() {
  for (int i = 0; i < w; i ++)
    for (int j = 0; j < h; j ++) {
      wm->mark_dirty(this->x + i, this->y + j);
    }
}

Window::Window(WindowManager *wm, const char *cmd, const char **argv, const char **envp) {
  this->wm = wm;
  x = y = w = h = 0;
  canvas = nullptr;
  esc_state.reset();
  esc_state.win = this;

  if (cmd) {
    has_titlebar = true;
    const char *title = cmd;
    for (const char *p = cmd; *p; p ++) {
      if (*p == '/') title = p + 1;
    }
    strcpy(this->title, title);

    // create child process
    assert(0 == pipe(nwm_to_app));
    assert(0 == pipe(app_to_nwm));

    read_fd = app_to_nwm[0];
    write_fd = nwm_to_app[1];

    int flags = fcntl(read_fd, F_GETFL, 0);
    fcntl(read_fd, F_SETFL, flags | O_NONBLOCK);

    int stdin_fd = dup(0);
    int stdout_fd = dup(1);
    int stderr_fd = dup(2);

    dup2(nwm_to_app[0], 0);
    dup2(app_to_nwm[1], 1);
    dup2(app_to_nwm[1], 2);

    pid_t p = vfork();
    if (p == 0) { // child
      execve(argv[0], (char**)argv, (char**)envp);
      assert(0);
    } else {
      dup2(stdin_fd, 0);
      dup2(stdout_fd, 1);
      dup2(stderr_fd, 2);
      close(stdin_fd);
      close(stdout_fd);
      close(stderr_fd);
    }
  } else {
    // an internal window (without title bar)
    has_titlebar = false;
    read_fd = write_fd = -1;
  }
}

void Window::move(int x, int y) {
  draw();
  this->x = x;
  this->y = y;
  draw();
}

void Window::center() {
  move((wm->w - w) / 2, (wm->h - h) / 2);
}

void Window::resize(int width, int height) {
  draw();

  if (has_titlebar) {
    this->w = width + border_px * 2;
    this->h = height + border_px * 2 + title_px;
    this->dx = border_px;
    this->dy = title_px + border_px;
  } else {
    this->w = width;
    this->h = height;
    this->dx = 0;
    this->dy = 0;
  }
  this->cw = width; // canvas w/h
  this->ch = height;
  if (canvas) delete [] canvas;
  canvas = new uint32_t[w * h];

  for (int i = 0; i < w; i ++)
    for (int j = 0; j < h; j ++)
      draw_raw_px(i, j, border_col);

  if (has_titlebar) {
    for (int i = 0; i < w; i ++) {
      for (int j = 0; j < title_px; j ++) {
        int cx = 100 - 100 * i / w;
        int cy = 100 - 100 * j / title_px;
        uint8_t c = (cx + cy) / 10 + 200;
        draw_raw_px(i, j, (c << 16) | (c << 8) | c);
      }
    }

    int x = (w - strlen(title) * wm->title_font->w) / 2;
    int y = 2;
    for (const char *p = title; *p; p ++) {
      draw_raw_ch(wm->title_font, x, y, *p, title_col);
      x += wm->title_font->w;
    }

    draw_raw_px(0, 0, 0xff000000);
    draw_raw_px(w - 1, 0, 0xff000000);
  }

  draw();
}

Window::~Window() {
  delete [] canvas;
  if (read_fd != -1) {
     // close pipes
    for (int i = 0; i < 2; i ++) {
      close(nwm_to_app[i]);
      close(app_to_nwm[i]);
    }
  }
}

void Window::update() {
  if (read_fd != -1) {
    char buf[64 * 1024];
    do {
      int nread = read(read_fd, buf, sizeof(buf)); // this a non-blocking read
      if (nread == -1) break;
      for (int i = 0; i < nread; i ++) {
        if (esc_state.feed(buf[i])) {
          draw_px(esc_state.x, esc_state.y, esc_state.px);
        }
      }
    } while (1);
  }
}

