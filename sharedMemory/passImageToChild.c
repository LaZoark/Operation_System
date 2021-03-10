#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#define SOURCE "Lenna.bmp"
#define DEST "new_Lenna.bmp"
int main()
{
    FILE *file = fopen(SOURCE, "rb");
    fseek(file, 0, SEEK_END) ? perror("fseek()") : 1; // go through the file
    int segment_size = ftell(file);                   // tell how far it goes
    fclose(file);
    printf("Shared Memory size:%d(Bytes)\n", segment_size); // which is the size of the file (bytes)
    /* a pointer to the shared memory segment */
    char *shared_memory;
    /** allocate a shared memory segment */
    const int segment_id = shmget(IPC_PRIVATE, segment_size, S_IRUSR | S_IWUSR);

    pid_t PID = fork(); // 從呼叫 fork 開始, 會分成兩支程序多工進行
    switch (PID)
    {
    case -1: // PID == -1 代表 fork 出錯
        perror("fork()");
        exit(-1);
    case 0: // PID == 0 代表是子程序
        shared_memory = (char *)shmat(segment_id, NULL, 0);
        printf("[Child]shared memory segment %d attached at address %p\n", segment_id, shared_memory);
        FILE *newfp = fopen(DEST, "wb+");
        printf("[Child] Child's PID is %d. copying the file.\n", getpid());
        for (int i = 0; i < segment_size; i++)
            fwrite(&shared_memory[i], sizeof(char), 1, newfp);
        fclose(newfp) ? perror("fclose()") : printf("Child was done.\n");
        break;
    default: // PID > 0 代表是父程序
        shared_memory = (char *)shmat(segment_id, NULL, 0);
        printf("[Parent]shared memory segment %d attached at address %p\n", segment_id, shared_memory);
        FILE *fp = fopen(SOURCE, "rb");
        if (fp != NULL)
            printf("[Parent] Parent's PID is %d. opening the file.\n", getpid());
        else
            perror("fopen(SOURCE)");
            char buffer;
        for (int j = 0; j < segment_size; j++)
        {
            
            fread(&buffer, sizeof(char), 1, fp);
            *(shared_memory + j) = buffer;
        }
        fclose(fp);
        wait(NULL);
        /** now detach the shared memory segment */
        if (shmdt(shared_memory) == -1)
            fprintf(stderr, "Unable to detach\n");
        else
        {
            /** now remove the shared memory segment */
            shmctl(segment_id, IPC_RMID, NULL);
            printf("detach was done.\n");
        }
    }

    return 0;
}
