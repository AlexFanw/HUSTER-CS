#include <iostream>
#include <sys/sem.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int semid;
union semun arg0,arg1;
int a = 0;
pthread_t  s0,s1;
struct sembuf p0,v0,p1,v1;

void* subp1(void*i);
void* subp2(void*i);
void initial();

int main() {
    initial();

    arg0.val = 0;
    arg1.val = 1;
    semid = semget(IPC_PRIVATE,2,IPC_CREAT|0666);
    //if(semctl(semid,0,SETVAL,arg)==-1)perror("sect setval error");//初始化信号量0
    //if(semctl(semid,1,SETVAL,arg)==-1)perror("sect setval error");//初始化信号量1
    semctl(semid,0,SETVAL,arg0);
    semctl(semid,1,SETVAL,arg1);

    pthread_create(&s0, NULL,subp1,NULL);
    pthread_create(&s1, NULL,subp2,NULL);


    pthread_join(s0, NULL);
    pthread_join(s1, NULL);
    pthread_exit(NULL);
}

void initial(){
    p0.sem_num = 0;
    p0.sem_op = -1;
    p0.sem_flg = SEM_UNDO;

    p1.sem_num = 1;
    p1.sem_op = -1;
    p1.sem_flg = SEM_UNDO;

    v0.sem_num = 0;
    v0.sem_op = 1;
    v0.sem_flg = SEM_UNDO;

    v1.sem_num = 1;
    v1.sem_op = 1;
    v1.sem_flg = SEM_UNDO;

}
void* subp1(void *i){
    for(int j=0;j<=100;j++){
        sleep(1);
        semop(semid,&p0,1);            /*占有临界资源*/
        cout << a << endl;
        semop(semid,&v1,1);            /*释放临界资源*/
    }
    semctl(semid,IPC_RMID,0);//撤销信号量集
    return 0;
}
void* subp2(void *i){
    for(int n=0;n<=100;n++){
        sleep(1);
        semop(semid,&p1,1);            /*占有临界资源*/
        a = a + n;
        semop(semid,&v0,1);            /*释放临界资源*/
    }
    return 0;
}