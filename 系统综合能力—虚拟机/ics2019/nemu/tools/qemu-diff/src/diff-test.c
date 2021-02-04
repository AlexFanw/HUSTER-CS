#include "common.h"
#include <sys/prctl.h>
#include <signal.h>
#include "isa.h"

bool gdb_connect_qemu(void);
bool gdb_memcpy_to_qemu(uint32_t, void *, int);
bool gdb_getregs(union isa_gdb_regs *);
bool gdb_setregs(union isa_gdb_regs *);
bool gdb_si(void);
void gdb_exit(void);

void init_isa(void);

void difftest_memcpy_from_dut(paddr_t dest, void *src, size_t n) {
  bool ok = gdb_memcpy_to_qemu(dest, src, n);
  assert(ok == 1);
}

void difftest_getregs(void *r) {
  union isa_gdb_regs qemu_r;
  gdb_getregs(&qemu_r);
  memcpy(r, &qemu_r, DIFFTEST_REG_SIZE);
}

void difftest_setregs(const void *r) {
  union isa_gdb_regs qemu_r;
  gdb_getregs(&qemu_r);
  memcpy(&qemu_r, r, DIFFTEST_REG_SIZE);
  gdb_setregs(&qemu_r);
}

void difftest_exec(uint64_t n) {
  while (n --) gdb_si();
}

void difftest_init(void) {
  int ppid_before_fork = getpid();
  int pid = fork();
  if (pid == -1) {
    perror("fork");
    assert(0);
  }
  else if (pid == 0) {
    // child

    // install a parent death signal in the chlid
    int r = prctl(PR_SET_PDEATHSIG, SIGTERM);
    if (r == -1) {
      perror("prctl error");
      assert(0);
    }

    if (getppid() != ppid_before_fork) {
      printf("parent has died!\n");
      assert(0);
    }

    close(STDIN_FILENO);
    execlp(ISA_QEMU_BIN, ISA_QEMU_BIN, ISA_QEMU_ARGS "-S", "-s", "-nographic", NULL);
    perror("exec");
    assert(0);
  }
  else {
    // father

    gdb_connect_qemu();
    printf("Connect to QEMU successfully\n");

    atexit(gdb_exit);

    init_isa();
  }
}
