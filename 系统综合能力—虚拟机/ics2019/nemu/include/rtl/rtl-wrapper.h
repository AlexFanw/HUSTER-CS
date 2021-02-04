#ifndef __RTL_RTL_WRAPPER_H__
#define __RTL_RTL_WRAPPER_H__

#include "macro.h"

#define RTL_PREFIX interpret

#define rtl_li        concat(RTL_PREFIX, _rtl_li      )
#define rtl_mv        concat(RTL_PREFIX, _rtl_mv      )
#define rtl_add       concat(RTL_PREFIX, _rtl_add     )
#define rtl_sub       concat(RTL_PREFIX, _rtl_sub     )
#define rtl_and       concat(RTL_PREFIX, _rtl_and     )
#define rtl_or        concat(RTL_PREFIX, _rtl_or      )
#define rtl_xor       concat(RTL_PREFIX, _rtl_xor     )
#define rtl_shl       concat(RTL_PREFIX, _rtl_shl     )
#define rtl_shr       concat(RTL_PREFIX, _rtl_shr     )
#define rtl_sar       concat(RTL_PREFIX, _rtl_sar     )
#define rtl_mul_lo    concat(RTL_PREFIX, _rtl_mul_lo  )
#define rtl_mul_hi    concat(RTL_PREFIX, _rtl_mul_hi  )
#define rtl_imul_lo   concat(RTL_PREFIX, _rtl_imul_lo )
#define rtl_imul_hi   concat(RTL_PREFIX, _rtl_imul_hi )
#define rtl_div_q     concat(RTL_PREFIX, _rtl_div_q   )
#define rtl_div_r     concat(RTL_PREFIX, _rtl_div_r   )
#define rtl_idiv_q    concat(RTL_PREFIX, _rtl_idiv_q  )
#define rtl_idiv_r    concat(RTL_PREFIX, _rtl_idiv_r  )
#define rtl_div64_q   concat(RTL_PREFIX, _rtl_div64_q )
#define rtl_div64_r   concat(RTL_PREFIX, _rtl_div64_r )
#define rtl_idiv64_q  concat(RTL_PREFIX, _rtl_idiv64_q)
#define rtl_idiv64_r  concat(RTL_PREFIX, _rtl_idiv64_r)
#define rtl_lm        concat(RTL_PREFIX, _rtl_lm      )
#define rtl_sm        concat(RTL_PREFIX, _rtl_sm      )
#define rtl_host_lm   concat(RTL_PREFIX, _rtl_host_lm )
#define rtl_host_sm   concat(RTL_PREFIX, _rtl_host_sm )
#define rtl_setrelop  concat(RTL_PREFIX, _rtl_setrelop)
#define rtl_j         concat(RTL_PREFIX, _rtl_j       )
#define rtl_jr        concat(RTL_PREFIX, _rtl_jr      )
#define rtl_jrelop    concat(RTL_PREFIX, _rtl_jrelop  )
#define rtl_exit      concat(RTL_PREFIX, _rtl_exit    )

#endif
