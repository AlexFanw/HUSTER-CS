#include "trap.h"

int if_else(int n) {
	int cost;
	if(n > 500) cost = 150;
	else if(n > 300) cost = 100;
	else if(n > 100) cost = 75;
	else if(n > 50) cost = 50;
	else cost = 0;

	return cost;
}

int test_data[] = {-1, 0, 49, 50, 51, 99, 100, 101, 299, 300, 301, 499, 500, 501};
int ans[] = {0, 0, 0, 0, 50, 50, 50, 75, 75, 75, 100, 100, 100, 150};

#define NR_DATA (sizeof(test_data) / sizeof(test_data[0]))

int main() {
	int i, ans_idx = 0;
	for(i = 0; i < NR_DATA; i ++) {
		nemu_assert(if_else(test_data[i]) == ans[ans_idx ++]);
	}

	nemu_assert(i == NR_DATA);

	return 0;
}
