#ifndef __WINIMPL_H__
#define __WINIMPL_H__

#include <nwm.h>
#include <string.h>

class BgImage: public Window {
public:
  BgImage(WindowManager *wm, int width, int height): Window(wm, nullptr, nullptr, nullptr) {
    move(0, 0);
    resize(width, height);

    for (int x = 0; x < w; x ++)
      for (int y = 0; y < h; y ++) {
        uint8_t r = 255 - x * x * 256 / w / w;
        uint8_t g = 255 - y * y * 256 / h / h;
        uint8_t b = 255 - (x * x + y * y) * 256 / (w + h) / (w + h);

        uint32_t col = (r << 16) | (g << 8) | b;
        draw_px(x, y, col);
      }
  }
};

class WindowSwitcher: public Window {
  bool visible;
  int last_n;

  void project(Window *win, int basex, int basey, int w, int h) {
    int w1, h1;
    if (win->h * w <= h * win->w) {
      w1 = w;
      h1 = win->h * w / win->w;
    } else {
      w1 = win->w * h / win->h;
      h1 = h;
    }
    for (int x = 0; x < w1; x ++)
      for (int y = 0; y < h1; y ++) {
        uint32_t col = win->canvas[
            ( y * win->h / h1 ) * win->w + 
            ( x * win->w / w1 )
          ];
        if (col & 0xff000000) {
          col = border_col;
        }
        draw_px(basex + x + (w - w1) / 2, basey + y + (h - h1) / 2, col);
      }
  }

  static const int preview_px = 72, preview_pad = 5, preview_border = 10;

public:
  WindowSwitcher(WindowManager *wm, int width, int height):
    Window(wm, nullptr, nullptr, nullptr) {
    resize(width, preview_px + 2 * preview_pad);
    visible = true;
    last_n = -1;
  }

  void sync() {
    if (visible) {
      int n = 0;
      for (Window *win: wm->windows) if (win) n ++; // number of windows

      int w1 = n * (2 * preview_pad + preview_px) + 2 * preview_border, base = (w - w1) / 2;

      if (n != last_n) {
        last_n = n;
        for (int i = 0; i < base; i ++)
          for (int j = 0; j < h; j ++) {
            draw_px(i, j, 0xff000000);
            draw_px(w - i - 1, j, 0xff000000);
          }
      }

      for (int i = 0; i < w1; i ++)
        for (int j = 0; j < h; j ++)
          draw_px(base + i, j, 0xc4c4c4);

      draw_px(base, 0, 0xff000000);
      draw_px(base + w1 - 1, 0, 0xff000000);
      draw_px(base, h - 1, 0xff000000);
      draw_px(base + w1 - 1, h - 1, 0xff000000);

      int x = preview_pad + (w - w1) / 2 + preview_border;

      for (Window *win: wm->windows) {
        if (win == wm->focus) {
          for (int i = 0; i < preview_px + 4; i ++)
            for (int j = 0; j < preview_px + 4; j ++)
              if ((i == 0 || i == preview_px + 3) &&
                  (j == 0 || j == preview_px + 3)) {
              } else {
                draw_px(x + i - 2, preview_pad + j - 2, 0x81bef7);
              }
        }
        if (win) {
          project(win, x, preview_pad, preview_px, preview_px);
          x += preview_px + 2 * preview_pad;
        }
      }
    }
    center();
  }
};


static const char *names[] = {
  "Terminal",
  "LiteNES",
  "Pal",
};

class AppFinder: public Window {
  static const int item_size = 38, item_pad = 6, icon_size = 32;
  int n, cur, cutline;

public:
  // TODO: read icons and commands from a configuration file.
  AppFinder(WindowManager *wm): Window(wm, nullptr, nullptr, nullptr) {
    n = 3;
    cur = 0;

    resize(item_size * n + item_pad * (n + 1), item_size + item_pad);
    move((wm->w - w) / 2, wm->h - h + 1);

    cutline = h * 1 / 2;
    for (int x = 0; x < w; x ++) {
      for (int y = 0; y < h; y ++) {
        if (y >= cutline) {
          draw_px(x, y, border_col);
        } else {
          draw_px(x, y, 0xff000000);
        }
      }
    }
    sync();
  }

  void draw_item(int idx, int x, int y) {
    Font *font = wm->font;
    if (idx == cur) {
      for (int i = 0; i < item_size; i ++) {
        for (int j = 0; j < item_size; j ++) {
          draw_px(x + i, y + j, 0xc0c0f0);
        }
      }
    } else {
      for (int i = 0; i < item_size; i ++)
        for (int j = 0; j < item_size; j ++) {
          if (y + j >= cutline) {
            draw_px(x + i, y + j, border_col);
          } else {
            draw_px(x + i, y + j, 0xff000000);
          }
        }
    }

    int icon_dx = (item_size - icon_size) / 2;
    int icon_dy = icon_dx;

    for (int i = 0; i < icon_size; i ++)
      for (int j = 0; j < icon_size; j ++) {
        draw_px(x + icon_dx + i, y + icon_dy + j, 0xf0f0f0);
      }

    int dx = 0, dy = 0;
    for (const char *p = names[idx]; *p; p ++) {
      if (dx + font->w >= icon_size) {
        dx = 0; dy += font->h;
      }
      if (dy + font->h >= icon_size) break;
      draw_ch(font, x + icon_dx + dx, y + icon_dy + dy, *p, 0x0);
      dx += font->w;
    }

  }

  void sync() {
    int dx = item_pad;
    int dy = item_pad;
    for (int i = 0; i < n; i ++) {
      draw_item(i, dx, dy);
      dx += item_size + item_pad;
    }
  }

  void prev() {
    cur = (cur - 1 + n) % n;
    sync();
  }

  void next() {
    cur = (cur + 1) % n;
    sync();
  }

  const char *getcmd() {
    switch (cur) {
      case 0: return "../nterm/build/nterm-native";
      case 1: return "../litenes/build/litenes-native";
      case 2: return "../pal/build/pal-native";
    }
    assert(0);
  }
};

#endif
