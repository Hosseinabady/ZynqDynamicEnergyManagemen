#ifndef __IMGCONV__H__
#define __IMGCONV__H__

#include <string.h>


#define MAX_WIDTH 1920
#define MAX_HEIGHT 1080

typedef unsigned long	u32;

// I/O Image Settings
#define INPUT_IMAGE_BASE "test_1080p"
#define OUTPUT_IMAGE_BASE "result_1080p"

#define INPUT_IMAGE "test_1080p.bmp"
#define INPUT_IMAGE_GOLDEN "result_1080p_golden.bmp"
#define OUTPUT_IMAGE "result_1080p.bmp"

#define ABSDIFF(x,y)	((x>y)? x - y : y - x)
#define ABS(x)          ((x>0)? x : -x)


typedef u32 AXI_PIXEL;

#define DATA_TYPE  AXI_PIXEL



struct ap_rgb{
   unsigned char B;
   unsigned char G;
   unsigned char R;
};


typedef ap_rgb RGB;
#endif //__IMGCONV__H__
