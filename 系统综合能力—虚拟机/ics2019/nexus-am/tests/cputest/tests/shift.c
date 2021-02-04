
#include "trap.h"
#define ARR_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

unsigned test[] = {
	0x12345678, 0x98765432, 0x0, 0xeffa1000, 0x7fffffff, 0x80000000, 0x33, 0xffffffff
};

unsigned srl_ans[] = {
	0x2468ac, 0x130eca8, 0x0, 0x1dff420, 0xffffff, 0x1000000, 0x0, 0x1ffffff
};

unsigned srlv_ans[] = {
	0x1234567, 0x4c3b2a1, 0x0, 0x1dff420, 0x7fffff, 0x400000, 0x0, 0x1fffff
};

unsigned srav_ans[] = {
	0x1234567, 0xfcc3b2a1, 0x0, 0xffdff420, 0x7fffff, 0xffc00000, 0x0, 0xffffffff
};


int main() {
	unsigned i;

	for(i = 0; i < ARR_SIZE(test); i ++) {
		nemu_assert((test[i] >> 7) == srl_ans[i]);
	}

	for(i = 0; i < ARR_SIZE(test); i ++) {
		nemu_assert((unsigned)((int)test[i] >> (i + 4)) == srav_ans[i]);
	}

	for(i = 0; i < ARR_SIZE(test); i ++) {
		nemu_assert((test[i] >> (i + 4)) == srlv_ans[i]);
	}

	return 0;
}
