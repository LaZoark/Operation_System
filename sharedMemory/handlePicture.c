#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>
#include "handleBMP.c"

int main()
{
    // 先宣告指標與結構
    unsigned char *bimage;
    lbheader bmpinfo;
    // 取得適當大小的陣列
    bimage = (unsigned char *)malloc(sizeof(unsigned char) * readbmp("Lenna", bmpinfo, 0, bimage));
    // 讀取影像
    readbmp("la", bmpinfo, 1, bimage);

    writebmp("new_la", bmpinfo, bimage);

    /*
讀取影像時要先知道影像大小，以便宣告足夠的記憶體空間，
所以要呼叫兩次readbmp()，一次先取到header，第二次才真的取影像資料
*/
}