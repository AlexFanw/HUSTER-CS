#ifndef __NTERM_H__
#define __NTERM_H__

#include <stdint.h>
#include <unistd.h>

class Terminal {
private:
  struct Pattern {
    const char *pattern;
    void (Terminal::*handle)(int *args);
  };
  static Pattern esc_seqs[];

  char *buf, input[256], cooked[256];
  uint8_t *color;
  bool *dirty;
  int inp_len;

  void move_one();
  void backspace();
  size_t write_escape(const char *str, size_t count);
  void scroll_up();


  void esc_move(int *args);
  void esc_movefirst(int *args);
  void esc_moveup(int *args);
  void esc_movedown(int *args);
  void esc_moveleft(int *args);
  void esc_moveright(int *args);
  void esc_save(int *args);
  void esc_restore(int *args);
  void esc_clear(int *args);
  void esc_erase(int *args);
  void esc_setattr1(int *args);
  void esc_setattr2(int *args);
  void esc_setattr3(int *args);
  void esc_rawmode(int *args);
  void esc_cookmode(int *args);

public:
  enum class Mode {
    raw,
    cook,
  } mode;

  int w, h;
  struct Cursor {
    int x, y;
  } cursor, saved;
  uint8_t col_f, col_b;

  Terminal(int width, int height);
  ~Terminal();
  void write(const char *str, size_t count);
  bool is_dirty(int x, int y);

  void putch(int x, int y, char ch);
  char getch(int x, int y);
  uint32_t foreground(int x, int y); // get color
  uint32_t background(int x, int y);

  void clear(); // clear dirty states
  const char *keypress(char ch);
};

#endif
