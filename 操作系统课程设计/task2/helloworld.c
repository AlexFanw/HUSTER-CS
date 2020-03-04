#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<sys/syscall.h>
#include<linux/kernel.h>
int main(int argc,char *argv[]){
	long int a=syscall(335,5);
        printf("System call sys_mycall return %ld\n",a);
        return 0;
}
