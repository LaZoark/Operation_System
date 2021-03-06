#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void pf(pid_t proid, int count, float stime)
{
    int i;
    for(i=0;i<count;i++)
    {
        printf("%d:%d\n",proid,i);
        sleep(stime);
    }
}
// int k=0;
int main()
{
    pid_t PID = fork();// 從呼叫 fork 開始, 會分成兩支程序多工進行
    switch(PID)
    {
        case -1: // PID == -1 代表 fork 出錯
            perror("fork()");
            exit(-1);
        case 0: // PID == 0 代表是子程序
            printf("[Child] Child's PID is %d\n",getpid());
            // pf(getpid(),3,1);
            // printf("k=%d\n",++k);
            pid_t id_child=fork();
            if(id_child==-1) // PID == -1 代表 fork 出錯
                {
                    perror("fork()");
                    exit(-1);
                }
                else if(id_child==0)// PID == 0 代表是子程序
                        printf("[*Child] Child's PID is   %d\n",getpid());
            else// PID > 0 代表是父程序
                    printf("[*Parent] Parent's PID is %d\n",getpid());
            break;
        default: // PID > 0 代表是父程序
            printf("[Parent] Parent's PID is %d\n",getpid());
            // pf(getpid(),5,0.3);
            wait(NULL);
            // printf("k=%d\n",++k);
            pid_t id_parent=fork();
            if(id_parent==-1) // PID == -1 代表 fork 出錯
                {
                    perror("fork()");
                    exit(-1);
                }
                else if(id_parent==0)// PID == 0 代表是子程序
                        printf("[*Child] Child's PID is   %d\n",getpid());
            else// PID > 0 代表是父程序
                    printf("[*Parent] Parent's PID is %d\n",getpid());
    }
    printf("------------------------------Complete\n");
    // exit(0);
}