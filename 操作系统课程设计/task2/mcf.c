#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<sys/syscall.h>
int main(int argc,char *argv[]){
	long a=syscall(336,argv[1],argv[2]);
        printf("System call sys_mcf return %ld\n",a);
        return 0;
}
