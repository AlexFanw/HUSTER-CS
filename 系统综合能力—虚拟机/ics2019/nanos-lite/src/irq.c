#include "common.h"

_Context* do_syscall(_Context *c);

//_Context修正
static _Context* do_event(_Event e, _Context* c) {
  switch (e.event) {
    case _EVENT_YIELD:
      Log("self trap");
      break;
    case _EVENT_SYSCALL: 
      do_syscall(c);        
      break;
    default: panic("Unhandled event ID = %d", e.event);
  }

  return NULL;
}

// _init_irq修正
void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  _cte_init(do_event);
}
