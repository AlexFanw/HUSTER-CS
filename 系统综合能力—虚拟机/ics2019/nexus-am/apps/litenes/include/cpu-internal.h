#ifndef CPU_INTERNAL_H
#define CPU_INTERNAL_H

#include "common.h"

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
extern int op_value, op_address; // Arguments for current instruction
extern int op_cycles;            // Additional instruction cycles used (e.g. when paging occurs)

byte cpu_ram_read(word address);
void cpu_ram_write(word address, byte data);

// Interrupt Addresses
word cpu_nmi_interrupt_address();
word cpu_reset_interrupt_address();
word cpu_irq_interrupt_address();

// CPU Adressing Modes
void cpu_address_implied();
void cpu_address_immediate();
void cpu_address_zero_page();
void cpu_address_zero_page_x();
void cpu_address_zero_page_y();
void cpu_address_absolute();
void cpu_address_absolute_x();
void cpu_address_absolute_y();
void cpu_address_relative();
void cpu_address_indirect();
void cpu_address_indirect_x();
void cpu_address_indirect_y();

#endif
