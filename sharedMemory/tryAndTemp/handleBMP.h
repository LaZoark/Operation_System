#ifndef HANDLEBMP_H_INCLUDED
#define HANDLEBMP_H_INCLUDED

/*
    Image handling http://capricorn-liver.blogspot.com/2010/11/cbmp.html
*/

/*  
BMP檔案格式，由bmpheader與image array兩個部份組成。
bmp header通常長度為58byte，所以也可以值些忽略前面的部份，讀取影像的資料，
但是為了寫回電腦時還是一樣是bmp檔，所以還是需要把header記下來，
先宣告一個結構(struct)來存放header資料，
*/
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
記住gcc有資料格式對齊的考量，為了到時後讀檔方便，
所以加入__attribute__((packed,aligned(1)))，強制gcc把結構作緊密排列，
這樣是為了到時候讀取資料時可以直接使用指標來擺放資料，就不需要一筆一筆去指定資料。
*/


#endif // HANDLEBMP_H_INCLUDED
