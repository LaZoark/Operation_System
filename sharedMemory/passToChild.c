#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int calc(int *arr, int n) {
    int sum = 0;
    for (int i = 1; i < n; i += 2) {
        sum = sum + arr[i];
    }
    return sum;
}

int main(void) {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int n = sizeof(arr) / sizeof(arr[0]);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        printf("I am the child process\n");

        int child_sum = calc(arr, n);
        exit(child_sum);
    }
    else {
        printf("I am the parent process\n");

        int parent_sum = calc(arr, n);

        int child_sum;
        if (wait(&child_sum) == -1) {
            perror("wait failed");
        }
        else {
            printf("Sum by child: %d\n", child_sum);
        }

        printf("Sum by parent: %d\n", parent_sum);
    }

    return 0;
}