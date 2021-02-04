#include <am.h>
#include <amdev.h>
#include <SDL2/SDL.h>

#define KEYDOWN_MASK 0x8000

#define KEY_QUEUE_LEN 1024
static int key_queue[KEY_QUEUE_LEN] = {};
static int key_f = 0, key_r = 0;
static SDL_mutex *key_queue_lock = NULL;

#define XX(k) [SDL_SCANCODE_##k] = _KEY_##k,
static int keymap[256] = {
  _KEYS(XX)
};

static int event_thread(void *args) {
  SDL_Event event;
  while (1) {
    SDL_WaitEvent(&event);
    switch (event.type) {
      case SDL_QUIT: _exit(0); break;
      case SDL_KEYDOWN: 
      case SDL_KEYUP:
        {
          SDL_Keysym k = event.key.keysym;
          int keydown = event.key.type == SDL_KEYDOWN;
          int scancode = k.scancode;
          if (keymap[scancode] != 0) {
            int am_code = keymap[scancode] | (keydown ? KEYDOWN_MASK : 0);
            SDL_LockMutex(key_queue_lock);
            key_queue[key_r] = am_code;
            key_r = (key_r + 1) % KEY_QUEUE_LEN;
            SDL_UnlockMutex(key_queue_lock);
          }
        }
        break;
    }
  }
}

void __am_input_init() {
  key_queue_lock = SDL_CreateMutex();
  SDL_CreateThread(event_thread, "event thread", NULL);
}

size_t __am_input_read(uintptr_t reg, void *buf, size_t size) {
  switch (reg) {
    case _DEVREG_INPUT_KBD: {
      _DEV_INPUT_KBD_t *kbd = (_DEV_INPUT_KBD_t *)buf;
      int k = _KEY_NONE;

      SDL_LockMutex(key_queue_lock);
      if (key_f != key_r) {
        k = key_queue[key_f];
        key_f = (key_f + 1) % KEY_QUEUE_LEN;
      }
      SDL_UnlockMutex(key_queue_lock);

      kbd->keydown = (k & KEYDOWN_MASK ? 1 : 0);
      kbd->keycode = k & ~KEYDOWN_MASK;

      return sizeof(_DEV_INPUT_KBD_t);
    }
  }
  return 0;
}
