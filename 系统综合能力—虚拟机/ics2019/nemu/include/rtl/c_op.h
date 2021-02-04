#ifndef __RTL_C_OP_H__
#define __RTL_C_OP_H__

#define c_add(a, b) ((a) + (b))
#define c_sub(a, b) ((a) - (b))
#define c_and(a, b) ((a) & (b))
#define c_or(a, b)  ((a) | (b))
#define c_xor(a, b) ((a) ^ (b))
#define c_shl(a, b) ((a) << (b))
#define c_shr(a, b) ((a) >> (b))
#define c_sar(a, b) ((int32_t)(a) >> (b))
#define c_mul_lo(a, b) ((a) * (b))
#define c_mul_hi(a, b) (((uint64_t)(a) * (uint64_t)(b)) >> 32)
#define c_imul_lo(a, b) ((int32_t)(a) * (int32_t)(b))
#define c_imul_hi(a, b) (((int64_t)(int32_t)(a) * (int64_t)(int32_t)(b)) >> 32)
#define c_div_q(a, b) ((a) / (b))
#define c_div_r(a, b)  ((a) % (b))
#define c_idiv_q(a, b) ((int32_t)(a) / (int32_t)(b))
#define c_idiv_r(a, b)  ((int32_t)(a) % (int32_t)(b))

#endif
