#include "trap.h"

char *s[] = {
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	", World!\n",
	"Hello, World!\n",
	"#####"
};

char str1[] = "Hello";
char str[20];

int main() {
	nemu_assert(strcmp(s[0], s[2]) == 0);
	nemu_assert(strcmp(s[0], s[1]) == -1);
	nemu_assert(strcmp(s[0] + 1, s[1] + 1) == -1);
	nemu_assert(strcmp(s[0] + 2, s[1] + 2) == -1);
	nemu_assert(strcmp(s[0] + 3, s[1] + 3) == -1);

	nemu_assert(strcmp( strcat(strcpy(str, str1), s[3]), s[4]) == 0);

	nemu_assert(memcmp(memset(str, '#', 5), s[5], 5) == 0);

	return 0;
}
