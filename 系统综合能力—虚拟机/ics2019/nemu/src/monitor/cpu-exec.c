#include "nemu.h"
#include "monitor/monitor.h"
#include "monitor/watchpoint.h"

/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the `si' command.
 * You can modify this value as you want.
 */
#define MAX_INSTR_TO_PRINT 10

/* restrict the size of log file */
#define LOG_MAX (1024 * 1024)

uint32_t expr(char *e, bool *success);
WP* get_head();

NEMUState nemu_state = {.state = NEMU_STOP};

void interpret_rtl_exit(int state, vaddr_t halt_pc, uint32_t halt_ret) {
  nemu_state = (NEMUState) { .state = state, .halt_pc = halt_pc, .halt_ret = halt_ret };
}

vaddr_t exec_once(void);
void difftest_step(vaddr_t ori_pc, vaddr_t next_pc);
void asm_print(vaddr_t ori_pc, int instr_len, bool print_flag);
void log_clearbuf(void);

static uint64_t g_nr_guest_instr = 0;

void monitor_statistic(void) {
  Log("total guest instructions = %ld", g_nr_guest_instr);
}

/* Simulate how the CPU works. */
void cpu_exec(uint64_t n) {
  switch (nemu_state.state) {
    case NEMU_END: case NEMU_ABORT:
      printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
      return;
    default: nemu_state.state = NEMU_RUNNING;
  }

  for (; n > 0; n --) {
    __attribute__((unused)) vaddr_t ori_pc = cpu.pc;

    /* Execute one instruction, including instruction fetch,
     * instruction decode, and the actual execution. */
    __attribute__((unused)) vaddr_t seq_pc = exec_once();

#if defined(DIFF_TEST)
  difftest_step(ori_pc, cpu.pc);
#endif

#ifdef DEBUG
  if (g_nr_guest_instr < LOG_MAX) {
    asm_print(ori_pc, seq_pc - ori_pc, n < MAX_INSTR_TO_PRINT);
  }
  else if (g_nr_guest_instr == LOG_MAX) {
    log_write("\n[Warning] To restrict the size of log file, "
              "we do not record more instruction trace beyond this point.\n"
              "To capture more trace, you can modify the LOG_MAX macro in %s\n\n", __FILE__);
  }
  log_clearbuf();

    /* TODO: check watchpoints here. */

  bool flag = false, success = true;
  WP *temp=get_head();
  for(;temp!=NULL;temp=temp->next){
    uint32_t res=expr(temp->str, &success);
    if(res!=temp->value){
      flag=true;
      temp->value=res;
    }
  }
  if(flag){
    printf("watchpoint:Status Changed\n");
    nemu_state.state=NEMU_STOP;
  }

#endif

  g_nr_guest_instr ++;

#ifdef HAS_IOE
    extern void device_update();
    device_update();
#endif

    if (nemu_state.state != NEMU_RUNNING) break;
  }

  switch (nemu_state.state) {
    case NEMU_RUNNING: nemu_state.state = NEMU_STOP; break;

    case NEMU_END: case NEMU_ABORT:
      _Log("nemu: %s\33[0m at pc = 0x%08x\n\n",
          (nemu_state.state == NEMU_ABORT ? "\33[1;31mABORT" :
           (nemu_state.halt_ret == 0 ? "\33[1;32mHIT GOOD TRAP" : "\33[1;31mHIT BAD TRAP")),
          nemu_state.halt_pc);
      monitor_statistic();
  }
}
