#include "trap.h"

long long mul(long long a,long long b) {
	long long ans = a*b;
	return ans;
}

int test_data[] = { 0xaeb1c2aa, 0x4500ff2b, 0x877190af, 0x11f42438};
long long ans[] = { 0x19d29ab9db1a18e4LL, 0xea15986d3ac3088eLL, 0x2649e980fc0db236LL, 0xfa4c43da0a4a7d30LL, 0x1299898e2c56b139LL, 0xdf8123d50a319e65LL, 0x4d6dfa84c15dd68LL, 0x38c5d79b9e4357a1LL, 0xf78b91cb1efc4248LL, 0x14255a47fdfcc40LL};

#define NR_DATA (sizeof(test_data) / sizeof(test_data[0]))

int main() {
	int i,j,ans_idx = 0;
	for (i = 0;i < NR_DATA;i++) {
		for (j = i;j < NR_DATA;j++) { 
			nemu_assert(ans[ans_idx++] == mul(test_data[i],test_data[j]));
		}
		nemu_assert(j == NR_DATA);
	}

	nemu_assert(i == NR_DATA);

	return 0;
}
			
