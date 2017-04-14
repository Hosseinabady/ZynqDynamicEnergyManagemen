/*
 * Please Add your accelerator function in this file
 *
 */

#include "sharpen.h"


void sharpen(DATA_TYPE*   memory,
             u32      input_image_offset,
		     u32      output_image_offset,
		     u32      block_id,
		     u32      block_size,
		     u32      number_of_blocks);






void sharpen_8DU(  volatile DATA_TYPE*   memory_0,
		           volatile DATA_TYPE*   memory_1,
				   volatile DATA_TYPE*   memory_2,
				   volatile DATA_TYPE*   memory_3,

				   volatile DATA_TYPE*   memory_4,
				   volatile DATA_TYPE*   memory_5,
				   volatile DATA_TYPE*   memory_6,
				   volatile DATA_TYPE*   memory_7,

		           volatile u32      input_image_offset,
				   volatile u32      output_image_offset
				){
#pragma HLS INTERFACE s_axilite register port=return bundle=control_bus
#pragma HLS INTERFACE s_axilite port=input_image_offset bundle=control_bus
#pragma HLS INTERFACE s_axilite port=output_image_offset bundle=control_bus
#pragma HLS INTERFACE m_axi port=memory_0
#pragma HLS INTERFACE m_axi port=memory_1
#pragma HLS INTERFACE m_axi port=memory_2
#pragma HLS INTERFACE m_axi port=memory_3

#pragma HLS INTERFACE m_axi port=memory_4
#pragma HLS INTERFACE m_axi port=memory_5
#pragma HLS INTERFACE m_axi port=memory_6
#pragma HLS INTERFACE m_axi port=memory_7
#pragma HLS DATAFLOW


	sharpen((DATA_TYPE*)memory_0, input_image_offset/sizeof(DATA_TYPE), output_image_offset/sizeof(DATA_TYPE),  0, IMAGE_HEIGHT/8, 8);
	sharpen((DATA_TYPE*)memory_1, input_image_offset/sizeof(DATA_TYPE), output_image_offset/sizeof(DATA_TYPE),  1, IMAGE_HEIGHT/8, 8);

	sharpen((DATA_TYPE*)memory_2, input_image_offset/sizeof(DATA_TYPE), output_image_offset/sizeof(DATA_TYPE),  2, IMAGE_HEIGHT/8, 8);
	sharpen((DATA_TYPE*)memory_3, input_image_offset/sizeof(DATA_TYPE), output_image_offset/sizeof(DATA_TYPE),  3, IMAGE_HEIGHT/8, 8);

	sharpen((DATA_TYPE*)memory_4, input_image_offset/sizeof(DATA_TYPE), output_image_offset/sizeof(DATA_TYPE),  4, IMAGE_HEIGHT/8, 8);
	sharpen((DATA_TYPE*)memory_5, input_image_offset/sizeof(DATA_TYPE), output_image_offset/sizeof(DATA_TYPE),  5, IMAGE_HEIGHT/8, 8);

	sharpen((DATA_TYPE*)memory_6, input_image_offset/sizeof(DATA_TYPE), output_image_offset/sizeof(DATA_TYPE),  6, IMAGE_HEIGHT/8, 8);
	sharpen((DATA_TYPE*)memory_7, input_image_offset/sizeof(DATA_TYPE), output_image_offset/sizeof(DATA_TYPE),  7, IMAGE_HEIGHT/8, 8);

}



void sharpen(DATA_TYPE*   memory,
             u32      input_image_offset,
		     u32      output_image_offset,
		     u32      block_id,
		     u32      block_size,
		     u32      number_of_blocks) {
#pragma HLS DATAFLOW

	DATA_TYPE lineBuffer[MASK_HEIGHT][IMAGE_WIDTH+2*(MASK_WIDTH/2)];
	DATA_TYPE        outputBuffer[IMAGE_WIDTH];
	int   mask_start;
	int   mask_end;
	int   input_offset;
	int   output_offset;

	const DATA_TYPE mask[MASK_WIDTH*MASK_HEIGHT] = {   0, -1,  0,
				                                  -1,  5, -1,
												   0, -1,  0
		                                       };

	for (int row = 0; row < block_size+2*(MASK_HEIGHT/2); row++) {
		if(row == 0) {
			if (block_id == 0)
				input_offset = 0;
			else
				input_offset  = (block_id*block_size - (MASK_HEIGHT/2))*IMAGE_WIDTH;
			output_offset = block_id*block_size*IMAGE_WIDTH;;
			mask_start = 0;
			mask_end   = MASK_WIDTH - 1;
		}


		memcpy(lineBuffer[mask_end]+(MASK_WIDTH/2),(DATA_TYPE *)(memory+input_image_offset+input_offset),(IMAGE_WIDTH)*sizeof(DATA_TYPE));

		DATA_TYPE left_padding  = lineBuffer[mask_end][(MASK_WIDTH/2)];
		DATA_TYPE right_padding = lineBuffer[mask_end][(IMAGE_WIDTH-1)+(MASK_WIDTH/2)];

		for (int i = 0; i < (MASK_WIDTH/2); i++) {
#pragma HLS PIPELINE II=1
//	#pragma HLS UNROLL
			lineBuffer[mask_end][i] = left_padding;
			lineBuffer[mask_end][IMAGE_WIDTH+(MASK_WIDTH/2)+i] = right_padding;
		}

		for (int col= 0; col < (IMAGE_WIDTH); col++) {
	#pragma HLS PIPELINE II=1
//	#pragma HLS UNROLL factor=1
			DATA_TYPE sum = 0;

			for (int msk_col = 0; msk_col < MASK_WIDTH; msk_col++)
				for (int msk_row = 0; msk_row < MASK_HEIGHT; msk_row++) {

					DATA_TYPE msk    = mask[msk_row * MASK_WIDTH + msk_col];
					DATA_TYPE in_img = lineBuffer[(mask_start + msk_row)% MASK_WIDTH][col+msk_col];

					sum += msk * in_img;
				}

			outputBuffer[col]= sum;
		}
		mask_end   = ++mask_end   % MASK_WIDTH;
		mask_start = ++mask_start % MASK_WIDTH;

		if (row >= 2*(MASK_WIDTH/2))
			memcpy((DATA_TYPE *)(memory+output_image_offset+output_offset), (DATA_TYPE *)(outputBuffer), (IMAGE_WIDTH)*sizeof(DATA_TYPE));

		if (number_of_blocks == 1) {
			if (    (block_id == 0 && row >= (MASK_WIDTH/2) && row < (IMAGE_HEIGHT-1)+(MASK_WIDTH/2) )
						   )
				input_offset  += IMAGE_WIDTH;
			}else {
				if (    (block_id == 0 && row >= (MASK_WIDTH/2) ) ||
						(block_id > 0 && block_id < (number_of_blocks - 1)) ||
						(block_id == (number_of_blocks - 1) && row < (block_size-1)+(MASK_WIDTH/2))
					)
					input_offset  += IMAGE_WIDTH;
			}

		if (row >= 2*(MASK_WIDTH/2))
			output_offset += IMAGE_WIDTH;
	}

}
