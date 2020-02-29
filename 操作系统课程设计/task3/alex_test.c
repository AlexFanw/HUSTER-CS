#include <stdio.h>   
#include <sys/types.h>   
#include <sys/stat.h>   
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int main()   
{   
	int testdev;   
	int i;   
	char buf[10];   
	testdev = open("/dev/alex",O_RDWR);   
	if ( testdev == -1 )   
	{   
		printf("Can't open file \n");   
		exit(0);   
		}   
	read(testdev,buf,10);   
	for (i = 0; i < 10;i++)
	printf("%d\n",buf[i]);  
	close(testdev);   
}  
