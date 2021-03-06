#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main()
{
    int fd[2];
    // create pipe descriptors
    pipe(fd);

    /* the identifier for the shared memory segment */
    int segment_id;
    /* a pointer to the shared memory segment */
    char *shared_memory;
    /* the size (in bytes) of the shared memory segment */
    const int segment_size = 4096;
    /** allocate  a shared memory segment */
    segment_id = shmget(IPC_PRIVATE, segment_size, S_IRUSR | S_IWUSR); // assigning the "id" of segment to "segment_id"
    /** attach the shared memory segment */
    shared_memory = (char *)shmat(segment_id, NULL, 0);
    printf("shared memory segment %d attached at address %p\n", segment_id, shared_memory);
    /** write a message to the shared memory segment   */
    sprintf(shared_memory, "Hi there!");

    pid_t PID = fork(); // 從呼叫 fork 開始, 會分成兩支程序多工進行
    switch (PID)
    {
    case -1: // PID == -1 代表 fork 出錯
        perror("fork()");
        exit(-1);
    case 0: // PID == 0 代表是子程序
        // child: reading only, so close the write-descriptor
		close(fd[1]);
        // now read the data (will block until it succeeds)
		read(fd[0], &shared_memory, sizeof(shared_memory));
        printf("[Child] Child's PID is %d\n", getpid());
        printf("passed content : *%s*\n", shared_memory);
        // close the read-descriptor
		close(fd[0]);
        break;
    default: // PID > 0 代表是父程序
        // parent: writing only, so close read-descriptor.
        close(fd[0]);
        // send the content on the write-descriptor.
        write(fd[1],&shared_memory,sizeof(shared_memory));
        printf("[Parent] Parent's PID is %d\n", getpid());
        /** now print out the string from shared memory */
        printf("shared content : *%s*\n", shared_memory);

        wait(NULL);
        // close the write descriptor
		close(fd[1]);
    }

    /** now detach the shared memory segment */
    if (shmdt(shared_memory) == -1)
    {
        fprintf(stderr, "Unable to detach\n");
    }
    else
    {
        /** now remove the shared memory segment */
        shmctl(segment_id, IPC_RMID, NULL);
        printf("detach was done.\n");
    }

    return 0;
}
// 把4096bytes指定給"某記憶體位置"(也就是segment_id)
// 建立一個指標(shared_memory)指向"某記憶體位置"(segment_id)
// 把"Hi there!"寫進去shared_memory所指向的segment_id
// 把指標所指向的記憶體位置之內容印出
// 切斷指標與記憶體位置的連結
// 釋放記憶體位置(segment_id)