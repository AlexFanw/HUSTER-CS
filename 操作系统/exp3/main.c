#include<stdio.h>
#include"main.h"

#include<sys/sem.h>//信号灯
#include<sys/shm.h>//共享内存
#include<sys/wait.h>

#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>


union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO */
};//信号灯集

void P(int semid, int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = SEM_UNDO;
    semop(semid, &sem, 1);
    return ;
}//p操作

void V(int semid, int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = SEM_UNDO;
    semop(semid, &sem, 1);
    return ;
}//v操作

static int read_proc = 0, write_proc = 0;//读写进程的进程号

typedef struct _ShareBuffer {
    unsigned char status;   //!< current shared buffer status
    uint32_t size;          //!< current message size
    int  nextshm;           //!< pointer to the next Message
    char data[DATASIZE];    //!< where data is stored
} ShareBuffer;

int read_pro(FILE *inFile, int shmhead, int shmtail, int semid) {
    // start to read file to buffer
    ShareBuffer *bufferTail = (ShareBuffer *)shmat(shmtail, NULL, 0);
    while (1) {
        P(semid, 2);//抢占进程权限.上锁
        P(semid, 1);//共享缓冲区空间减1
        printf("Read\n");//读取中
        size_t bytesRead;
        if ((bytesRead = fread((void *)(bufferTail->data), 1, DATASIZE, inFile)) == 0) {
            //从文件流中读入DATASIZE大小的数据进缓冲区//
            bufferTail->status = STATUS_ALL;
            bufferTail->size = bytesRead;
            fclose(inFile);
            V(semid, 0);//读入文件加1
            V(semid, 2);//释放权限.
            return 0;
        }
        bufferTail->size = bytesRead;//缓冲区大小为读入数据块的大小
        shmtail = bufferTail->nextshm;//跳转至下一个缓冲区//
        bufferTail = (ShareBuffer *)shmat(shmtail, NULL, 0);//获取该缓冲区
        V(semid, 0);//读入文件加1
        V(semid, 2);//释放权限
    }
}

int write_pro(FILE *outFile, int shmhead, int shmtail, int semid) {
    ShareBuffer *bufferhead = (ShareBuffer *)shmat(shmhead, NULL, 0);
    while (1) {
        P(semid, 2);//抢占进程权限.上锁
        P(semid, 0);//缓冲区文件减1
        printf("write\n");//写入文件
        if (bufferhead->status == STATUS_ALL) {
            fwrite((void *)(bufferhead->data), bufferhead->size, 1, outFile);//写入缓冲区数据块大小的文件进入目标文件
            fclose(outFile);//关闭文件
            V(semid, 1);//共享缓冲区数量加1
            V(semid, 2);//解除权限
            return 0;
        }
        fwrite((void *)(bufferhead->data), bufferhead->size, 1, outFile);//写入缓冲区数据块大小的文件进入目标文件
        shmhead = bufferhead->nextshm;//缓冲区头部转移至下一块缓冲区
        bufferhead = (ShareBuffer *)shmat(shmhead, NULL, 0);//获取该缓冲区
        V(semid, 1);//共享缓冲区空间减1
        V(semid, 2);//解除权限
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("请在 ./main 后依次输入源文件与目标文件\n");
        return 1;
    }//如果不按要求输出文件路径,进行报错

    FILE *fileIn;
    FILE *fileOut;
    if ((fileIn = fopen(argv[1], "rb")) == NULL) {
        perror("无法读取源文件.");
        return 1;
    }//打开源文件
    if ((fileOut = fopen(argv[2], "wb")) == NULL) {
        perror("无法创建打开目标文件.");
        return 1;
    }//如果目标文件不存在,则创建目标文件

    key_t shmkey;
    if ((shmkey = ftok("./key", 'b')) == (key_t)(-1)) {
        perror("无法获取key值");
        exit(1);
    }//获取共享内存key值

    int shm_head;
    if ((shm_head = shmget(shmkey, sizeof(ShareBuffer), IPC_CREAT | 0666)) <= 0) {
        perror("无法创建共享缓冲区");
        exit(1);
    }//创建第一个head共享缓冲区

    ShareBuffer *shareBuffer = (ShareBuffer *)shmat(shm_head, NULL, 0);
    if ((int64_t)(shareBuffer) == -1) {
        perror("无法获取共享缓冲区");
        exit(1);
    }//获取该共享缓冲区
    shareBuffer->status = STATUS_PENDING | STATUS_HEAD | STATUS_TAIL;//停等I/O输入

    for (int i = 0; i < BUFFERNUM; ++i) {
        key_t shmkey;
        if ((shmkey = ftok("./key", i)) == (key_t)(-1)) {
            perror("无法获取key值");
            exit(1);
        }//获取共享缓冲区key值
        int idShm;
        if ((idShm = shmget(shmkey, sizeof(ShareBuffer), IPC_CREAT | 0666)) <= 0) {
            perror("无法创建共享缓冲区");
            exit(1);
        }//创建共享缓冲区,原理同上述创建head缓冲区一样.
        shareBuffer->nextshm = idShm;
        shareBuffer->status = STATUS_PENDING;
        shareBuffer = (ShareBuffer *)shmat(idShm, NULL, 0);
        if ((int64_t)(shareBuffer) == -1) {
            perror("无法获取共享缓冲区");
            exit(1);
        }
    }
    shareBuffer->nextshm = shm_head;//将最后一个缓冲区链接到头缓冲区构成循环

    int semid;
    semid = semget(IPC_PRIVATE, 3, IPC_CREAT | 0666);//创建三个信号灯.
    union semun wp; // 用于写进程的参数
    union semun rp; // 用于读进程的参数
    union semun mutex;
    wp.val = BUFFERNUM; // 写进程的初始值为BUFFSIZE
    rp.val = 0; // 读进程的初始值为0
    mutex.val = 1;
    if (semctl(semid, 0, SETVAL, wp) == -1 || 
        semctl(semid, 1, SETVAL, rp) == -1 ||
        semctl(semid, 2, SETVAL, mutex)  == -1) {
        perror("IPC error 1: semctl");
        exit(1);
        }//初始化三个信号灯,并将三个信号灯分配给三个进程.

    if ((read_proc = fork()) == -1) {
        perror("Failed to create process.");
        return 1;
    }//创建读文件子进程
    if (read_proc == 0){
        return read_pro(fileIn, shm_head, shm_head, semid);
    }//调用read_pro函数读取文件,并放入缓冲区.
    if ((write_proc = fork()) == -1) {
        perror("Failed to create process.");
        kill(read_proc, SIGKILL);//当read进程结束时,销毁write进程
        return 1;
    }//创建写文件子进程
    if (write_proc == 0){
        return write_pro(fileOut, shm_head, shm_head, semid);
    }//调用write_pro函数将文件写入.

    waitpid(read_proc, NULL, 0);//等待进程结束
    waitpid(write_proc, NULL, 0);//等待进程结束

    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("销毁信号灯失败\n");
    }//销毁信号灯
    if (shmctl(shm_head, IPC_RMID, NULL) == -1) {
        perror("销毁共享内存失败\n");
    }//销毁共享内存
    return 0;
}

