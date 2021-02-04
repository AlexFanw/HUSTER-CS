#include "klib.h"

int main() {
  int round = 30;
  static char arr[4 * 1024 * 1024];
  for (int i = 0; i < round; i++)
    arr[i * 64] = i;
  for (int i = 0; i < round; i++)
    assert(arr[i * 64] == (char)i);
  return 0;
}
