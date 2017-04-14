/*******************************************************************************
Vendor: Xilinx 
Associated Filename: sobel.cpp
Purpose: Sobel edge detection algorithm for AutoESL
Revision History: February 13, 2012 - initial release
                                                
*******************************************************************************
© Copyright 2008 �? 2012 Xilinx, Inc. All rights reserved. 

This file contains confidential and proprietary information of Xilinx, Inc. and 
is protected under U.S. and international copyright and other intellectual 
property laws.

DISCLAIMER
This disclaimer is not a license and does not grant any rights to the materials 
distributed herewith. Except as otherwise provided in a valid license issued to 
you by Xilinx, and to the maximum extent permitted by applicable law: 
(1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL FAULTS, AND XILINX 
HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, 
INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, OR 
FITNESS FOR ANY PARTICULAR PURPOSE; and (2) Xilinx shall not be liable (whether 
in contract or tort, including negligence, or under any other theory of 
liability) for any loss or damage of any kind or nature related to, arising under 
or in connection with these materials, including for any direct, or any indirect, 
special, incidental, or consequential loss or damage (including loss of data, 
profits, goodwill, or any type of loss or damage suffered as a result of any 
action brought by a third party) even if such damage or loss was reasonably 
foreseeable or Xilinx had been advised of the possibility of the same.

CRITICAL APPLICATIONS
Xilinx products are not designed or intended to be fail-safe, or for use in any 
application requiring fail-safe performance, such as life-support or safety 
devices or systems, Class III medical devices, nuclear facilities, applications 
related to the deployment of airbags, or any other applications that could lead 
to death, personal injury, or severe property or environmental damage 
(individually and collectively, "Critical Applications"). Customer assumes the 
sole risk and liability of any use of Xilinx products in Critical Applications, 
subject only to applicable laws and regulations governing limitations on product 
liability. 

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT 
ALL TIMES.

*******************************************************************************/

#include <stdio.h>
#include "sobel.h"
#include <hls_stream.h>

// RGB to Y Conversion 
// Resulting luminance value used in edge detection
unsigned char rgb2y(RGB pix)
{
  unsigned char y;

  y = ((66 * pix.R.to_int() + 129 * pix.G.to_int() + 25 * pix.B.to_int() + 128) >> 8) + 16;

  return y;
}

//Sobel Computation using a 3x3 neighborhood
RGB sobel_operator(WINDOW *window)
{
  short x_weight = 0;
  short y_weight = 0;

  short edge_weight;
  unsigned char edge_val;
  RGB pixel;

  char i;
  char j;


  const char x_op[3][3] = { {-1,0,1},
			    {-2,0,2},
			    {-1,0,1}};

  const char y_op[3][3] = { {1,2,1},
			    {0,0,0},
			    {-1,-2,-1}};

  //Compute approximation of the gradients in the X-Y direction
  for(i=0; i < 3; i++){
    for(j = 0; j < 3; j++){

      // X direction gradient
      x_weight = x_weight + (window->getval(i,j) * x_op[i][j]);
      
      // Y direction gradient
      y_weight = y_weight + (window->getval(i,j) * y_op[i][j]);
    }
  }
  
  edge_weight = ABS(x_weight) + ABS(y_weight);

  edge_val = (255-(unsigned char)(edge_weight));

  //Edge thresholding
  if(edge_val > 200)
    edge_val = 255;
  else if(edge_val < 100)
    edge_val = 0;

  pixel.R = pixel.G = pixel.B = edge_val;

  return pixel;
}

//Main function for Sobel Filtering
//This function includes a line buffer for a streaming implementation
void sobel_filter(AXI_PIXEL *memory_1,
				  AXI_PIXEL *memory_2,
		          u32 inter_pix_offset,
				  u32 out_pix_offset,
				  int rows,
				  int cols)  {
#pragma HLS INTERFACE s_axilite port=return bundle=control_bus
#pragma HLS INTERFACE s_axilite port=inter_pix_offset bundle=control_bus
#pragma HLS INTERFACE s_axilite port=out_pix_offset bundle=control_bus
#pragma HLS INTERFACE s_axilite port=rows bundle=control_bus
#pragma HLS INTERFACE s_axilite port=cols bundle=control_bus
#pragma HLS INTERFACE m_axi port=memory_1
#pragma HLS INTERFACE m_axi port=memory_2
  //Place the 8-bit color components in a 24-bit container. R is least significant byte

  //Create AXI streaming interfaces for the core

  cols= MAX_WIDTH;
  rows = MAX_HEIGHT;
  int row;
  int col;

  Y_BUFFER buff_A;
  RGB_BUFFER buff_B;
  WINDOW buff_C;

#pragma HLS DATAFLOW
  hls::stream<AXI_PIXEL> input_pixel_stream;
  hls::stream<AXI_PIXEL> output_pixel_stream;

  for(row = 0; row < rows; row++){
    for(col = 0; col < cols; col++){

//  for (int i = 0; i < rows*cols; i++) {
#pragma HLS PIPELINE II = 1
		input_pixel_stream << *(memory_1+inter_pix_offset+row*cols+col);
    }
  }


  for(row = 0; row < rows+1; row++){
    for(col = 0; col < cols+1; col++){
//    for (int i = 0; i < rows*cols; i++) {
#pragma HLS PIPELINE II = 1

  //  	col = i%cols;
  //  	row = i/cols;
      // Temp values are used to reduce the number of memory reads
      unsigned char temp;
      RGB tempx;
      unsigned char test_val;
      
      //Line Buffer fill
      if(col < cols){
    	  buff_A.shift_up(col);
    	  temp = buff_A.getval(0,col);
      }

      //There is an offset to accomodate the active pixel region
      //There are only MAX_WIDTH and MAX_HEIGHT valid pixels in the image
      if(col < cols & row < rows){
		RGB new_pix;
		AXI_PIXEL input_pixel_local;
		input_pixel_local = input_pixel_stream.read();
		new_pix.B = input_pixel_local & 0x000000FF;
		new_pix.G = (input_pixel_local & 0x0000FF00) >> 8;
		new_pix.R = (input_pixel_local & 0x00FF0000) >> 16;
		tempx = new_pix;
		buff_A.insert_bottom(rgb2y(tempx),col);
      }

      //Shift the processing window to make room for the new column
      buff_C.shift_right();

      //The Sobel processing window only needs to store luminance values
      //rgb2y function computes the luminance from the color pixel
      if(col < cols){
    	  buff_C.insert(buff_A.getval(2,col),0,2);
    	  buff_C.insert(temp,1,2);
    	  buff_C.insert(rgb2y(tempx),2,2);
      }
      RGB edge;

      //The sobel operator only works on the inner part of the image
      //This design assumes there are no edges on the boundary of the image
      if( row <= 1 || col <= 1 || row > (rows-1) || col > (cols-1)){
    	  edge.R = edge.G = edge.B = 0;
      }
      else{

    	  //Sobel operation on the inner portion of the image
    	  edge = sobel_operator(&buff_C);
      }

      //The output image is offset from the input to account for the line buffer
      if(row > 0 && col > 0){
    	  AXI_PIXEL output_pixel;
    	  ap_uint<8> padding = 0xff;
    	  output_pixel = padding;
    	  output_pixel = output_pixel << 8;
    	  output_pixel = output_pixel | edge.R;
    	  output_pixel = output_pixel << 8;
    	  output_pixel = output_pixel | edge.G;
    	  output_pixel = output_pixel << 8;
    	  output_pixel = output_pixel | edge.B;

    	  output_pixel_stream << output_pixel;

      }
    }
  }

    for(row = 0; row < rows; row++){
        for(col = 0; col < cols; col++){

//	for (int i = 0; i < rows*cols; i++) {
#pragma HLS PIPELINE II = 1
			*(memory_2+out_pix_offset + row*cols+col) = output_pixel_stream.read();
		}
	}
}

