#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint64_t);
void isa_reg_display();
void print_wp();
void free_wp(int NO);
WP* new_wp();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}

static int cmd_q(char *args) {
  return -1;
}

static int cmd_help(char *args);

static int cmd_si(char*args){
  int num=1;
  if(!(args==NULL))
    num=atoi(args);
  cpu_exec(num);
  return 0;
}

static int cmd_info(char *args){
  if(args!=NULL && args[0] == 'r')
    isa_reg_display();
  else if(args!=NULL && args[0] == 'w')
    print_wp();
  return 0;
}

static int cmd_x(char *args){
  int num;
  vaddr_t addr;
  char* temp;
  if(args==NULL){
    return -1;
  }
  char *token=strtok(args," ");
  num=atoi(token);
  token=strtok(NULL, " ");
  if(token==NULL){
    return -1;
  }
  addr=strtol(token,&temp,16);
  for(int i=0;i<num;i++){
    printf("0x%08x 0x%08x\n", addr+i*4,vaddr_read(addr+i*4,4));
  }
  return 0;
}

static int cmd_p(char *args){
  bool success=true;
  uint32_t res = expr(args, &success);
  if(!success){
    printf("Expression Wrong!\n");
    return -1;
  }
  printf("%d\n", res);
  return 0;
}

static int cmd_w(char *args){
  bool success=true;
  uint32_t res=expr(args, &success);
  if(!success){
    printf("Expression Wrong\n");
    return -1;
  }
  WP *new=new_wp();
  new->value=res;
  strcpy(new->str,args);
  printf("Set Watchpoint Succeed\n");
  return 0;
}

static int cmd_d(char *args){
  if(args==NULL)
    return -1;
  int num=atoi(args);
  free_wp(num);
  printf("Delete No.%d Watchpoint~\n", num);
  return 0;
}

static struct {
  char *name;
  char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display informations about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "Single Step Execute", cmd_si},
  { "info", "Print details of register || watchpoint", cmd_info},
  { "x", "Scan memory", cmd_x},
  { "p", "Expression Evaluation", cmd_p},
  { "w", "Set a New Watchpoint", cmd_w},
  { "d", "Delete Watchpoint", cmd_d}
  /* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void ui_mainloop(int is_batch_mode) {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef HAS_IOE
    extern void sdl_clear_event_queue(void);
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}
