#ifndef __NDL_H__
#define __NDL_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _KEYS(_) \
  _(ESCAPE) _(F1) _(F2) _(F3) _(F4) _(F5) _(F6) _(F7) _(F8) _(F9) _(F10) _(F11) _(F12) \
  _(GRAVE) _(1) _(2) _(3) _(4) _(5) _(6) _(7) _(8) _(9) _(0) _(MINUS) _(EQUALS) _(BACKSPACE) \
  _(TAB) _(Q) _(W) _(E) _(R) _(T) _(Y) _(U) _(I) _(O) _(P) _(LEFTBRACKET) _(RIGHTBRACKET) _(BACKSLASH) \
  _(CAPSLOCK) _(A) _(S) _(D) _(F) _(G) _(H) _(J) _(K) _(L) _(SEMICOLON) _(APOSTROPHE) _(RETURN) \
  _(LSHIFT) _(Z) _(X) _(C) _(V) _(B) _(N) _(M) _(COMMA) _(PERIOD) _(SLASH) _(RSHIFT) \
  _(LCTRL) _(APPLICATION) _(LALT) _(SPACE) _(RALT) _(RCTRL) \
  _(UP) _(DOWN) _(LEFT) _(RIGHT) _(INSERT) _(DELETE) _(HOME) _(END) _(PAGEUP) _(PAGEDOWN)

#define enumdef(k) NDL_SCANCODE_##k,

enum NDL_ScanCode {
  NDL_SCANCODE_NONE = 0,
  _KEYS(enumdef)
};

enum NDL_EventType {
  NDL_EVENT_KEYDOWN,
  NDL_EVENT_KEYUP,
  NDL_EVENT_TIMER,
};

typedef struct NDL_Event {
  enum NDL_EventType type; 
  int32_t data;
} NDL_Event;

typedef struct NDL_Bitmap {
  int w, h;
  uint32_t *pixels;
} NDL_Bitmap;

int NDL_OpenDisplay(int w, int h);
int NDL_CloseDisplay();
int NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h);
int NDL_Render();
int NDL_WaitEvent(NDL_Event *event);
int NDL_LoadBitmap(NDL_Bitmap *bmp, const char *filename);
int NDL_ReleaseBitmap(NDL_Bitmap *bmp);

#ifdef __cplusplus
}
#endif

#endif
