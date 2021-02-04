#include <stdio.h>
#include <string.h>
#include <font.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <nterm.h>
#include <ndl.h>

const char *nterm_proc = "/bin/dash";
const char *font_fname = "/share/fonts/Courier-7.bdf";

int columns = 48, lines = 16; // terminal geom
int read_fd, write_fd, nterm_to_app[2], app_to_nterm[2]; // file desc
Terminal *term;

static void draw_ch(Font *font, int x, int y, char ch, uint32_t fg, uint32_t bg);
static void poll_terminal();
static char handle_key(const char *buf);
static void fork_child();

int main() {
  Font *font = new Font(font_fname);

  // setup display
  int win_w = font->w * columns;
  int win_h = font->h * lines;

  NDL_OpenDisplay(win_w, win_h);

  term = new Terminal(columns, lines);

  // fork the child process and setup fds
  fork_child();

  int elapse = -1, ntick = 0, last_k = 0;

  while (1) {
    poll_terminal();
    char buf[256], *p = buf, ch;
    while ((ch = getc(stdin)) != -1) {
      *p ++ = ch;
      if (ch == '\n') break;
    }
    *p = '\0';

    if (buf[0] == 'k') {
      last_k = elapse;
      const char *res = term->keypress(handle_key(buf + 1));
      if (res) {
        write(write_fd, res, strlen(res));
      }
    }

    if (buf[0] == 't') {
      int now;
      sscanf(buf + 2, "%d", &now);
      for (int i = 0; i < columns; i ++)
        for (int j = 0; j < lines; j ++)
          if (term->is_dirty(i, j)) {
            draw_ch(font, i * font->w, j * font->h, term->getch(i, j), term->foreground(i, j), term->background(i, j));
          }
      term->clear();

      if (now - last_k < 1000 || (now - last_k) % 1000 <= 500) {
        draw_ch(font, term->cursor.x * font->w, term->cursor.y * font->h, ' ', 0x0, 0x0);
      }

      NDL_Render();
      elapse = now;
    }
  }

  assert(0);
}

static void draw_ch(Font *font, int x, int y, char ch, uint32_t fg, uint32_t bg) {
  uint32_t *bm = font->font[ch];
  if (!bm) return;
  for (int j = 0; j < font->h; j ++) {
    uint32_t pixels[font->w];
    for (int i = 0; i < font->w; i ++) {
      pixels[i] = ((bm && ((bm[j] >> i) & 1))) ? fg : bg;
    }
    NDL_DrawRect(pixels, x, y + j, font->w, 1);
  }
}

static void poll_terminal() {
  static char buf[4096];
  int nread = read(read_fd, buf, sizeof(buf));
  if (nread > 0) {
    term->write(buf, nread);
  }
}

static struct {
  const char *name;
  char noshift, shift;
} SHIFT[] = {
  {"ESCAPE",       '\033', '\033'},
  {"SPACE",        ' ' , ' '},
  {"RETURN",       '\n', '\n'},
  {"BACKSPACE",    '\b', '\b'},
  {"1",            '1',  '!'},
  {"2",            '2',  '@'},
  {"3",            '3',  '#'},
  {"4",            '4',  '$'},
  {"5",            '5',  '%'},
  {"6",            '6',  '^'},
  {"7",            '7',  '&'},
  {"8",            '8',  '*'},
  {"9",            '9',  '('},
  {"0",            '0',  ')'},
  {"GRAVE",        '`',  '~'},
  {"MINUS",        '-',  '_'},
  {"EQUALS",       '=',  '+'},
  {"SEMICOLON",    ';',  ':'},
  {"APOSTROPHE",   '\'', '"'},
  {"LEFTBRACKET",  '[',  '{'},
  {"RIGHTBRACKET", ']',  '}'},
  {"BACKSLASH",    '\\', '|'},
  {"COMMA",        ',',  '<'},
  {"PERIOD",       '.',  '>'},
  {"SLASH",        '/',  '?'},
};

static char handle_key(const char *buf) {
  char key[32];
  static int shift = 0;
  sscanf(buf + 2, "%s", key);

  if (strcmp(key, "LSHIFT") == 0 || strcmp(key, "RSHIFT") == 0)  { shift ^= 1; return '\0'; }

  if (buf[0] == 'd') {
    if (key[0] >= 'A' && key[0] <= 'Z' && key[1] == '\0') {
      if (shift) return key[0];
      else return key[0] - 'A' + 'a';
    }
    for (auto item: SHIFT) {
      if (strcmp(item.name, key) == 0) {
        if (shift) return item.shift;
        else return item.noshift;
      }
    }
  }
  return '\0';
}

static void fork_child() {
  const char *argv[] = {
    nterm_proc,
    NULL,
  };
  char env_lines[32]; sprintf(env_lines, "LINES=%d", lines);
  char env_columns[32]; sprintf(env_columns, "COLUMNS=%d", columns);
  const char *envp[] = {
    env_lines,
    env_columns,
    "TERM=ansi",
    NULL
  };

  assert(0 == pipe(nterm_to_app));
  assert(0 == pipe(app_to_nterm));
  read_fd = app_to_nterm[0];
  write_fd = nterm_to_app[1];

  int flags = fcntl(read_fd, F_GETFL, 0);
  fcntl(read_fd, F_SETFL, flags | O_NONBLOCK);

  int stdin_fd = dup(0), stdout_fd = dup(1), stderr_fd = dup(2);

  dup2(nterm_to_app[0], 0);
  dup2(app_to_nterm[1], 1);
  dup2(app_to_nterm[1], 2);

  pid_t p = vfork();
  if (p == 0) {
    execve(argv[0], (char**)argv, (char**)envp);
    assert(0);
  } else {
    dup2(stdin_fd, 0); dup2(stdout_fd, 1); dup2(stderr_fd, 2);
    close(stdin_fd); close(stdout_fd); close(stderr_fd);
  }
}
