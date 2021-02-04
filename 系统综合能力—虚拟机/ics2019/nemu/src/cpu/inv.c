#include "common.h"

void display_inv_msg(vaddr_t pc) {
  extern char isa_logo[];
  printf("There are two cases which will trigger this unexpected exception:\n"
      "1. The instruction at PC = 0x%08x is not implemented.\n"
      "2. Something is implemented incorrectly.\n", pc);
  printf("Find this PC(0x%08x) in the disassembling result to distinguish which case it is.\n\n", pc);
  printf("\33[1;31mIf it is the first case, see\n%s\nfor more details.\n\nIf it is the second case, remember:\n"
      "* The machine is always right!\n"
      "* Every line of untested code is always wrong!\33[0m\n\n", isa_logo);
}
