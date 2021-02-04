#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

#include <am.h>
#include <klib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MB * 1024 * 1024
#define KB * 1024

#define true 1
#define false 0

#define REF_CPU    "i7-7700K @ 4.20GHz"
#define REF_SCORE  100000

#define REPEAT  1

//                  size |  heap | time |  checksum
#define QSORT_S {     100,   1 KB,     0, 0x08467105}
#define QSORT_M {   30000, 128 KB,     0, 0xa3e99fe4}
#define QSORT_L {  100000, 640 KB,  5114, 0xed8cff89}
#define QUEEN_S {       8,   0 KB,     0, 0x0000005c}
#define QUEEN_M {      11,   0 KB,     0, 0x00000a78}
#define QUEEN_L {      12,   0 KB,  4707, 0x00003778}
#define    BF_S {       4,  32 KB,     0, 0xa6f0079e}
#define    BF_M {      25,  32 KB,     0, 0xa88f8a65}
#define    BF_L {     180,  32 KB, 23673, 0x9221e2b3}
#define   FIB_S {       2,   1 KB,     0, 0x7cfeddf0}
#define   FIB_M {      23,  16 KB,     0, 0x94ad8800}
#define   FIB_L {      91, 256 KB, 28318, 0xebdc5f80}
#define SIEVE_S {     100,   1 KB,     0, 0x00000019}
#define SIEVE_M {  200000,  32 KB,     0, 0x00004640}
#define SIEVE_L {10000000,   2 MB, 39361, 0x000a2403}
#define  PZ15_S {       0,   1 KB,     0, 0x00000006}
#define  PZ15_M {       1, 256 KB,     0, 0x0000b0df}
#define  PZ15_L {       2,   2 MB,  4486, 0x00068b8c}
#define DINIC_S {      10,   8 KB,     0, 0x0000019c}
#define DINIC_M {      80, 512 KB,     0, 0x00004f99}
#define DINIC_L {     128,   1 MB, 10882, 0x0000c248}
#define  LZIP_S {     128, 128 KB,     0, 0xe05fc832}
#define  LZIP_M {   50000,   1 MB,     0, 0xdc93e90c}
#define  LZIP_L { 1048576,   4 MB,  7593, 0x8d62c81f}
#define SSORT_S {     100,   4 KB,     0, 0x4c555e09}
#define SSORT_M {   10000, 512 KB,     0, 0x0db7909b}
#define SSORT_L {  100000,   4 MB,  4504, 0x4f0ab431}
#define   MD5_S {     100,   1 KB,     0, 0xf902f28f}
#define   MD5_M {  200000, 256 KB,     0, 0xd4f9bc6d}
#define   MD5_L {10000000,  16 MB, 17239, 0x27286a42}

#define BENCHMARK_LIST(def) \
  def(qsort, "qsort", QSORT_S, QSORT_M, QSORT_L, "Quick sort") \
  def(queen, "queen", QUEEN_S, QUEEN_M, QUEEN_L, "Queen placement") \
  def(   bf,    "bf",    BF_S,    BF_M,    BF_L, "Brainf**k interpreter") \
  def(  fib,   "fib",   FIB_S,   FIB_M,   FIB_L, "Fibonacci number") \
  def(sieve, "sieve", SIEVE_S, SIEVE_M, SIEVE_L, "Eratosthenes sieve") \
  def( 15pz,  "15pz",  PZ15_S,  PZ15_M,  PZ15_L, "A* 15-puzzle search") \
  def(dinic, "dinic", DINIC_S, DINIC_M, DINIC_L, "Dinic's maxflow algorithm") \
  def( lzip,  "lzip",  LZIP_S,  LZIP_M,  LZIP_L, "Lzip compression") \
  def(ssort, "ssort", SSORT_S, SSORT_M, SSORT_L, "Suffix sort") \
  def(  md5,   "md5",   MD5_S,   MD5_M,   MD5_L, "MD5 digest") \

// Each benchmark will run REPEAT times

#define DECL(_name, _sname, _s, _m, _l, _desc) \
  void bench_##_name##_prepare(); \
  void bench_##_name##_run(); \
  int bench_##_name##_validate();

BENCHMARK_LIST(DECL)

typedef struct Setting {
  int size;
  unsigned long mlim, ref;
  uint32_t checksum;
} Setting;

typedef struct Benchmark {
  void (*prepare)();
  void (*run)();
  int (*validate)();
  const char *name, *desc;
  Setting settings[3];
} Benchmark;

extern Benchmark *current;
extern Setting *setting;

typedef struct Result {
  int pass;
  unsigned long tsc, msec;
} Result;

void prepare(Result *res);
void done(Result *res);

// memory allocation
void* bench_alloc(size_t size);
void bench_free(void *ptr);

// random number generator
void bench_srand(uint32_t seed);
uint32_t bench_rand(); // return a random number between 0..32767

// checksum
uint32_t checksum(void *start, void *end);

#ifdef __cplusplus
}
#endif

#endif
