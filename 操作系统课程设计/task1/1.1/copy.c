#include "main.h"


int main(int argc,char *argv[]){
	int size;
	int semid,shmid1,shmid2;
	semid=semget(semkey,4,IPC_CREAT|0666);//获取信号灯id
	shmid1=shmget(bufkey1,sizeof(SharedBuf),IPC_CREAT|0666);//获取共享内存id
	SharedBuf *vaddr1=(SharedBuf *)shmat(shmid1,NULL,0);//共享内存附接到本程序上

	shmid2=shmget(bufkey2,sizeof(SharedBuf),IPC_CREAT|0666);//获取共享内存id
	SharedBuf *vaddr2=(SharedBuf *)shmat(shmid2,NULL,0);//共享内存附接到本程序上	

	int OK=0;
	while(OK!=1){
		P(semid,1);
		P(semid,2);
		size=sizeof(char)*vaddr1->len[vaddr1->write_cur];
		memcpy(vaddr2->buf[vaddr2->read_cur],vaddr1->buf[vaddr1->write_cur],size);
		vaddr2->len[vaddr2->read_cur]=size;
		if(size<241) OK=1;
		vaddr1->write_cur=(vaddr1->write_cur+1)%10;//下标向后移动
		vaddr2->read_cur=(vaddr2->read_cur+1)%10;//下标向后移动
		V(semid,0);
		V(semid,3);
	}
	int del=shmdt(vaddr1);
	int del2=shmdt(vaddr2);
	return 0;
}
