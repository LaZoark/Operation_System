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
int readbmp(char *filename, lbheader &hbmp, int mode, unsigned char *buffer,int ddddd)
{
    FILE *ifp;
    char c[128];
    unsigned char *ptr;

    sprintf(c, "./result/%s.bmp", filename);
    ifp = fopen(c, "rb");
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
    }
    else
    {
        fclose(ifp);
        return (hbmp.width * hbmp.height * 3);
    }
    fclose(ifp);
    return 1;
}


int writebmp(char *filename, lbheader hbmp, unsigned char *buffer)
{
    FILE *ofp;
    char c[128];
    unsigned char *ptr;

    sprintf(c, "./result/%s.bmp", filename);
    ofp = fopen(c, "wb");
    if (ofp == NULL)
    {
        printf("writebmp: file open error\n");
        return -1;
    }

    ptr = (unsigned char *)&hbmp;
    fwrite(ptr, sizeof(unsigned char), sizeof(lbheader), ofp);
    fwrite(buffer, sizeof(unsigned char), (hbmp.width * hbmp.height * 3), ofp);

    fclose(ofp);
    return 1;
}

int main()
{
    lbheader hbmp;
    unsigned char *ptr;
    ptr = (unsigned char *)&hbmp;
    fread(ptr, sizeof(unsigned char), sizeof(lbheader), fp);

    // 先宣告指標與結構
    unsigned char *bimage;
    lbheader bmpinfo;
    // 取得適當大小的陣列
    bimage = (unsigned char *)malloc(sizeof(unsigned char) * readbmp("/home/lazoark/Documents/OS_study/sharedMemory/Lenna.bmp",
                                                                     bmpinfo, 0, bimage));
    // 讀取影像
    readbmp("/home/lazoark/Documents/OS_study/sharedMemory/Lenna.bmp",
            bmpinfo, 1, bimage);
/*
讀取影像時要先知道影像大小，以便宣告足夠的記憶體空間，
所以要呼叫兩次readbmp()，一次先取到header，第二次才真的取影像資料
*/
}