#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <klib.h>

#define PMEM_SHM_FILE "/native-pmem"
#define PMEM_SIZE (128 * 1024 * 1024) // 128MB
#define PMEM_MAP_START (uintptr_t)0x100000
#define PMEM_MAP_END   (uintptr_t)PMEM_SIZE
#define PMEM_MAP_SIZE  (PMEM_MAP_END - PMEM_MAP_START)

static int pmem_fd = 0;
static ucontext_t uc_example = {};

int main(const char *args);

static void init_platform() __attribute__((constructor));
static void init_platform() {
  pmem_fd = shm_open(PMEM_SHM_FILE, O_RDWR | O_CREAT, 0700);
  assert(pmem_fd != -1);
  assert(0 == ftruncate(pmem_fd, PMEM_SIZE));

  void *ret = mmap((void *)PMEM_MAP_START, PMEM_MAP_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC,
      MAP_SHARED | MAP_FIXED, pmem_fd, PMEM_MAP_START);
  assert(ret != (void *)-1);

  _heap.start = (void *)(PMEM_MAP_START + 4096);  // this is to skip the trap entry
  _heap.end = (void *)PMEM_MAP_END;

  getcontext(&uc_example);

  const char *args = getenv("mainargs");
  exit(main(args ? args : "")); // call main here!
}

static void exit_platform() __attribute__((constructor));
static void exit_platform() {
  int ret = munmap((void *)PMEM_MAP_START, PMEM_MAP_SIZE);
  assert(ret == 0);
  close(pmem_fd);
  ret = shm_unlink(PMEM_SHM_FILE);
  assert(ret == 0);
}

void __am_shm_mmap(void *va, void *pa, int prot) {
  void *ret = mmap(va, 4096, PROT_READ | PROT_WRITE | PROT_EXEC,
      MAP_SHARED | MAP_FIXED, pmem_fd, (uintptr_t)pa);
  assert(ret != (void *)-1);
}

void __am_shm_munmap(void *va) {
  int ret = munmap(va, 4096);
  assert(ret == 0);
}

void __am_get_example_uc(_Context *r) {
  memcpy(&r->uc, &uc_example, sizeof(uc_example));
}

// This dummy function will be called in trm.c.
// The purpose of this dummy function is to let linker add this file to the object
// file set. Without it, the constructor of @_init_platform will not be linked.
void __am_platform_dummy() {
}
