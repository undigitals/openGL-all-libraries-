//
//  BitmapReader.cpp
//  loadingTextures
//
//  Created by Umid Negmatullayev on 6/3/18.
//  Copyright © 2018 Umid Negmatullayev. All rights reserved.
//

#include "BitmapReader.h"
#include <stdio.h>
#include <cmath>
#include <stdlib.h>

BitmapReader::BitmapReader(char* filename){
    img =NULL;
    tagBITMAPFILEHEADER fh;
    tagBITMAPINFOHEADER infoh;
    FILE* fp = fopen(filename, "rb");
    if(!fp){
        printf("\a Failed to read file\n");
        return;
    }
    
    fread(&fh, sizeof(fh), 1, fp);
    fread(&infoh, sizeof(infoh), 1, fp);
    
    if(infoh.biBitCount !=24){
        printf("\a enter a 24 bit BMP file");
        return;
    }
    width = infoh.biWidth;
    height = abs(infoh.biHeight);
    img = new unsigned char [infoh.biSizeImage];
    
    fread (img, infoh.biSizeImage, 1, fp);
    // swap the R<->B channels
    
    unsigned char temp;
    for(int i = 0; i<infoh.biSizeImage; i++){
        temp = img[i];
        img[i] = img[i+2];
        img[i+2]=temp;
        i+=2;
    }
}


BitmapReader::~BitmapReader(){
    if(img) delete []img;
}










