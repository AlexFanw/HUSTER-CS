#define _GNU_SOURCE
#include <unistd.h>
#include <dlfcn.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

const int disp_w = 400, disp_h = 300;
const char *SHM_FILE = "/dev/shm/navy-fb";
const char *FIFO_FILE = "/tmp/navy-fifo";
const char *NWM_FILE = "/tmp/nwm-fifo";

static FILE *(*real_fopen)(const char *path, const char *mode) = NULL;

int W, H;
#define FPS 30

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static int shm_fd = -1;
static FILE *fifo_r = NULL;
static int fifo_w = -1, nwm_r = -1, nwm_w = -1;
static uint32_t fb[640 * 480];
static uint32_t buf[640 * 480];
static bool fbdev_opened = false;

static void draw_sync() {
  if (fbdev_opened) {
    if (shm_fd < 0) return;
    lseek(shm_fd, 0, SEEK_SET);
    int nread = read(shm_fd, buf, W * H * 4);
    for (int i = 0; i < W * H; i ++) {
      fb[i] = buf[i];
    }
  }
  SDL_UpdateTexture(texture, NULL, fb, W * sizeof(Uint32));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

#define _KEYS(_) \
  _(ESCAPE) _(F1) _(F2) _(F3) _(F4) _(F5) _(F6) _(F7) _(F8) _(F9) _(F10) _(F11) _(F12) \
  _(GRAVE) _(1) _(2) _(3) _(4) _(5) _(6) _(7) _(8) _(9) _(0) _(MINUS) _(EQUALS) _(BACKSPACE) \
  _(TAB) _(Q) _(W) _(E) _(R) _(T) _(Y) _(U) _(I) _(O) _(P) _(LEFTBRACKET) _(RIGHTBRACKET) _(BACKSLASH) \
  _(CAPSLOCK) _(A) _(S) _(D) _(F) _(G) _(H) _(J) _(K) _(L) _(SEMICOLON) _(APOSTROPHE) _(RETURN) \
  _(LSHIFT) _(Z) _(X) _(C) _(V) _(B) _(N) _(M) _(COMMA) _(PERIOD) _(SLASH) _(RSHIFT) \
  _(LCTRL) _(APPLICATION) _(LALT) _(SPACE) _(RALT) _(RCTRL) \
  _(UP) _(DOWN) _(LEFT) _(RIGHT) _(INSERT) _(DELETE) _(HOME) _(END) _(PAGEUP) _(PAGEDOWN)

#define COND(k) \
  if (scancode == SDL_SCANCODE_##k) name = #k;

struct StateMachine {
  enum State {
    WAIT_ESC = 0,
    WAIT_BRK,
    WAIT_X,
    X,
    Y,
    WAIT_B1,
    WAIT_B2,
    WAIT_B3,
    WAIT_B4,
    WAIT_NXT,
  };
  State state;
  int x, y;
  uint32_t px;

  void clear() {
    state = WAIT_ESC;
    x = y = 0; px = 0;
  }

  bool accept(uint8_t ch) {
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
    if (state == Y && ch == 's') { 
      W = x; H = y;
      // TODO: there is a race condition on W
      // but generally it is harmless.
      SDL_SetWindowSize(window, W * 2, H * 2);
      texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
      clear();
      state = WAIT_ESC; return false;
    }
    clear();
    return false;
  }
};

static int nwm_thread(void *args) {
  static char buf[1 << 20];
  StateMachine s;
  s.clear();
  while (1) {
    usleep(1000);
    if (nwm_r == -1) continue;
    int nread = read(nwm_r, buf, sizeof(buf));
    if (nread == -1) continue;

    for (int i = 0; i < nread; i ++) {
      if (s.accept(buf[i])) {
        int idx = s.x + s.y * W;
        fb[idx] = s.px;
      }
    }
  }
}

static int event_thread(void *args) {
  SDL_Event event;
  while (1) {
    SDL_WaitEvent(&event);

    switch (event.type) {
      case SDL_QUIT: exit(0); break;
      case SDL_USEREVENT:
        if (event.user.code == 0) {
          static int tsc = 0;
          tsc ++;
          if (fifo_w != -1) {
            char buf[256];
            sprintf(buf, "t %d\n", tsc * (1000 / FPS));
            write(fifo_w, buf, strlen(buf));
          }
          draw_sync();
        }
        break;
      case SDL_KEYDOWN:
      case SDL_KEYUP: {
        SDL_Keysym k = event.key.keysym;
        int keydown = event.key.type == SDL_KEYDOWN;
        int scancode = k.scancode;

        const char *name = NULL;
        _KEYS(COND);
        if (name) {
          char cmd[128];
          sprintf(cmd, "%s %s\n", keydown ? "kd" : "ku", name);
          write(fifo_w, cmd, strlen(cmd));
        }
        break;
      }
    }
  }
}

static Uint32 timer(Uint32 interval, void *param) {
  SDL_Event event;
  SDL_UserEvent user;
  user.type = SDL_USEREVENT;
  user.code = 0;
  event.type = SDL_USEREVENT;
  event.user = user;
  SDL_PushEvent(&event);
  return interval;
}

static void open_display() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(W * 2, H * 2, 0, &window, &renderer);
  SDL_SetWindowTitle(window, getenv("NWM_APP") ? "Simulated NWM Application" : "Simulated Nanos Application");
  SDL_AddTimer(1000 / FPS, timer, nullptr);
  SDL_CreateThread(event_thread, "event thread", nullptr);
  SDL_CreateThread(nwm_thread, "nwm thread", nullptr);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
  shm_fd = open(SHM_FILE, O_CREAT | O_RDWR, 0666);
  assert(shm_fd >= 0);
  memset(fb, 0x0, W * H * sizeof(uint32_t));
  lseek(shm_fd, 0, SEEK_SET);
  write(shm_fd, fb, W * H * sizeof(uint32_t));
}

static void open_fifo() {
  if (!real_fopen) {
    real_fopen = (FILE*(*)(const char*, const char*))dlsym(RTLD_NEXT, "fopen");
  }

  mkfifo(FIFO_FILE, 0666);
  fifo_w = open(FIFO_FILE, O_RDWR);
  fifo_r = real_fopen(FIFO_FILE, "r");
}

extern "C" FILE *fopen(const char *path, const char *mode);

FILE *fopen(const char *path, const char *mode) {
  char newpath[1024];

  if (!real_fopen) {
    real_fopen = (FILE*(*)(const char*, const char*))dlsym(RTLD_NEXT, "fopen");
  }

  if (strcmp(path, "/dev/fb") == 0) {
    if (shm_fd == -1) {
      W = disp_w;
      H = disp_h;
      open_display();
    }
    assert(shm_fd != -1);
    fbdev_opened = true;
    return real_fopen(SHM_FILE, mode);
  } else if (strcmp(path, "/dev/events") == 0) {
    if (shm_fd == -1) {
      open_display();
    }
    if (fifo_w == -1) {
      open_fifo();
    }
    return fifo_r;
  } else if (strcmp(path, "/proc/dispinfo") == 0) {
    char tmpfile[128];
    strcpy(tmpfile, "/tmp/navy-XXXXXX");
    mktemp(tmpfile);
    FILE *fp = fopen(tmpfile, "w"); assert(fp);
    fprintf(fp, "WIDTH: %d\n", disp_w);
    fprintf(fp, "HEIGHT: %d\n", disp_h);
    fclose(fp);
    return real_fopen(tmpfile, mode);
  } else {
    strcpy(newpath, getenv("NAVY_HOME"));
    strcat(newpath, "/fsimg");
    strcat(newpath, path);
    if (0 == access(newpath, 0)) {
      fprintf(stderr, "Redirecting file open: %s -> %s\n", path, newpath);
    } else {
      strcpy(newpath, path);
    }
  }

  return real_fopen(newpath, mode);
}

struct Init {
  Init() {
    if (getenv("NWM_APP")) {
      open_fifo();
      open_display();
      W = H = 0;
      mkfifo(NWM_FILE, 0666);
      nwm_w = open(NWM_FILE, O_RDWR);
      nwm_r = open(NWM_FILE, O_RDONLY | O_NONBLOCK);
      assert(nwm_w != -1 && nwm_r != -1);

      freopen(FIFO_FILE, "r", stdin);
      freopen(NWM_FILE, "w", stdout);
    }
  }
};

Init init;
