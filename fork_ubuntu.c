#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){    
    pid_t PID = fork();// 從呼叫 fork 開始, 會分成兩支程序多工進行
    switch(PID){    // PID == -1 代表 fork 出錯
        case -1: perror("fork()"); exit(-1);                
        case 0: // PID == 0 代表是子程序
            printf("I'm Child process\n");
            printf("Child's PID is %d\n", getpid()); break;          
        default: // PID > 0 代表是父程序
            printf("I'm Parent process\n");
            printf("Parent's PID is %d\n", getpid());
    }
    return 0;
}
