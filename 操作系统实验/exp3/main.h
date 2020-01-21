#ifndef MAIN_H_
#define MAIN_H_
#include<stdio.h>
#include<stdint.h>
#define BUFFERNUM 1024
#define DATASIZE 1000
#define STATUS_PENDING  0x01
#define STATUS_READ     0x02
#define STATUS_WRITTEN  0x04
#define STATUS_ALL      0x08
#define STATUS_HEAD     0x10
#define STATUS_TAIL     0x20
#define SIZE_HEADER 5

int read_pro(FILE *inFile, int idShmHead, int idShmTail, int idSem);

int write_pro(FILE *outFile, int idShmHead, int idShmTail, int idSem);

#endif