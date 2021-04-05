#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
void SIGFPE_Handler(int);
int main()
{
    int a, b;
    if (signal(SIGFPE, SIGFPE_Handler) == SIG_ERR)
    {
        perror("Set up signal handler error!");
        abort();
    }
    printf("If you divided some integer by 0,\nit can start the signal handler..\n");
    printf("Now we can input two integers for division.\n");
    scanf("%d %d", &a, &b);
    printf("%d / %d = %d\n", a, b, a / b);
}
void SIGFPE_Handler(int signum)
{
    printf("Signal: %d\n", signum);
    perror("Division error!\a");
    abort();
}
