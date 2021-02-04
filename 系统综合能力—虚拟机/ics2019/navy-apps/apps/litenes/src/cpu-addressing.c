#include <cpu.h>
#include <memory.h>

// CPU Addressing Modes

void cpu_address_implied()
{
}

void cpu_address_immediate()
{
    op_value = memory_readb(cpu.PC);
    cpu.PC++;

}

void cpu_address_zero_page()
{
    op_address = memory_readb(cpu.PC);
    op_value = CPU_RAM[op_address];
    cpu.PC++;
}

void cpu_address_zero_page_x()
{
    op_address = (memory_readb(cpu.PC) + cpu.X) & 0xFF;
    op_value = CPU_RAM[op_address];
    cpu.PC++;
}

void cpu_address_zero_page_y()
{
    op_address = (memory_readb(cpu.PC) + cpu.Y) & 0xFF;
    op_value = CPU_RAM[op_address];
    cpu.PC++;
}

void cpu_address_absolute()
{
    op_address = memory_readw(cpu.PC);
    op_value = memory_readb(op_address);
    cpu.PC += 2;
}

void cpu_address_absolute_x()
{
    op_address = memory_readw(cpu.PC) + cpu.X;
    op_value = memory_readb(op_address);
    cpu.PC += 2;

    if ((op_address >> 8) != (cpu.PC >> 8)) {
        op_cycles++;
    }
}

void cpu_address_absolute_y()
{
    op_address = (memory_readw(cpu.PC) + cpu.Y) & 0xFFFF;
    op_value = memory_readb(op_address);
    cpu.PC += 2;

    if ((op_address >> 8) != (cpu.PC >> 8)) {
        op_cycles++;
    }
}

void cpu_address_relative()
{
    op_address = memory_readb(cpu.PC);
    cpu.PC++;
    if (op_address & 0x80)
        op_address -= 0x100;
    op_address += cpu.PC;

    if ((op_address >> 8) != (cpu.PC >> 8)) {
        op_cycles++;
    }
}

void cpu_address_indirect()
{
    word arg_addr = memory_readw(cpu.PC);

    // The famous 6502 bug when instead of reading from $C0FF/$C100 it reads from $C0FF/$C000
    if ((arg_addr & 0xFF) == 0xFF) {
        // Buggy code
        op_address = (memory_readb(arg_addr & 0xFF00) << 8) + memory_readb(arg_addr);
    }
    else {
        // Normal code
        op_address = memory_readw(arg_addr);
    }
    cpu.PC += 2;
}

void cpu_address_indirect_x()
{
    byte arg_addr = memory_readb(cpu.PC);
    op_address = (memory_readb((arg_addr + cpu.X + 1) & 0xFF) << 8) | memory_readb((arg_addr + cpu.X) & 0xFF);
    op_value = memory_readb(op_address);
    cpu.PC++;
}

void cpu_address_indirect_y()
{
    byte arg_addr = memory_readb(cpu.PC);
    op_address = (((memory_readb((arg_addr + 1) & 0xFF) << 8) | memory_readb(arg_addr)) + cpu.Y) & 0xFFFF;
    op_value = memory_readb(op_address);
    cpu.PC++;

    if ((op_address >> 8) != (cpu.PC >> 8)) {
        op_cycles++;
    }
}
