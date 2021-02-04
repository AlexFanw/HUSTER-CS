#include "common.h"

#ifndef CPU_H
#define CPU_H

byte cpu_ram_read(word address);
void cpu_ram_write(word address, byte data);

void cpu_init();
void cpu_reset();
void cpu_interrupt();
void cpu_run(long cycles);

// CPU cycles that passed since power up
unsigned long cpu_clock();

typedef enum {
    carry_flag     = 0x01,
    zero_flag      = 0x02,
    interrupt_flag = 0x04,
    decimal_flag   = 0x08,
    break_flag     = 0x10,
    unused_flag    = 0x20,
    overflow_flag  = 0x40,
    negative_flag  = 0x80
} cpu_p_flag;

typedef enum {
    carry_bp      = 0,
    zero_bp       = 1,
    interrupt_bp  = 2,
    decimal_bp    = 3,
    break_bp      = 4,
    unused_bp     = 5,
    overflow_bp   = 6,
    negative_bp   = 7
} cpu_p_bp;

typedef struct {
    word PC; // Program Counter,
    byte SP; // Stack Pointer,
    byte A, X, Y; // Registers
    byte P; // Flag Register
} CPU_STATE;

extern CPU_STATE cpu;

extern byte CPU_RAM[0x8000];

extern byte op_code;             // Current instruction code
extern int op_value, op_address; // Arguments for current instruction
extern int op_cycles;            // Additional instruction cycles used (e.g. when paging occurs)

#endif
