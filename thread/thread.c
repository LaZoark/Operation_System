#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define SOURCE "Lenna.bmp"
#define DEST "new_Lenna.bmp"

static int data_size = 0;
int count = 0;

void *child(void *data_)
{
    char *d = (char *)data_;
    FILE *newfp = fopen(DEST, "wb+");
    int i=0;
    while(i<data_size)
    {
        if(i<count)
            fwrite(&d[i++], sizeof(char), 1, newfp);
    }
    // for (int i = 0; i < data_size; i++)
    //     if (i < count)
    //         fwrite(&d[i], sizeof(char), 1, newfp);
    //     else i--;
    fclose(newfp) ? perror("fclose()") : printf("Child was done.\n");
    pthread_exit(NULL); // no need to return
}

int main()
{
    FILE *file = fopen(SOURCE, "rb");
    fseek(file, 0, SEEK_END) ? perror("fseek()") : 1; // go through the file
    data_size = ftell(file);                          // tell how far it goes
    fclose(file);
    printf("Image size:%d(Bytes)\n", data_size);

    char *data = calloc(data_size, sizeof(char)); // memory allocation

    pthread_t t;

    // 建立子執行緒
    pthread_create(&t, NULL, child, (void *)data);

    FILE *fp = fopen(SOURCE, "rb");
    if (fp != NULL)
        printf("Master has read the file.\n");
    else
        perror("fopen(SOURCE)");
    char buffer;
    // printf("sizeof(buffer)=%ld\n",sizeof(buffer));
    for (int j = 0; j < data_size; j++)
    {
        fread(&buffer, sizeof(char), 1, fp);
        *(data + j) = buffer;
        count = j;
    }
    fclose(fp);
    // printf("sizeof(buffer)=%ld\n",sizeof(buffer));

    sleep(1); // wait for the data(child) ready

    pthread_join(t, NULL); // 等待子執行緒執行完成
    free(data);            // 釋放記憶體
    return 0;
}