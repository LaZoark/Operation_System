#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

void pf(pid_t,int,float);

int main()
{
    pid_t pid;
    /* fork a child process */
    pid = fork();
    if (pid < 0) { /* error occurred */
            fprintf(stderr, "Fork Failed\n");
            exit(-1);
    }
    else if (pid == 0) { /* child process */
            printf("I am the child %d\n",getpid());
            pf(getpid(),3,2);
            //sleep(1);
            //execlp("/bin/ls","ls",NULL);
    }
    else { /* parent process */
            /* parent will wait for the child to complete */
            printf("I am the parent %d\n",getpid());
            pf(getpid(),4,1);
            //wait(NULL);
            sleep(3);
            printf("Child Complete\n");
            //exit(0);
    }

}

void pf(pid_t proid,int no ,float tm)
{   
    for(int i=0;i<no;i++)
    {
        printf("%d:%d\n",proid,i);
        sleep(tm);
    }
}