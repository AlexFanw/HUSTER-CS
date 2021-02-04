#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

uint32_t isa_reg_str2val(const char *s, bool *success);
uint32_t paddr_read(paddr_t addr, int len);

enum {
  TK_NOTYPE = 256, TK_EQ,

  /* TODO: Add more token types */
  
  TK_INT, TK_HEX, TK_REG, TK_NOTEQ, TK_AND, TK_OR, TK_DEREFERENCE, TK_NEGATIVE
};

static struct rule {
  char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},         // equal
  {"\\-", '-'},
  {"\\*", '*'},
  {"\\/", '/'},
  {"\\(", '('},
  {"\\)", ')'},
  {"[0-9]+", TK_INT},
  {"0[Xx][0-9a-fA-F]+", TK_HEX},
  {"\\$(\\$0|ra|sp|gp|tp|t[0-6]|s[0-9]|a[0-7]|s10|s11)", TK_REG},
  {"!=", TK_NOTEQ},
  {"&&", TK_AND},
  {"\\|\\|", TK_OR},
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        //Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            //i, rules[i].regex, position, substr_len, substr_len, substr_start);
        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
          case '+':
            tokens[nr_token++].type='+';
            break;
          case '-':
            tokens[nr_token++].type='-';
            break;
          case '*':
            tokens[nr_token++].type='*';
            break;
          case '/':
            tokens[nr_token++].type='/';
            break;
          case '(':
            tokens[nr_token++].type='(';
            break;
          case ')':
            tokens[nr_token++].type=')';
            break;
          case TK_NOTYPE:
            break;
          case TK_EQ:
            tokens[nr_token++].type=TK_EQ;
            break;
          case TK_NOTEQ:
            tokens[nr_token++].type=TK_NOTEQ;
            break;
          case TK_AND:
            tokens[nr_token++].type=TK_AND;
            break;
          case TK_OR:
            tokens[nr_token++].type=TK_OR;
            break;
          case TK_INT:
            tokens[nr_token].type=TK_INT;
            if(substr_len>=32){
              printf("string too long\n");
              return false;
            }
            strncpy(tokens[nr_token].str,substr_start,substr_len);
            tokens[nr_token].str[substr_len]='\0';
            nr_token++;
            break;
          case TK_HEX:
            tokens[nr_token].type=TK_HEX;
            if(substr_len>=32){
              printf("string too long\n");
              return false;
            }
            strncpy(tokens[nr_token].str,substr_start,substr_len);
            tokens[nr_token].str[substr_len]='\0';
            nr_token++;
            break;
          case TK_REG:
            tokens[nr_token].type=TK_REG;
            strncpy(tokens[nr_token].str,substr_start+1,substr_len-1);
            tokens[nr_token].str[substr_len-1]='\0';
            nr_token++;
            break;
          case TK_DEREFERENCE:
            tokens[nr_token++].type=TK_DEREFERENCE;
            break;
        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

bool check_parentheses(int p,int q){
  bool res=false;
  if(tokens[p].type!='('||tokens[q].type!=')')
    return res;
  int count=0;
  res=true;
  for(int i=p+1;i<=q-1;i++){
    if(tokens[i].type=='(')
      count++;
    else if(tokens[i].type==')')
      count--;
    if(count<0)
      res=false;
  }
  if(count!=0)
    res=false;
  return res;
}

int op_priority(int type){
  switch(type){
    case TK_NEGATIVE:
      return 1;
    case TK_DEREFERENCE:
      return 2;
    case '*':
    case '/':
      return 3;
    case '+':
    case '-':
      return 4;
    case TK_EQ:
    case TK_NOTEQ:
      return 5;
    case TK_AND:
      return 6;
    case TK_OR:
      return 7;
    default:
      return 0;
  }
  return 0;
}

uint32_t hex_val(char c){
  if(c>='a'&&c<='f')
    return c-'a'+10;
  if(c>='A'&&c<='F')
    return c-'A'+10;
  return c-'0';
}

uint32_t eval(int p,int q,bool *success){
  if(p>q){
    printf("wrong input p>q\n");
    *success=false;
    return 0;
  }
  else if(p==q){
    if(tokens[p].type!=TK_INT&&tokens[p].type!=TK_HEX&&tokens[p].type!=TK_REG){
      printf("wrong single token p:%d\n",p);
      *success=false;
      return 0;
    }
    uint32_t value=0;
    if(tokens[p].type==TK_INT){
      for(int i=0;i<strlen(tokens[p].str);i++)
        value=value*10+tokens[p].str[i]-'0';
    }
    else if(tokens[p].type==TK_HEX){
      for(int i=0;i<strlen(tokens[p].str);i++)
        value=value*16+hex_val(tokens[p].str[i]);
    }
    else{
      bool temp=true;
      value=isa_reg_str2val(tokens[p].str,&temp);
      if(!temp){
        *success=false;
        return 0;
      }
    }
    return value;
  }
  else if(check_parentheses(p,q)==true){
    bool temp=true;
    uint32_t res=eval(p+1,q-1,&temp);
    if(!temp){
      *success=false;
      return 0;
    }
    return res;
  }
  else{
    int op=-1,op_pri=0;
    int count=0;
    for(int i=p;i<=q;i++){
      if(tokens[i].type=='(')
        count++;
      if(tokens[i].type==')')
        count--;
      if(count!=0)
        continue;
      if(op_priority(tokens[i].type)>0){
        int cur_pri=op_priority(tokens[i].type);
        if(cur_pri>=op_pri){
          if(!(cur_pri==op_pri&&(op_pri==1||op_pri==2))){
            op=i;
            op_pri=cur_pri;
          }
        }
      }
    }
    if(op!=-1){
      bool temp1=true,temp2=true;
      uint32_t val1=0,val2=0;
      if(tokens[op].type!=TK_NEGATIVE&&tokens[op].type!=TK_DEREFERENCE)
        val1=eval(p,op-1,&temp1);
      val2=eval(op+1,q,&temp2);
      if(!temp1||!temp2){
        *success=false;
        return 0;
      }
      switch(tokens[op].type){
        case '+':
          return val1+val2;
        case '-':
          return val1-val2;
        case '*':
          return val1*val2;
        case '/':
          if(val2==0){
            *success=false;
            return 0;
          }
          return val1/val2;
        case '(':
        case ')':
          *success=false;
          return 0;
        case TK_EQ:
          return val1==val2;
        case TK_NOTEQ:
          return val1!=val2;
        case TK_AND:
          return val1&&val2;
        case TK_OR:
          return val1||val2;
        case TK_NEGATIVE:
          return -val2;
        case TK_DEREFERENCE:
          return paddr_read(val2,4);
        default:
          *success=false;
          return 0;
      }
    }
    else{
      *success=false;
      return 0;
    }
  }
  return 0;
}

uint32_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */

  for(int i=0;i<nr_token;i++){
    if(tokens[i].type=='*'&&(i==0||tokens[i-1].type=='+'||tokens[i-1].type=='-'||tokens[i-1].type=='*'||tokens[i-1].type=='/'||tokens[i-1].type=='('||tokens[i-1].type==TK_DEREFERENCE)){
      tokens[i].type=TK_DEREFERENCE;
    }
  }
  for(int i=0;i<nr_token;i++){
    if(tokens[i].type=='-'&&(i==0||tokens[i-1].type=='+'||tokens[i-1].type=='-'||tokens[i-1].type=='*'||tokens[i-1].type=='/'||tokens[i-1].type=='('||tokens[i-1].type==TK_NEGATIVE)){
      tokens[i].type=TK_NEGATIVE;
    }
  }
  /*
  for(int i=0;i<nr_token;i++){
    printf("%s %d\n",tokens[i].str,tokens[i].type);
  }
  */
  return eval(0,nr_token-1,success);
}

