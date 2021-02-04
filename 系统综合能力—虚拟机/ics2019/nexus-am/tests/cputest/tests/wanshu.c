#include "trap.h"

int ans[] = {6, 28};

int main() {
	int n, sum, i, k = 0;
	for(n = 1; n < 30; n ++) {
		sum = 0;
		for(i = 1; i < n; i ++) {
			if(n % i == 0) {
				sum += i;
			}
		}
		
		if(sum == n) {
			nemu_assert(n == ans[k]);
			k ++;
		}
	}

	nemu_assert(k == 2);

	return 0;
}
