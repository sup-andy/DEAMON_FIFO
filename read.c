 //pipe_read.c

#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <fcntl.h>  
#include <limits.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
  
 typedef struct msg
{
	char ip[16];
	char name[60];
}MSG;

#define FIFO_NAME "/tmp/my_fifo"  
#define BUFFER_SIZE sizeof(MSG)  
  
int main()  
{  
    int pipe_fd;  
    int res;  
  
    int open_mode = O_RDONLY;  
    char buffer[BUFFER_SIZE]; 
	MSG *msg;
    int bytes = 0;  
  
    memset(buffer, '0', sizeof(buffer));  
  
    printf("Process %d opeining FIFO O_RDONLY\n", getpid());  
    pipe_fd = open(FIFO_NAME, open_mode);  
    printf("Process %d result %d\n", getpid(), pipe_fd);  
  
    if (pipe_fd != -1)  
    {  
        do{  
            res = read(pipe_fd, buffer, BUFFER_SIZE);  
            bytes += res;  
        printf("%d\n",bytes);
		msg = (MSG*)buffer;
		printf("ip address is %s", msg->ip);
		printf("ip name is %s", msg->name);
        }while(res > 0);  
        close(pipe_fd);  
    }  
    else  
    {  
        exit(EXIT_FAILURE);  
    }  
  
    printf("Process %d finished, %d bytes read\n", getpid(), bytes);  
    exit(EXIT_SUCCESS);  
}