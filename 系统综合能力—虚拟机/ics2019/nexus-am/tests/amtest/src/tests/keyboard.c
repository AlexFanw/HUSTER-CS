#include <amtest.h>
#include <amdev.h>

#define NAME(key) \
  [_KEY_##key] = #key,

const char *names[256] = {
  [_KEY_NONE] = "NONE",
  _KEYS(NAME)
};

void keyboard_test() {
  printf("Try to press any key...\n");
  while (1) {
    int key = read_key();
    int down = 0;
    if (key & 0x8000) {
      key ^= 0x8000;
      down = 1;
    }
    if (key != _KEY_NONE) {
      printf("Get key: %d %s %s\n", key, names[key], down ? "down" : "up");
    }
  }
}
