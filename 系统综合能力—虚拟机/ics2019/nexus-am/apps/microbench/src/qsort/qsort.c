#include <benchmark.h>

static int N, *data;

void bench_qsort_prepare() {
  bench_srand(1);

  N = setting->size;

  data = bench_alloc(N * sizeof(int));
  for (int i = 0; i < N; i ++) {
    int a = bench_rand();
    int b = bench_rand();
    data[i] = (a << 16) | b;
  }
}

static void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

static void myqsort(int *a, int l, int r) {
  if (l < r) {
    int p = a[l], pivot = l, j;
    for (j = l + 1; j < r; j ++) {
      if (a[j] < p) {
        swap(&a[++pivot], &a[j]);
      }
    }
    swap(&a[pivot], &a[l]);
    myqsort(a, l, pivot);
    myqsort(a, pivot + 1, r);
  }
}

void bench_qsort_run() {
  myqsort(data, 0, N);
}

int bench_qsort_validate() {
  return checksum(data, data + N) == setting->checksum;
}
