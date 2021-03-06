#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, const char * argv[])
{
    char *buffer;
    FILE *picture;
    FILE *newPicture;
    struct stat st;
    long fileSize = 0;


    picture = fopen("/home/lazoark/Documents/OS_study/sharedMemory/Lenna.jpg", "rb");
    fstat(picture, &st);
    fileSize = st.st_size;
    if(fileSize > 0) {
        buffer = malloc(fileSize);

        if(read(picture, buffer, fileSize) < 0) {
            printf("Error reading file");
        }
        fclose(picture);

        newPicture = fopen("/home/lazoark/Documents/OS_study/sharedMemory/test.jpg", "wb");
        write(newPicture, buffer, fileSize);
    }
    free(buffer);
}