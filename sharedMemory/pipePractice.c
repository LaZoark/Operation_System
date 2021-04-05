#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void SIGFPE_Handler(int);
int main()
{
    int fd[2]; // 兩個檔案描述符
    pid_t pid;
    char *buff[20];//={};
    if (signal(SIGPIPE, SIGFPE_Handler) == SIG_ERR)
    {
        perror("Set up signal handler error!");
        abort();
    }
    if (pipe(fd) < 0) // 建立管道
        printf("Create Pipe Error!\n");

    if ((pid = fork()) < 0) // 建立子程序
        printf("Fork Error!\n");
    else if (pid > 0) // 父程序
    {
        printf("father here\n");
        // close(fd[0]); // 關閉讀端
        write(fd[1], "hello world\n", 12);
        // write(fd[1], "ABCD1234\n", 9);
    }
    else
    {
        printf("child here\n");
        close(fd[1]); // 關閉寫端
        // close(fd[0]);
        read(fd[0], buff, sizeof(buff));
        printf("%s", buff);
    }
    return 0;
}


void SIGFPE_Handler(int signum)
{
    printf("Signal: %d\n", signum);
    perror("Write to pipe with no readers!\a");
    abort();
}