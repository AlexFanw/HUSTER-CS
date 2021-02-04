#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_wp(){
  if(free_ == NULL){
    printf("watchpoints:FULL");
    assert(0);
  }
  WP *new=free_;
  free_=free_->next;
  new->next=head;
  head=new;
  return new;
}

void free_wp(int NO){
  if(head==NULL||NO<0||NO>NR_WP){
    printf("Free Watchpoint Failed. Don't exist\n");
    assert(0);
  }
  WP *temp=head;
  WP *pre=(WP*)malloc(sizeof(WP));
  pre->next=temp;
  while(temp->NO!=NO){
    pre=pre->next;
    temp=temp->next;
  }
  if(temp==NULL)
    return;
  pre->next=pre->next->next;
  if(temp==head)
    head = temp->next;
  temp->next = free_;
  free_ = temp;
}

void print_wp(){
  if(head==NULL)
    printf("watchpoint : None\n");
  else{
    printf("%-10s %-20s %-10s\n", "NO", "EXPR", "VALUE");
    for(WP *temp=head; temp!=NULL;temp=temp->next){
      printf("%-10d %-20s %-10d\n", temp->NO,temp->str,temp->value);
    }
  }
}

WP* get_head(){
  return head;
}