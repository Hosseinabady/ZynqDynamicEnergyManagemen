#include "icp.h"

int main (){

	initialize_sw();

	readScans_sw((char *)"../../../scans/scans_simple_corner");

	runGA_sw();
//	runGA_hw(input_scans, map_sw);

	std::cout<<"Finished!\n";
#ifdef __OPENCV__
	cvWaitKey(0);
#endif
	return 0;
}
