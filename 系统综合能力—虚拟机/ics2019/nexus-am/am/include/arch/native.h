#ifndef __ARCH_H__
#define __ARCH_H__

#ifndef __USE_GNU
# define __USE_GNU
#endif

#include <unistd.h>
#include <ucontext.h>
#include <sys/types.h>

#define false 0
#define true 1

struct _Context {
  union {
    uint8_t pad[1024];
    struct {
      ucontext_t uc;
      void *as;
    };
  };
  uintptr_t rdi;
  uintptr_t rax;
  uintptr_t rip;
};

#define GPR1 rax
#define GPR2 rdi
#define GPR3 uc.uc_mcontext.gregs[REG_RSI]
#define GPR4 uc.uc_mcontext.gregs[REG_RDX]
#define GPRx rax

#undef __USE_GNU

#endif
