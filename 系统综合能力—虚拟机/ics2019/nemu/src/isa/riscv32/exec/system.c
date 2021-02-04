#include "cpu/exec.h"

#define SEPC 0x141
#define SSTATUS 0x100
#define SCAUSE 0x142
#define STVEC 0x105

void raise_intr(uint32_t NO, vaddr_t epc);

//实现四个新的指令
make_EHelper(sys){
  switch(decinfo.isa.instr.funct3){
    case 0:{ //ecall&&sret
      if(decinfo.isa.instr.simm11_0==0){ //ecall
        raise_intr(reg_l(17),cpu.pc);
      }
      else if(decinfo.isa.instr.simm11_0==0b000100000010){ //sret
        rtl_j(cpu.sepc+4);
      }
      break;
    }
    case 1:{ //csrrw 
      switch(decinfo.isa.instr.csr){
        case SEPC:
          t0=cpu.sepc;
          cpu.sepc=id_src->val;
          rtl_sr(id_dest->reg,&t0,4);
          break;
        case SSTATUS:
          t0=cpu.sstatus;
          cpu.sstatus=id_src->val;
          rtl_sr(id_dest->reg,&t0,4);
          break;
        case SCAUSE:
          t0=cpu.scause;
          cpu.scause=id_src->val;
          rtl_sr(id_dest->reg,&t0,4);
          break;
        case STVEC:
          t0=cpu.stvec;
          cpu.stvec=id_src->val;
          rtl_sr(id_dest->reg,&t0,4);
          break;
      }
      print_asm_template3(csrrw);
      break;
    }
    case 2:{ //csrrs
      switch(decinfo.isa.instr.csr){
        case SEPC:
          t0=cpu.sepc;
          cpu.sepc=t0|id_src->val;
          rtl_sr(id_dest->reg,&t0,4);
          break;
        case SSTATUS:
          t0=cpu.sstatus;
          cpu.sstatus=t0|id_src->val;
          rtl_sr(id_dest->reg,&t0,4);
          break;
        case SCAUSE:
          t0=cpu.scause;
          cpu.scause=t0|id_src->val;
          rtl_sr(id_dest->reg,&t0,4);
          break;
        case STVEC:
          t0=cpu.stvec;
          cpu.stvec=t0|id_src->val;
          rtl_sr(id_dest->reg,&t0,4);
          break;
      }
      print_asm_template3(csrrs);
      break;
    }
  }
}