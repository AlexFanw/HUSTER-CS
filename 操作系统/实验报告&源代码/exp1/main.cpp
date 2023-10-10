#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int pipefd[2];
pid_t s1,s2;

void my_func(int);//全部杀死
void kill_s1(int);//s1 kill
void kill_s2(int);//s2 kill

int main() {
    signal(SIGINT,my_func);//父进程控制进程终止
    char buffer[128];//管道缓冲区
    pipe(pipefd);//管道初始化
    s1 = fork();//子进程s1创建
    if(s1 == 0){//s1子进程运行

        signal(SIGINT,SIG_IGN);
        signal(SIGTERM,kill_s1);

        int x = 1;
        while(1){//写入缓冲区,通过管道读取
            sprintf(buffer, "I send you %d times\n", x);
            write(pipefd[1] , buffer , 128);
            sleep(1);//间隔一秒
            x++;
        }
    }
    
    else {//父进程执行
        s2 = fork();//s2子进程创建
        
        if(s2 == 0){//s2子进程

            signal(SIGINT,SIG_IGN);//忽略ctrl+c
            signal(SIGTERM,kill_s2);

            while(1) {
                read(pipefd[0], buffer, 128);
                cout << buffer ;
            }
        }
        
        else {//父进程执行
            waitpid(s1,NULL,0);
            waitpid(s2,NULL,0);
            close(pipefd[0]);
            close(pipefd[1]);
            cout << "Parent Process is Killed!" << endl;
            return 0;
        }
    }
   
}

void my_func(int sig_no)
{
    signal(SIGINT,SIG_DFL);
    kill(s1,SIGTERM);
    kill(s2,SIGTERM);
}
void kill_s1(int sig_no) {
    cout << "Child Process 1 is Killed by Parent!" << endl;
    exit(1);
}
void kill_s2(int sig_no){
    cout << "Child Process 2 is Killed by Parent!" << endl;
    exit(1);
}