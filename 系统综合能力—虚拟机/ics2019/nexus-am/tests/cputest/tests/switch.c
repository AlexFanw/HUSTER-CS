#include "trap.h"

int switch_case(int n) {
	int ret;
	switch(n) {
		case 0: ret = 0; break;
		case 1: ret = 2; break;
		case 2: case 3: ret = 5; break;
		case 4: case 5: case 6: case 7: ret = 8; break;
		case 8: case 9: case 10: case 11: ret = 10; break;
		case 12: ret = 15; break;
		default: ret = -1; break;
	}

	return ret;
}

int ans[] = {-1, 0, 2, 5, 5, 8, 8, 8, 8, 10, 10, 10, 10, 15, -1};

int main() {
	int i;
	for(i = 0; i < 15; i ++) {
		nemu_assert(switch_case(i - 1) == ans[i]);
	}

	nemu_assert(i == 15);

	return 0;
}
