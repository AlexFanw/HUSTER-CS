#include "cpu/exec.h"

make_EHelper(jal){
  uint32_t addr=cpu.pc+4;
  rtl_sr(id_dest->reg,&addr,4);
  rtl_add(&decinfo.jmp_pc,&cpu.pc,&id_src->val);
  rtl_j(decinfo.jmp_pc);

  print_asm_template2(jal);
}

make_EHelper(jalr){
  uint32_t addr=cpu.pc+4;
  rtl_sr(id_dest->reg,&addr,4);
  decinfo.jmp_pc=(id_src->val+id_src2->val)&~1;
  rtl_j(decinfo.jmp_pc);

  difftest_skip_dut(1, 2); //difftest

  print_asm_template2(jalr);
}

make_EHelper(branch){
  decinfo.jmp_pc=cpu.pc+id_dest->val;
  switch(decinfo.isa.instr.funct3){
    case 0: //beq
      rtl_jrelop(RELOP_EQ,&id_src->val,&id_src2->val,decinfo.jmp_pc);
      print_asm_template2(beq);
      break;
    case 1: //bne
      rtl_jrelop(RELOP_NE,&id_src->val,&id_src2->val,decinfo.jmp_pc);
      print_asm_template2(bne);
      break;
    case 4: //blt
      rtl_jrelop(RELOP_LT,&id_src->val,&id_src2->val,decinfo.jmp_pc);
      print_asm_template2(blt);
      break;
    case 5: //bge
      rtl_jrelop(RELOP_GE,&id_src->val,&id_src2->val,decinfo.jmp_pc);
      print_asm_template2(bge);
      break;
    case 6: //bltu
      rtl_jrelop(RELOP_LTU,&id_src->val,&id_src2->val,decinfo.jmp_pc);
      print_asm_template2(bltu);
      break;
    case 7: //bgeu
      rtl_jrelop(RELOP_GEU,&id_src->val,&id_src2->val,decinfo.jmp_pc);
      print_asm_template2(bgeu);
      break;
  }
}
