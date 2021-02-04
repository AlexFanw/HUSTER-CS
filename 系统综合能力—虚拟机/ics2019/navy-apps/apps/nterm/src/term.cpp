#include <nterm.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define EMPTY ' '

enum Color {
  BLACK = 0, 
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
};

static int colors[] = {
  [Color::BLACK  ] = 0x323232,
  [Color::RED    ] = 0xe41b17,
  [Color::GREEN  ] = 0x4aa02c,
  [Color::YELLOW ] = 0xe8a317,
  [Color::BLUE   ] = 0x0041c2,
  [Color::MAGENTA] = 0xe3319d,
  [Color::CYAN   ] = 0x77bfc7,
  [Color::WHITE  ] = 0xf0f0f0,
};

Terminal::Pattern Terminal::esc_seqs[] = {
  {"\033[1t", &Terminal::esc_cookmode}, // added by us
  {"\033[2t", &Terminal::esc_rawmode}, // added by us

  {"\033[s", &Terminal::esc_save},
  {"\033[u", &Terminal::esc_restore},
  {"\033[J", &Terminal::esc_clear},
  {"\033[2J", &Terminal::esc_clear},
  {"\033[K", &Terminal::esc_erase},
  {"\033[f", &Terminal::esc_movefirst},
  {"\033[H", &Terminal::esc_movefirst},
  {"\033[#;#f", &Terminal::esc_move},
  {"\033[#;#H", &Terminal::esc_move},
  {"\033[#A", &Terminal::esc_moveup},
  {"\033[#B", &Terminal::esc_movedown},
  {"\033[#C", &Terminal::esc_moveright},
  {"\033[#D", &Terminal::esc_moveleft},
  {"\033[#m", &Terminal::esc_setattr1},
  {"\033[#;#m", &Terminal::esc_setattr2},
  {"\033[#;#;#m", &Terminal::esc_setattr3},
};

static inline int min(int x, int y) { return x < y ? x : y; }
static inline int max(int x, int y) { return x > y ? x : y; }

void Terminal::esc_move(int *args) {
  cursor = { .x = args[1] - 1, .y = args[0] - 1 };
}

void Terminal::esc_movefirst(int *args) {
  cursor = { .x = 0, .y = 0 };
}

void Terminal::esc_moveup(int *args) {
  cursor.y -= args[0];
}

void Terminal::esc_movedown(int *args) {
  cursor.y += args[0];
}

void Terminal::esc_moveleft(int *args) {
  cursor.x -= args[0];
}

void Terminal::esc_moveright(int *args) {
  cursor.x += args[0];
}

void Terminal::esc_save(int *args) {
  saved = cursor;
}

void Terminal::esc_restore(int *args) {
  cursor = saved;
}

void Terminal::esc_clear(int *args) {
  for (int i = 0; i < w; i ++)
    for (int j = 0; j < h; j ++) {
      putch(i, j, EMPTY);
    }
  cursor = {.x = 0, .y = 0};
}

void Terminal::esc_setattr1(int *args) {
  int attr = args[0];
  switch (attr) {
    case 0:  col_f = Color::BLACK; col_b = Color::WHITE; break; // reset
    case 30: col_f = Color::BLACK; break;
    case 31: col_f = Color::RED; break;
    case 32: col_f = Color::GREEN; break;
    case 33: col_f = Color::YELLOW; break;
    case 34: col_f = Color::BLUE; break;
    case 35: col_f = Color::MAGENTA; break;
    case 36: col_f = Color::CYAN; break;
    case 37: col_f = Color::WHITE; break;
    case 40: col_b = Color::BLACK; break;
    case 41: col_b = Color::RED; break;
    case 42: col_b = Color::GREEN; break;
    case 43: col_b = Color::YELLOW; break;
    case 44: col_b = Color::BLUE; break;
    case 45: col_b = Color::MAGENTA; break;
    case 46: col_b = Color::CYAN; break;
    case 47: col_b = Color::WHITE; break;
  }
}

void Terminal::esc_setattr2(int *args) {
  esc_setattr1(&args[0]);
  esc_setattr1(&args[1]);
}

void Terminal::esc_setattr3(int *args) {
  esc_setattr1(&args[0]);
  esc_setattr1(&args[1]);
  esc_setattr1(&args[2]);
}

void Terminal::esc_erase(int *args) {
  for (int i = cursor.x; i < w; i ++) {
    putch(i, cursor.y, EMPTY);
  }
}

void Terminal::esc_rawmode(int *args) {
  mode = Mode::raw;
}

void Terminal::esc_cookmode(int *args) {
  mode = Mode::cook;
}

Terminal::Terminal(int width, int height) {
  w = width; h = height;
  mode = Mode::cook;
  cursor = {.x = 0, .y = 0};
  saved = cursor;
  buf = new char[w * h];
  color = new uint8_t[w * h];
  dirty = new bool[w * h];
  inp_len = 0;
  col_f = Color::BLACK;
  col_b = Color::WHITE;

  for (int x = 0; x < w; x ++) {
    for (int y = 0; y < h; y ++) {
      putch(x, y, EMPTY);
    }
  }
}

Terminal::~Terminal() {
  delete [] buf;
  delete [] color;
  delete [] dirty;
}

void Terminal::backspace() {
  cursor.x --;
  if (cursor.x < 0) {
    cursor.x = w - 1;
    cursor.y --;
    if (cursor.y < 0) cursor.x = cursor.y = 0;
  }
  buf[cursor.y * w + cursor.x] = EMPTY;
  dirty[cursor.y * w + cursor.x] = true;
}

void Terminal::move_one() {
  auto &c = cursor;
  int ret = c.y * w + c.x;
  c.x ++;
  if (c.x >= w) {
    c.x = 0;
    c.y ++;
  }
  if (c.y >= h) {
    scroll_up();
    ret -= w;
    c.y --;
  }
}

void Terminal::scroll_up() {
  memmove(buf, buf + w, w * (h - 1));
  memmove(color, color + w, w * (h - 1));
  for (int i = 0; i < w; i ++) {
    putch(i, h - 1, EMPTY);
  }
  for (int i = 0; i < w * h; i ++) {
    dirty[i] = true;
  }
}

size_t Terminal::write_escape(const char *str, size_t count) {
  for (auto &p: esc_seqs) {
    bool match = false;
    int len = 0, args[4], narg = 0;

    for (const char *cur = p.pattern, *s = str; ; cur ++) {
      if (*cur == '\0') { // found a match.
        match = true; break;
      }
      if (*cur != '#') {
        if (*s != *cur) break;
        s ++;
        len ++;
      } else {
        int data = 0;
        for (; *s >= '0' && *s <= '9' && s - str < count; s ++, len ++) {
          data = data * 10 + *s - '0';
        }
        args[narg ++] = data;
      }
    }

    if (match) {
      (this->*p.handle)(args);
      cursor.x = max(min(cursor.x, w - 1), 0);
      cursor.y = max(min(cursor.y, h - 1), 0);
      return len;
    }
  }
  return 1;
}

void Terminal::write(const char *str, size_t count) {
  for (size_t i = 0; i != count && str[i]; ) {
    char ch = str[i];
    if (ch == '\033') {
        i += write_escape(&str[i], count - i);
    } else {
      switch (ch) {
        case '\x07':
          break;
        case '\n':
          cursor.x = 0;
          cursor.y ++;
          if (cursor.y >= h) {
            scroll_up();
            cursor.y --;
          }
          break;
        case '\t':
          // TODO: implement it.
          break;
        case '\r':
          cursor.x = 0;
          break;
        default:
          putch(cursor.x, cursor.y, ch);
          move_one();
      }
      i ++;
    }
  }
}

const char *Terminal::keypress(char ch) {
  if (ch == '\0') return nullptr;
  if (mode == Mode::raw) {
    input[0] = ch;
    input[1] = '\0';
    return input;
  } else if (mode == Mode::cook) {
    const char *ret = nullptr;
    switch (ch) {
      case '\033':
        break;
      case '\n':
        strcpy(cooked, input);
        strcat(cooked, "\n");
        ret = cooked;
        write("\n", 1);
        inp_len = 0;
        break;
      case '\b':
        if (inp_len > 0) {
          inp_len --;
          backspace();
        }
        break;
      default:
        if (inp_len + 1 < sizeof(input)) {
          input[inp_len ++] = ch;
          write(&ch, 1);
        }
    }
    input[inp_len] = '\0';
    return ret;
  }
}

char Terminal::getch(int x, int y) {
  return buf[x + y * w];
}

void Terminal::putch(int x, int y, char ch) {
  buf[x + y * w] = ch;
  color[x + y * w] = (col_f << 4) | col_b;
  dirty[x + y * w] = ch;
}

uint32_t Terminal::foreground(int x, int y) {
  return colors[color[x + y * w] >> 4];
}

uint32_t Terminal::background(int x, int y) {
  return colors[color[x + y * w] & 0xf];
}

bool Terminal::is_dirty(int x, int y) {
  return dirty[x + y * w];
}

void Terminal::clear() {
  for (int i = 0; i < w * h; i ++) dirty[i] = false;
  dirty[cursor.x + cursor.y * w] = true;
}

