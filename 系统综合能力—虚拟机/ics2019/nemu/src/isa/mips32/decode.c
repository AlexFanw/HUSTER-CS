#include "cpu/decode.h"
#include "rtl/rtl.h"

// decode operand helper
#define make_DopHelper(name) void concat(decode_op_, name) (Operand *op, uint32_t val, bool load_val)

static inline make_DopHelper(i) {
  op->type = OP_TYPE_IMM;
  op->imm = val;
  rtl_li(&op->val, op->imm);

  print_Dop(op->str, OP_STR_SIZE, "%d", op->imm);
}

static inline make_DopHelper(r) {
  op->type = OP_TYPE_REG;
  op->reg = val;
  if (load_val) {
    rtl_lr(&op->val, op->reg, 4);
  }

  print_Dop(op->str, OP_STR_SIZE, "%s", reg_name(op->reg, 4));
}

make_DHelper(IU) {
  decode_op_r(id_src, decinfo.isa.instr.rs, true);
  decode_op_i(id_src2, decinfo.isa.instr.imm, true);
  decode_op_r(id_dest, decinfo.isa.instr.rt, false);

  print_Dop(id_src2->str, OP_STR_SIZE, "0x%x", decinfo.isa.instr.imm);
}

static inline make_DHelper(addr) {
  decode_op_r(id_src, decinfo.isa.instr.rs, true);
  decode_op_i(id_src2, decinfo.isa.instr.simm, true);

  print_Dop(id_src->str, OP_STR_SIZE, "%d(%s)", id_src2->val, reg_name(id_src->reg, 4));

  rtl_add(&id_src->addr, &id_src->val, &id_src2->val);
}

make_DHelper(ld) {
  decode_addr(NULL);
  decode_op_r(id_dest, decinfo.isa.instr.rt, false);
}

make_DHelper(st) {
  decode_addr(NULL);
  decode_op_r(id_dest, decinfo.isa.instr.rt, true);
}
