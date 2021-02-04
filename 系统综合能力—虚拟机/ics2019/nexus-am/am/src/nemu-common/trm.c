#include <am.h>
#include <nemu.h>

extern char _heap_start;
extern char _heap_end;
int main(const char *args);

_Area _heap = {
  .start = &_heap_start,
  .end = &_heap_end,
};

void _putc(char ch) {
  outb(SERIAL_PORT, ch);
}

void _halt(int code) {
  nemu_trap(code);

  // should not reach here
  while (1);
}

void _trm_init() {
  extern const char _start;
  const char *mainargs = &_start - 0x100000;
  int ret = main(mainargs);
  _halt(ret);
}
