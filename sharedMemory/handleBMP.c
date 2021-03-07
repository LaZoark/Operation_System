#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>
#include "handleBMP.h"

/*
像這樣開始讀取檔案的58byte，直接使用unsigned char型態指標從結構開始位址開始寫入，數值就會按照位置擺入結構中。
讀完header後，取出width與height，由於一個pixel有rgb三個pixel，算影像大小的公式為width*height*3，
再與(filesize-bitmap_dataoffset)比較看看是否相等，判斷大小是否有算錯
*/
int readbmp(char *filename, lbheader hbmp, int mode, unsigned char *buffer)
{
    FILE *ifp;
    char c[128];
    unsigned char *ptr;

    sprintf(c, "/home/lazoark/Documents/OS_study/sharedMemory/%s.bmp", filename);
    ifp = fopen(filename, "rb");
    if (ifp == NULL)
    {
        printf("readbmp: file open error\n");
        return -1;
    }
    ptr = (unsigned char *)&hbmp;
    fread(ptr, sizeof(unsigned char), sizeof(lbheader), ifp);
    if (mode == 1)
    {
        fread(buffer, sizeof(unsigned char), (hbmp.width * hbmp.height * 3), ifp);
        printf("Bmp was read!\n");
    }
    else
    {
        fclose(ifp);
        return (hbmp.width * hbmp.height * 3);
    }
    fclose(ifp);
    printf("Bmp was closed.\n");
    return 1;
}

int writebmp(char *filename, lbheader hbmp, unsigned char *buffer)
{
    FILE *ofp;
    char c[128];
    unsigned char *ptr;

    sprintf(c, "/home/lazoark/Documents/OS_study/sharedMemory/%s.bmp", filename);
    ofp = fopen(c, "wb");
    if (ofp == NULL)
    {
        printf("writebmp: file open error\n");
        return -1;
    }

    ptr = (unsigned char *)&hbmp;
    fwrite(ptr, sizeof(unsigned char), sizeof(lbheader), ofp);
    printf("bmpheader was placed.\n");
    fwrite(buffer, sizeof(unsigned char), (hbmp.width * hbmp.height * 3), ofp);
    printf("image array was placed.\n");
    fclose(ofp);
    printf("NICE!!!!!!!!");
    return 1;
}
