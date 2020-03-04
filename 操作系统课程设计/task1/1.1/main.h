#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>
#include<pthread.h>
#include<unistd.h>
#include<wait.h>
#include<fcntl.h>
#include <sys/stat.h>
#include<string.h>

void P(int semid,int index)
{	   struct sembuf sem;	
        sem.sem_num = index;
        sem.sem_op = -1;	
        sem.sem_flg = 0; //操作标记：0或IPC_NOWAIT等
        semop(semid,&sem,1);	//1:表示执行命令的个数	
        return;
}

void V(int semid,int index)
{	
	struct sembuf sem;	
    sem.sem_num = index;
    sem.sem_op =  1;
    sem.sem_flg = 0;	
    semop(semid,&sem,1);	
    return;
}

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

typedef struct sharedbuf{
	char buf[10][256];
	int len[10];
	int read_cur,write_cur;
}SharedBuf;

key_t semkey=100;
key_t bufkey1=0x2500;
key_t bufkey2=0x2525;


