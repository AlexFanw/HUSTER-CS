#include "trap.h"

volatile unsigned x = 0xffffffff;
volatile unsigned char buf[16];

int main() {

	for(int i = 0; i < 4; i++) {
		*((volatile unsigned*)(buf + 3)) = 0xaabbccdd;

		x = *((volatile unsigned*)(buf + 3));
		nemu_assert(x == 0xaabbccdd);

		buf[0] = buf[1] = 0;
	}

	return 0;
}
