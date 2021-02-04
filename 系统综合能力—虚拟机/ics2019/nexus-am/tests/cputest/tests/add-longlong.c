#include "trap.h"

long long add(long long a, long long b) {
	long long c = a + b;
	return c;
}

long long test_data[] = {0, 1, 2, 0x7fffffffffffffffLL, 0x8000000000000000LL, 0x8000000000000001LL, 0xfffffffffffffffeLL, 0xffffffffffffffffLL};
long long ans[] = {0LL, 0x1LL, 0x2LL, 0x7fffffffffffffffLL, 0x8000000000000000LL, 0x8000000000000001LL, 0xfffffffffffffffeLL, 0xffffffffffffffffLL, 0x1LL, 0x2LL, 0x3LL, 0x8000000000000000LL, 0x8000000000000001LL, 0x8000000000000002LL, 0xffffffffffffffffLL, 0LL, 0x2LL, 0x3LL, 0x4LL, 0x8000000000000001LL, 0x8000000000000002LL, 0x8000000000000003LL, 0LL, 0x1LL, 0x7fffffffffffffffLL, 0x8000000000000000LL, 0x8000000000000001LL, 0xfffffffffffffffeLL, 0xffffffffffffffffLL, 0LL, 0x7ffffffffffffffdLL, 0x7ffffffffffffffeLL, 0x8000000000000000LL, 0x8000000000000001LL, 0x8000000000000002LL, 0xffffffffffffffffLL, 0LL, 0x1LL, 0x7ffffffffffffffeLL, 0x7fffffffffffffffLL, 0x8000000000000001LL, 0x8000000000000002LL, 0x8000000000000003LL, 0LL, 0x1LL, 0x2LL, 0x7fffffffffffffffLL, 0x8000000000000000LL, 0xfffffffffffffffeLL, 0xffffffffffffffffLL, 0LL, 0x7ffffffffffffffdLL, 0x7ffffffffffffffeLL, 0x7fffffffffffffffLL, 0xfffffffffffffffcLL, 0xfffffffffffffffdLL, 0xffffffffffffffffLL, 0LL, 0x1LL, 0x7ffffffffffffffeLL, 0x7fffffffffffffffLL, 0x8000000000000000LL, 0xfffffffffffffffdLL, 0xfffffffffffffffeLL};

#define NR_DATA (sizeof(test_data) / sizeof(test_data[0]))

int main() {
	int i, j, ans_idx = 0;
	for(i = 0; i < NR_DATA; i ++) {
		for(j = 0; j < NR_DATA; j ++) {
			nemu_assert(add(test_data[i], test_data[j]) == ans[ans_idx ++]);
		}
	}

	return 0;
}
