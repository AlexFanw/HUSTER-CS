#include "trap.h"

#define ARR_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

unsigned short mem[] = {
	0x0, 0x0258, 0x4abc, 0x7fff, 0x8000, 0x8100, 0xabcd, 0xffff
};

unsigned lh_ans[] = {
	0x00000000, 0x00000258, 0x00004abc, 0x00007fff, 0xffff8000, 0xffff8100, 0xffffabcd, 0xffffffff
};

unsigned lhu_ans[] = {
	0x00000000, 0x00000258, 0x00004abc, 0x00007fff, 0x00008000, 0x00008100, 0x0000abcd, 0x0000ffff
};

unsigned  sh_ans[] = {
	0x0000fffd, 0x0000fff7, 0x0000ffdf, 0x0000ff7f, 0x0000fdff, 0x0000f7ff, 0x0000dfff, 0x00007fff
};

unsigned  lwlr_ans[] = {
	0xbc025800, 0x7fff4a, 0xcd810080, 0xffffab
};

int main() {
	unsigned i;

	for(i = 0; i < ARR_SIZE(mem); i ++) {
		nemu_assert((short)mem[i] == lh_ans[i]);
	}

	for(i = 0; i < ARR_SIZE(mem); i ++) {
		nemu_assert(mem[i] == lhu_ans[i]);
	}

	for(i = 0; i < ((ARR_SIZE(mem) / 2) - 1); i ++) {
		unsigned x = ((unsigned*)((void*)mem + 1))[i];
		nemu_assert(x == lwlr_ans[i]);
	}

	for(i = 0; i < ARR_SIZE(mem); i ++) {
		mem[i] = ~(1 << (2 * i + 1));
		nemu_assert(mem[i] == sh_ans[i]);
	}

	return 0;
}
