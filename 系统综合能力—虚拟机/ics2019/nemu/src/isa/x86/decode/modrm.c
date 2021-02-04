#include "cpu/exec.h"

void load_addr(vaddr_t *pc, ModR_M *m, Operand *rm) {
  assert(m->mod != 3);

  int32_t disp = 0;
  int disp_size = 4;
  int base_reg = -1, index_reg = -1, scale = 0;
  rtl_li(&s0, 0);

  if (m->R_M == R_ESP) {
    SIB s;
    s.val = instr_fetch(pc, 1);
    base_reg = s.base;
    scale = s.ss;

    if (s.index != R_ESP) { index_reg = s.index; }
  }
  else {
    /* no SIB */
    base_reg = m->R_M;
  }

  if (m->mod == 0) {
    if (base_reg == R_EBP) { base_reg = -1; }
    else { disp_size = 0; }
  }
  else if (m->mod == 1) { disp_size = 1; }

  if (disp_size != 0) {
    /* has disp */
    disp = instr_fetch(pc, disp_size);
    if (disp_size == 1) { disp = (int8_t)disp; }

    rtl_addi(&s0, &s0, disp);
  }

  if (base_reg != -1) {
    rtl_add(&s0, &s0, &reg_l(base_reg));
  }

  if (index_reg != -1) {
    rtl_shli(&s1, &reg_l(index_reg), scale);
    rtl_add(&s0, &s0, &s1);
  }
  rtl_mv(&rm->addr, &s0);

#ifdef DEBUG
  char disp_buf[16];
  char base_buf[8];
  char index_buf[8];

  if (disp_size != 0) {
    /* has disp */
    sprintf(disp_buf, "%s%#x", (disp < 0 ? "-" : ""), (disp < 0 ? -disp : disp));
  }
  else { disp_buf[0] = '\0'; }

  if (base_reg == -1) { base_buf[0] = '\0'; }
  else { 
    sprintf(base_buf, "%%%s", reg_name(base_reg, 4));
  }

  if (index_reg == -1) { index_buf[0] = '\0'; }
  else { 
    sprintf(index_buf, ",%%%s,%d", reg_name(index_reg, 4), 1 << scale);
  }

  if (base_reg == -1 && index_reg == -1) {
    sprintf(rm->str, "%s", disp_buf);
  }
  else {
    sprintf(rm->str, "%s(%s%s)", disp_buf, base_buf, index_buf);
  }
#endif

  rm->type = OP_TYPE_MEM;
}

void read_ModR_M(vaddr_t *pc, Operand *rm, bool load_rm_val, Operand *reg, bool load_reg_val) {
  ModR_M m;
  m.val = instr_fetch(pc, 1);
  decinfo.isa.ext_opcode = m.opcode;
  if (reg != NULL) {
    reg->type = OP_TYPE_REG;
    reg->reg = m.reg;
    if (load_reg_val) {
      rtl_lr(&reg->val, reg->reg, reg->width);
    }

#ifdef DEBUG
    snprintf(reg->str, OP_STR_SIZE, "%%%s", reg_name(reg->reg, reg->width));
#endif
  }

  if (m.mod == 3) {
    rm->type = OP_TYPE_REG;
    rm->reg = m.R_M;
    if (load_rm_val) {
      rtl_lr(&rm->val, m.R_M, rm->width);
    }

#ifdef DEBUG
    sprintf(rm->str, "%%%s", reg_name(m.R_M, rm->width));
#endif
  }
  else {
    load_addr(pc, &m, rm);
    if (load_rm_val) {
      rtl_lm(&rm->val, &rm->addr, rm->width);
    }
  }
}
