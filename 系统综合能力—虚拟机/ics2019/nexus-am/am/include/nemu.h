#ifndef __NEMU_H__
#define __NEMU_H__

#include ISA_H // "x86.h", "mips32.h", ...

#if defined(__ISA_X86__)
# define nemu_trap(code) asm volatile (".byte 0xd6" : :"a"(code))
#elif defined(__ISA_MIPS32__)
# define nemu_trap(code) asm volatile ("move $v0, %0; .word 0xf0000000" : :"r"(code))
#elif defined(__ISA_RISCV32__)
# define nemu_trap(code) asm volatile("mv a0, %0; .word 0x0000006b" : :"r"(code))
#elif
# error unsupported ISA __ISA__
#endif

#ifdef __ARCH_X86_NEMU
# define SERIAL_PORT  0x3f8
# define KBD_ADDR     0x60
# define RTC_ADDR     0x48
# define SCREEN_ADDR  0x100
# define SYNC_ADDR    0x104
# define FB_ADDR      0xa0000000
#else
# define SERIAL_PORT  0xa10003f8
# define KBD_ADDR     0xa1000060
# define RTC_ADDR     0xa1000048
# define SCREEN_ADDR  0xa1000100
# define SYNC_ADDR    0xa1000104
# define FB_ADDR      0xa0000000
#endif

#define PMEM_SIZE (128 * 1024 * 1024)
#define PGSIZE    4096

#define MMIO_BASE 0xa0000000
#define MMIO_SIZE 0x10000000

#endif
