 //pipe_write.c

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
#define TEN_MEG (sizeof(MSG) * 2)  
  
int main()  
{  
    int pipe_fd;  
    int res;  
    int open_mode = O_WRONLY;  
  
    int bytes = 0;  
    MSG mssage;
	memcpy(mssage.ip, "172.16.23.219", strlen("172.16.23.219"));
	memcpy(mssage.name, "/stroage/clip/123.mp4", strlen("/stroage/clip/123.mp4"));
  
    if (access(FIFO_NAME, F_OK) == -1)  
    {  
        res = mkfifo(FIFO_NAME, 0777);  
        if (res != 0)  
        {  
            fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);  
            exit(EXIT_FAILURE);  
        }  
    }  
  
    printf("Process %d opening FIFO O_WRONLY\n", getpid());  
    pipe_fd = open(FIFO_NAME, open_mode);  
    printf("Process %d result %d\n", getpid(), pipe_fd);  
  
   //sleep(20);
    if (pipe_fd != -1)  
    {  
        while (bytes < TEN_MEG)  
        {  
            res = write(pipe_fd,&mssage, BUFFER_SIZE);  
            if (res == -1)  
            {  
                fprintf(stderr, "Write error on pipe\n");  
                exit(EXIT_FAILURE);  
            }  
            bytes += res;  
        printf("%d\n",bytes);
        }  
        close(pipe_fd);  
    }  
    else  
    {  
        exit(EXIT_FAILURE);  
    }
   unlink(FIFO_NAME);  
  
    printf("Process %d finish\n", getpid());  
    exit(EXIT_SUCCESS);  
}
