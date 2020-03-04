#include "main.h"
#include<string.h>

int main(int argc,char *argv[]){
	int size;
	int semid,shmid;
	semid=semget(semkey,4,IPC_CREAT|0666);//获取信号灯id
	shmid=shmget(bufkey2,sizeof(SharedBuf),IPC_CREAT|0666);//获取共享内存id
	SharedBuf *vaddr=(SharedBuf *)shmat(shmid,NULL,0);//共享内存附接到本程序上
	
	int fp;
	if((fp=open(argv[2],O_WRONLY|O_CREAT,S_IRWXU|S_IRWXG|S_IRWXO))==-1){
		printf("文件打开失败!\n");
		exit(0);
	}

	int over=0;
	printf("Write成功打开文件!信号灯id为%d，共享内存id为%d\n",semid,shmid);
	while(over!=1){
		if(vaddr->len[vaddr->write_cur]<241) over=1;
		P(semid,3);
		write(fp,vaddr->buf[vaddr->write_cur],sizeof(char)*vaddr->len[vaddr->write_cur]);
		vaddr->write_cur=(vaddr->write_cur+1)%10;
		V(semid,2);
		if(over) break;
	}
	close(fp);
	int del=shmdt(vaddr);
	return 0;
	
}
