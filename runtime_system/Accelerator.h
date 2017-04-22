#ifndef __ACCELERATOR_STATE__
#define __ACCELERATOR_STATE__


class Accelerator {

public:
	int   x;         // throughput
	int   g_index;   // logic synthesis: the index of g in the list
	int   f_factor;  // frequency
	float v;         // voltage
	
	Accelerator();

	Accelerator(Accelerator &a);
	Accelerator(int x_, int g_, float f_, float v_);
	void update(int x_, int g_, float f_, float v_);
};


#endif //__ACCELERATOR_STATE__
