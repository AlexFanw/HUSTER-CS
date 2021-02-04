#include "klib.h"


#define KB 1024
#define MB 1024 * 1024

unsigned int g_seed;

void fast_srand(int seed) {
  g_seed = seed;
}

int fast_rand(void) {
  g_seed = (214013*g_seed+2531011);
  return g_seed;
}

int main() {
  fast_srand(0x12345678);
  unsigned int steps = 1024;
  static uint32_t arr[4 * MB];
  int lengthMod;
  int sizes[] = { 4 * MB };
  int s;

  for (int j = 0; j < 10; j++) {
    for (s = 0; s < sizeof(sizes)/sizeof(int); s++) {
      lengthMod = sizes[s] - 1;
      for (unsigned int i = 0; i < steps; i++) {
        int idx = fast_rand() & lengthMod;
        int result = fast_rand();
        arr[idx] = result;
      }
    }
  }

  fast_srand(0x12345678);
  for (int j = 0; j < 10; j++) {
    for (s = 0; s < sizeof(sizes)/sizeof(int); s++) {
      lengthMod = sizes[s] - 1;
      for (unsigned int i = 0; i < steps; i++) {
        int idx = fast_rand() & lengthMod;
        int result = fast_rand();
        assert(arr[idx] == result);
      }
    }
  }
  return 0;
}
