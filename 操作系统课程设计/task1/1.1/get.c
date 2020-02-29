#include "main.h"


int main(int argc,char *argv[]){
	int size;
	int semid,shmid;
	semid=semget(semkey,4,IPC_CREAT|0666);//获取信号灯id
	shmid=shmget(bufkey1,sizeof(SharedBuf),IPC_CREAT|0666);//获取共享内存id
	SharedBuf *vaddr=(SharedBuf *)shmat(shmid,NULL,0);//共享内存附接到本程序上
	
	//开始进行复制操作
	int fp;
	if((fp=open(argv[1],O_RDONLY))==-1){
		printf("文件打开失败!退出程序\n");
		exit(0);
	}
	printf("Get成功打开文件!信号灯id为%d，共享内存id为%d\n",semid,shmid);
	
	int OK=0;
	while(OK!=1){
		P(semid,0);
		size=read(fp,vaddr->buf[vaddr->read_cur],sizeof(char)*241);
		vaddr->len[vaddr->read_cur]=size;
		if(size<241){//size只要小于256，表明读取已经完成了
			OK=1;	
		}
		vaddr->read_cur=(vaddr->read_cur+1)%10;//下标向后移动
		V(semid,1);
	}
	close(fp);
	int del=shmdt(vaddr);
	return 0;
}
