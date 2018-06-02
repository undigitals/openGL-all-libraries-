//
//  BitmapReader.h
//  loadingTextures
//
//  Created by Umid Negmatullayev on 6/3/18.
//  Copyright © 2018 Umid Negmatullayev. All rights reserved.
//

#ifndef BitmapReader_h
#define BitmapReader_h


typedef int WORD;
typedef long DWORD;
typedef long LONG;

typedef struct tagBITMAPFILEHEADER {
    WORD  bfType;
    DWORD bfSize;
    WORD  bfReserved1;
    WORD  bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG  biWidth;
    LONG  biHeight;
    WORD  biPlanes;
    WORD  biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG  biXPelsPerMeter;
    LONG  biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;


class BitmapReader{
public:
    int height, width;
    
    BitmapReader (char* filename);
    unsigned char* ImageMatrix(){
        return img;
    }
    
    ~BitmapReader();
    
private:
    unsigned char* img;
};


#endif /* BitmapReader_h */
