#include "quicklz.h"
#include <benchmark.h>

static int SIZE;

static qlz_state_compress *state;
static char *blk;
static char *compress;
static int len;

void bench_lzip_prepare() {
  SIZE = setting->size;
  bench_srand(1);
  state = bench_alloc(sizeof(qlz_state_compress));
  blk = bench_alloc(SIZE);
  compress = bench_alloc(SIZE + 400);
  for (int i = 0; i < SIZE; i ++) {
    blk[i] = 'a' + bench_rand() % 26;
  }
}

void bench_lzip_run() {
  len = qlz_compress(blk, compress, SIZE, state);
}

int bench_lzip_validate() {
  return checksum(compress, compress + len) == setting->checksum;
}

