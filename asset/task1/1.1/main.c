#include "main.h"


int main(int argc,char *argv[]){
	int semid=semget(semkey,4,IPC_CREAT|0666);
	//信号灯创建
	union semun un1,un2,un3,un4;
	un1.val=10;
	un2.val=0;
	un3.val=10;
	un4.val=0;
	semctl(semid,0,SETVAL,un1);
	semctl(semid,1,SETVAL,un2);
	semctl(semid,2,SETVAL,un3);
	semctl(semid,3,SETVAL,un4);



	//共享内存创建
	int shmid1=shmget(bufkey1,sizeof(SharedBuf),IPC_CREAT|0666);
	SharedBuf *vaddr1=(SharedBuf*)shmat(shmid1,NULL,0);//附接到main本程序上

	//共享内存创建
	int shmid2=shmget(bufkey2,sizeof(SharedBuf),IPC_CREAT|0666);
	SharedBuf *vaddr2=(SharedBuf*)shmat(shmid2,NULL,0);//附接到main本程序上



	vaddr1->read_cur=0;
	vaddr1->write_cur=0;
	vaddr2->read_cur=0;
	vaddr2->write_cur=0;
	pid_t p1,p2,p3;

	printf("主进程信号灯id为%d,共享内存id为%dand%d\n",semid,shmid1,shmid2);
	if((p1=fork())==-1){
		printf("子进程1创建失败!\n");
		exit(0);
	}
	else if(p1==0){
		printf("Get开始执行\n");
		execv("./Get",argv);
	}
	else if((p2=fork())==-1){
		printf("子进程2创建失败!\n");
		exit(0);
	}
	else if(p2==0){
		printf("Copy开始执行\n");
		execv("./Copy",argv);
	}
	else if((p3=fork())==-1){
		printf("子进程3创建失败!\n");
		exit(0);
	}
	else if(p3==0){
		printf("Write开始执行\n");
		execv("./Write",argv);
	}
	else{
		//等待两个子进程退出
		wait(&p1);
		wait(&p2);
		wait(&p3);
		int del=shmdt(vaddr1);
		int del2=shmdt(vaddr2);
		//删除信号灯和共享内存
		semctl(semid,0,IPC_RMID);
		shmctl(shmid1,0,IPC_RMID);
		shmctl(shmid2,0,IPC_RMID);
		printf("主程序退出\n");

	}
	return 0;

}
