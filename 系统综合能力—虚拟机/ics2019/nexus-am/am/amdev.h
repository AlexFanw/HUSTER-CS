#ifndef __AMDEV_H__
#define __AMDEV_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// =========================== AM Devices ============================

#define _DEV_PERFCNT 0x0000ac01 // AM Virtual Performance Counter 
#define _DEV_INPUT   0x0000ac02 // AM Virtual Input Device
#define _DEV_TIMER   0x0000ac03 // AM Virtual Timer
#define _DEV_VIDEO   0x0000ac04 // AM Virtual Video Controller
#define _DEV_SERIAL  0x0000ac05 // AM Virtual Serial
#define _DEV_PCICONF 0x00000080 // PCI Configuration Space

#define _AM_DEVREG(dev, reg, id, ...) \
  enum { _DEVREG_##dev##_##reg = id }; \
  typedef struct { __VA_ARGS__; } __attribute__((packed)) \
    _DEV_##dev##_##reg##_t;

// ================= Device Register Specifications ==================

_AM_DEVREG(INPUT,  KBD,    1, int keydown, keycode);
_AM_DEVREG(TIMER,  UPTIME, 1, uint32_t hi, lo);
_AM_DEVREG(TIMER,  DATE,   2, int year, month, day, hour, minute, second);
_AM_DEVREG(VIDEO,  INFO,   1, int width, height);
_AM_DEVREG(VIDEO,  FBCTL,  2, int x, y; uint32_t *pixels; int w, h, sync);
_AM_DEVREG(SERIAL, RECV,   1, uint8_t data);
_AM_DEVREG(SERIAL, SEND,   2, uint8_t data);
_AM_DEVREG(SERIAL, STAT,   3, uint8_t data);
_AM_DEVREG(SERIAL, CTRL,   4, uint8_t data);
#define _DEVREG_PCICONF(bus, slot, func, offset) \
  ((uint32_t)(   1) << 31) | ((uint32_t)( bus) << 16) | \
  ((uint32_t)(slot) << 11) | ((uint32_t)(func) <<  8) | (offset)

// ============================ Key Codes ============================

#define _KEYS(_) \
  _(ESCAPE) \
  _(F1) _(F2) _(F3) _(F4) _(F5) _(F6) _(F7) _(F8) _(F9) _(F10) _(F11) _(F12) \
  _(GRAVE) _(1) _(2) _(3) _(4) _(5) _(6) _(7) _(8) _(9) _(0) \
  _(MINUS) _(EQUALS) _(BACKSPACE) \
  _(TAB) _(Q) _(W) _(E) _(R) _(T) _(Y) _(U) _(I) _(O) _(P) \
  _(LEFTBRACKET) _(RIGHTBRACKET) _(BACKSLASH) \
  _(CAPSLOCK) _(A) _(S) _(D) _(F) _(G) _(H) _(J) _(K) _(L) \
  _(SEMICOLON) _(APOSTROPHE) _(RETURN) \
  _(LSHIFT) _(Z) _(X) _(C) _(V) _(B) _(N) _(M) \
  _(COMMA) _(PERIOD) _(SLASH) _(RSHIFT) \
  _(LCTRL) _(APPLICATION) _(LALT) _(SPACE) _(RALT) _(RCTRL) \
  _(UP) _(DOWN) _(LEFT) _(RIGHT) _(INSERT) _(DELETE) \
  _(HOME) _(END) _(PAGEUP) _(PAGEDOWN)
#define _KEY_NAME(k) _KEY_##k,
enum {
  _KEY_NONE = 0,
  _KEYS(_KEY_NAME)
};

#ifdef __cplusplus
}
#endif

#endif
