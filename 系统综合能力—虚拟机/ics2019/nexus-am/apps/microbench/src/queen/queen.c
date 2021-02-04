#include <benchmark.h>

static unsigned int FULL;

static unsigned int dfs(unsigned int row, unsigned int ld, unsigned int rd) {
  if (row == FULL) {
    return 1;
  } else {
    unsigned int pos = FULL & (~(row | ld | rd)), ans = 0;
    while (pos) {
      unsigned int p = (pos & (~pos + 1));
      pos -= p;
      ans += dfs(row | p, (ld | p) << 1, (rd | p) >> 1);
    }
    return ans;
  }
}

static unsigned int ans;

void bench_queen_prepare() {
  ans = 0;
  FULL = (1 << setting->size) - 1;
}

void bench_queen_run() {
  ans = dfs(0, 0, 0);
}

int bench_queen_validate() {
  return ans == setting->checksum;
}
