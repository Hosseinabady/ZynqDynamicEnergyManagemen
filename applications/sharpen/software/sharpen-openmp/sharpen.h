#ifndef __IMGCONV__H__
#define __IMGCONV__H__

#include <string.h>


#define DELAY_FOR_POWER_MEASUREMENT 10000
#define IMAGE_HEIGHT   1080 //60 //1080 //5
#define IMAGE_WIDTH    1920 //120 //1920 //5


#define MASK_HEIGHT   3
#define MASK_WIDTH    3

typedef unsigned long	u32;


#define INPUT_FILE_NAME  "image-1(1920x1080).bmp";
#define OUTPUT_FILE_NAME_SW "out_image-1-SW(1920x1080).bmp";
#define OUTPUT_FILE_NAME_HW "out_image-1-HW(1920x1080).bmp";


#define MAX_COMPUTE_DEVICE 5



#endif //__IMGCONV__H__
