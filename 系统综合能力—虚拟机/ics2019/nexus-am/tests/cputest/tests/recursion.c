#include "trap.h"

int f0(int, int);
int f1(int, int);
int f2(int, int);
int f3(int, int);

int (*func[])(int, int) = {
  f0, f1, f2, f3,
};

int rec = 0, lvl = 0;

int f0(int n, int l) {
  if (l > lvl) lvl = l;
  rec ++;
  return n <= 0 ? 1 : func[3](n / 3, l + 1);
};

int f1(int n, int l) {
  if (l > lvl) lvl = l;
  rec ++;
  return n <= 0 ? 1 : func[0](n - 1, l + 1);
};

int f2(int n, int l) {
  if (l > lvl) lvl = l;
  rec ++;
  return n <= 0 ? 1 : func[1](n, l + 1) + 9;
};

int f3(int n, int l) {
  if (l > lvl) lvl = l;
  rec ++;
  return n <= 0 ? 1 : func[2](n / 2, l + 1) * 3 + func[2](n / 2, l + 1) * 2;
};

int ans[] = {38270, 218, 20};

int main() {
  int x = func[0](14371, 0);
  nemu_assert(x == ans[0]);   // answer
  nemu_assert(rec == ans[1]); // # recursions
  nemu_assert(lvl == ans[2]); // max depth
  return 0;
}
