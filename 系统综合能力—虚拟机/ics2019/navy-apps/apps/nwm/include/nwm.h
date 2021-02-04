#ifndef __NWM_H__
#define __NWM_H__

#include <stdint.h>
#include <font.h>
#include <stdio.h>
#include <assert.h>

class Window;
class WindowManager;

#define FOREACH_EVENT(_) \
  _("t", timer) \
  _("ku", keyup) \
  _("kd", keydown) \
  _("A-GRAVE", switch_window) \
  _("A-UP", moveup_window) \
  _("A-DOWN", movedown_window) \
  _("A-LEFT", moveleft_window) \
  _("A-RIGHT", moveright_window) \
  _("A-R", appfinder) \

class Window {
protected:
  void draw_raw_px(int x, int y, uint32_t color);
  void draw_raw_ch(Font *font, int x, int y, char ch, uint32_t color);

  // for parsing nwm escape sequences
  struct StateMachine {
    enum State {
      WAIT_ESC = 0, WAIT_BRK, WAIT_X,
      X, Y, WAIT_B1, WAIT_B2, WAIT_B3, WAIT_B4, WAIT_NXT, // payloads
    } state;
    Window *win;
    int x, y;
    uint32_t px;

    void reset();
    bool feed(uint8_t ch);
  } esc_state;

  WindowManager *wm;
  int app_to_nwm[2], nwm_to_app[2]; // file descriptors connecting the window's children

public:
  static const int border_px        = 1;
  static const int title_px         = 16;
  static const uint32_t border_col  = 0xc4c4c4;
  static const uint32_t title_col   = 0x353535;

  char title[64]; // titlebar
  bool has_titlebar;

  int x, y, w, h; // upper-left position (x, y) and window size (w * h)
  int cw, ch, dx, dy; // canvas size (cw * ch) and offset (dx, dy)

  int read_fd, write_fd; // IPC file descriptors. read_fd must be non-blocking
  
  uint32_t *canvas;

  Window(WindowManager *wm, const char *cmd, const char **argv, const char **envp);
  ~Window();

  void move(int x, int y);
  void center();
  void resize(int w, int h);
  
  void draw_px(int x, int y, uint32_t color);
  void draw_ch(Font *font, int x, int y, char ch, uint32_t color);
  void draw();

  void update();
};

class BgImage;
class WindowSwitcher;
class AppFinder;

class WindowManager {
private:
  uint32_t *fb;
  bool *changed;
  uint32_t uptime;
  BgImage *background;
  WindowSwitcher *switcher;
  AppFinder *appfinder;
  bool display_switcher, display_appfinder;

  void set_focus(Window *);
  void draw_px(int x, int y, uint32_t col);
  void draw_window(Window *win);

public:
  int w, h, tw, th;
  Font *font, *title_font;
  Window *focus, *windows[16];

  WindowManager(int width, int height);
  ~WindowManager();
  Window *spawn(const char *path);
  void handle_event(const char *evt);
  void render();
  void mark_dirty(int x, int y);
  #define DECLARE_HANDLER(n, h) void evt_##h(const char *);
  FOREACH_EVENT(DECLARE_HANDLER)
  #undef DECLARE_HANDLER
};

extern FILE *fbdev;

#include <winimpl.h>

#endif
