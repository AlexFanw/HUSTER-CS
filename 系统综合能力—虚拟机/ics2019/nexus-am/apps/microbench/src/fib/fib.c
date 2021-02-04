#include <benchmark.h>

// f(n) = (f(n-1) + f(n-2) + .. f(n-m)) mod 2^32

#define N 2147483603
static int M;

static void put(uint32_t *m, int i, int j, uint32_t data) {
  m[i * M + j] = data;
}

static uint32_t get(uint32_t *m, int i, int j) {
  return m[i * M + j];
}

static inline void mult(uint32_t *c, uint32_t *a, uint32_t *b) {
  for (int i = 0; i < M; i ++)
    for (int j = 0; j < M; j ++) {
      put(c, i, j, 0);
      for (int k = 0; k < M; k ++) {
        put(c, i, j, get(c, i, j) + get(a, i, k) * get(b, k, j));
      }
    }
}

static inline void assign(uint32_t *a, uint32_t *b) {
  for (int i = 0; i < M; i ++)
    for (int j = 0; j < M; j ++)
      put(a, i, j, get(b, i, j));
}

static uint32_t *A, *ans, *T, *tmp;

void bench_fib_prepare() {
  M = setting->size;
  int sz = sizeof(uint32_t) * M * M;
  A = bench_alloc(sz);
  T = bench_alloc(sz);
  ans = bench_alloc(sz);
  tmp = bench_alloc(sz);
}

void bench_fib_run() {
  for (int i = 0; i < M; i ++)
    for (int j = 0; j < M; j ++) {
      uint32_t x = (i == M - 1 || j == i + 1);
      put(A, i, j, x);
      put(T, i, j, x);
      put(ans, i, j, i == j);
    }

  for (int n = N; n > 0; n >>= 1) {
    if (n & 1) {
      mult(tmp, ans, T);
      assign(ans, tmp);
    }
    mult(tmp, T, T);
    assign(T, tmp);
  }
}

int bench_fib_validate() {
  return get(ans, M-1, M-1) == setting->checksum;
}
