#include "cpu/exec.h"

make_EHelper(lui) {
  rtl_sr(id_dest->reg, &id_src->val, 4);

  print_asm_template2(lui);
}

make_EHelper(auipc){
  rtl_add(&id_dest->val,&cpu.pc,&id_src->val);
  rtl_sr(id_dest->reg,&id_dest->val,4);

  print_asm_template2(auipc);
}

make_EHelper(imm){
  switch(decinfo.isa.instr.funct3){
    case 0: //addi
      rtl_add(&id_dest->val,&id_src->val,&id_src2->val);
      rtl_sr(id_dest->reg,&id_dest->val,4);
      print_asm_template2(addi);
      break;
    case 1: //slli
      rtl_shl(&id_dest->val,&id_src->val,&id_src2->reg);
      rtl_sr(id_dest->reg,&id_dest->val,4);
      print_asm_template2(slli);
      break;
    case 2: //slti
      id_dest->val=(signed)id_src->val<(signed)id_src2->val;
      rtl_sr(id_dest->reg,&id_dest->val,4);
      print_asm_template2(slti);
      break;
    case 3: //sltiu
      id_dest->val=(unsigned)id_src->val<(unsigned)id_src2->val;
      rtl_sr(id_dest->reg,&id_dest->val,4);
      print_asm_template2(sltiu);
      break;
    case 4: //xori
      rtl_xor(&id_dest->val,&id_src->val,&id_src2->val);
      rtl_sr(id_dest->reg,&id_dest->val,4);
      print_asm_template2(xori);
      break;
    case 5: //srli&&srai
      if(decinfo.isa.instr.funct7==0b0000000){ //srli
        rtl_shr(&id_dest->val,&id_src->val,&id_src2->reg);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template2(srli);
      }
      else if(decinfo.isa.instr.funct7==0b0100000){ //srai
        rtl_sar(&id_dest->val,&id_src->val,&id_src2->reg);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template2(srai);
      }
      break;
    case 6: //ori
      rtl_or(&id_dest->val,&id_src->val,&id_src2->val);
      rtl_sr(id_dest->reg,&id_dest->val,4);
      print_asm_template2(ori);
      break;
    case 7: //andi
      rtl_and(&id_dest->val,&id_src->val,&id_src2->val);
      rtl_sr(id_dest->reg,&id_dest->val,4);
      print_asm_template2(andi);
      break;
  }
}

make_EHelper(reg){
  switch(decinfo.isa.instr.funct3){
    case 0: //add&&sub&&mul
      if(decinfo.isa.instr.funct7==0b0000000){ //add
        rtl_add(&id_dest->val,&id_src->val,&id_src2->val);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template3(add);
      }
      else if(decinfo.isa.instr.funct7==0b0100000){ //sub
        rtl_sub(&id_dest->val,&id_src->val,&id_src2->val);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template3(sub);
      }
      else if(decinfo.isa.instr.funct7==0b0000001){ //mul
        rtl_imul_lo(&id_dest->val,&id_src->val,&id_src2->val);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template3(mul);
      }
      break;
    case 1: //sll&&mulh
      if(decinfo.isa.instr.funct7==0b0000000){ //sll
        rtl_shl(&id_dest->val,&id_src->val,&id_src2->val);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template3(sll); 
      }
      else if(decinfo.isa.instr.funct7==0b0000001){ //mulh
        rtl_imul_hi(&id_dest->val,&id_src->val,&id_src2->val);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template3(mulh);
      }
      break;
    case 2: //slt
      id_dest->val=(signed)id_src->val<(signed)id_src2->val;
      rtl_sr(id_dest->reg,&id_dest->val,4);
      print_asm_template3(slt);
      break;
    case 3: //sltu
      id_dest->val=(unsigned)id_src->val<(unsigned)id_src2->val;
      rtl_sr(id_dest->reg,&id_dest->val,4);
      print_asm_template3(sltu);
      break;
    case 4: //xor&&div
      if(decinfo.isa.instr.funct7==0b0000000){ //xor
        rtl_xor(&id_dest->val,&id_src->val,&id_src2->val);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template3(xor);
      }
      else if(decinfo.isa.instr.funct7==0b0000001){ //div
        rtl_idiv_q(&id_dest->val,&id_src->val,&id_src2->val);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template3(div);
      }
      break;
    case 5: //srl&&sra&&divu
      if(decinfo.isa.instr.funct7==0b0000000){ //srl
        rtl_shr(&id_dest->val,&id_src->val,&id_src2->val);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template2(srl);
      }
      else if(decinfo.isa.instr.funct7==0b0100000){ //sra
        rtl_sar(&id_dest->val,&id_src->val,&id_src2->val);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template2(sra);
      }
      else if(decinfo.isa.instr.funct7==0b0000001){ //divu
        rtl_div_q(&id_dest->val,&id_src->val,&id_src2->val);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template3(divu);
      }
      break;
    case 6: //or&&rem
      if(decinfo.isa.instr.funct7==0b0000000){ //or
        rtl_or(&id_dest->val,&id_src->val,&id_src2->val);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template3(or);
      }
      else if(decinfo.isa.instr.funct7==0b0000001){ //rem
        rtl_idiv_r(&id_dest->val,&id_src->val,&id_src2->val);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template3(rem);
      }
      break;
    case 7: //and&&remu 
      if(decinfo.isa.instr.funct7==0b0000000){ //and
        rtl_and(&id_dest->val,&id_src->val,&id_src2->val);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template3(and);
      }
      else if(decinfo.isa.instr.funct7==0b0000001){ //remu
        rtl_div_r(&id_dest->val,&id_src->val,&id_src2->val);
        rtl_sr(id_dest->reg,&id_dest->val,4);
        print_asm_template3(remu);
      }
      break;
  }
}