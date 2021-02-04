#include <am.h>
#include <klib.h>

#define N 5

void f(void *s) {
  int volatile n = 0;
  const char *str = s;
  while (1) {
    printf("%s", str);
    if (str[0] == 'a' && ++n >= 10000) {
      return; // bug, should panic.
    }
  }
}

_Context *current = NULL;
_Context contexts[N];
char texts[N][2];
uint8_t stacks[N][1024];

_Context* handler(_Event ev, _Context *ctx) {
  if (!current) {
    current = contexts; // 1st interrupt
  } else {
    *current = *ctx;
    current++;
    if (current == contexts + N) { // round-robin
      current = contexts;
    }
  }
  return current;
}

#define STACK(id) \
  (_Area) { .start = &stacks[(id)    ][0], \
            .end   = &stacks[(id) + 1][0], }

int main(){
  printf("kcontext test started.\n");
  _cte_init(handler);
  assert(!_intr_read());
  for (int i = 0; i < N; i++) {
    texts[i][0] = 'a' + i;
    contexts[i] = *_kcontext(STACK(i), f, texts[i]);
  }
  _intr_write(1);
  while (1) {
    _yield();
  }
  return 0;
}
