#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>
// #include "handleBMP.h"

typedef struct _lbheader{
    unsigned short identifier;      // 0x0000
    unsigned int filesize;          // 0x0002
    unsigned int reserved;          // 0x0006
    unsigned int bitmap_dataoffset; // 0x000A
    unsigned int bitmap_headersize; // 0x000E
    unsigned int width;             // 0x0012
    unsigned int height;            // 0x0016
    unsigned short planes;          // 0x001A
    unsigned short bits_perpixel;   // 0x001C
    unsigned int compression;       // 0x001E
    unsigned int bitmap_datasize;   // 0x0022
    unsigned int hresolution;       // 0x0026
    unsigned int vresolution;       // 0x002A
    unsigned int usedcolors;        // 0x002E
    unsigned int importantcolors;   // 0x0032
    unsigned int palette;           // 0x0036
} __attribute__((packed,aligned(1))) lbheader;
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
    // printf("{-buffer-size }%ld\n",sizeof(&buffer));
    sprintf(c, "/home/lazoark/Documents/OS_study/sharedMemory/%s.bmp", filename);
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
        printf("Bmp was read!\n");
    }
    else
    {
        fclose(ifp);
        // printf("mode=0\n");
        printf("[read]%d\n",hbmp.width * hbmp.height * 3);
        printf("{-buffer-size }%ld\n",sizeof(buffer));
        return (hbmp.width * hbmp.height * 3);
    }

    fclose(ifp);
    printf("Bmp was closed.\n");
    printf("{FILE size }%ld\n",sizeof(*ifp));
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
    printf("[write]%d\n",hbmp.width * hbmp.height * 3);
    printf("{FILE size }%ld\n",sizeof(*ofp));
    printf("image array was placed.\n");
    fclose(ofp);
    // printf("NICE!!!!!!!!");
    return 1;
    
}


// int main()
// {
//     // 先宣告指標與結構
//     unsigned char *bimage;
//     lbheader bmpinfo;
//     // 取得適當大小的陣列
//     bimage = (unsigned char *)malloc(sizeof(unsigned char) * readbmp("la", bmpinfo, 0, bimage));
//     // printf("sizeof(bimage)=%ld\n",sizeof(bimage));
    
//     // 讀取影像
//     readbmp("la", bmpinfo, 1, bimage);
//     // printf("sizeof(bimage)=%ld\n",sizeof(bimage));
    
//     writebmp("new_la", bmpinfo, bimage);

//     /*
// 讀取影像時要先知道影像大小，以便宣告足夠的記憶體空間，
// 所以要呼叫兩次readbmp()，一次先取到header，第二次才真的取影像資料
// */
// }