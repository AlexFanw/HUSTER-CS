#include "klib.h"

int ans[64] = {0};

int main() {
  int i = 0;
  for (i = 0; i < 64; i++)
    ans[i] = 64 - i;
  for (i = 0; i < 64; i++)
    assert(ans[i] == 64 - i);
  return 0;
}
