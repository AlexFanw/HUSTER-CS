#include "psg.h"
#include <amdev.h>
#include <klib.h>

static int p = 10;
static int key_state[256];

static int MAP[256] = {
  0, // On/Off
  _KEY_G, // A
  _KEY_H, // B
  _KEY_T, // SELECT
  _KEY_Y, // START
  _KEY_W,
  _KEY_S,
  _KEY_A, 
  _KEY_D, 
  255,
};

byte psg_io_read(word address) {
  // Joystick 1
  if (address == 0x4016) {
    if (p++ < 9) {
      return key_state[MAP[p]];
    }
  }
  return 0;
}

void psg_io_write(word address, byte data) {
  static byte prev_write;
  if (address == 0x4016) {
    if ((data & 1) == 0 && prev_write == 1) {
      // strobe
      p = 0;
    }
  }
  prev_write = data & 1;
}

void psg_detect_key() {
  int key = read_key();
  for (; key != _KEY_NONE; key = read_key()) {
    int down = (key & 0x8000) != 0;
    int code = key & ~0x8000;
    key_state[code] = down;
  }
}

void psg_init() {
  key_state[0] = 1;
}
