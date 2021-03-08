#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd[2]; // 兩個檔案描述符
    pid_t pid;
    char buff[20];

    if (pipe(fd) < 0) // 建立管道
        printf("Create Pipe Error!\n");

    if ((pid = fork()) < 0) // 建立子程序
        printf("Fork Error!\n");
    else if (pid > 0) // 父程序
    {
        close(fd[0]); // 關閉讀端
        write(fd[1], "hello world\n", 12);
    }
    else
    {
        close(fd[1]); // 關閉寫端
        read(fd[0], buff, 20);
        printf("%s", buff);
    }

    return 0;
}