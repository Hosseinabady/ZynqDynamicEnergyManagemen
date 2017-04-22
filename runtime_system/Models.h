#ifndef __MODEL_H__
#define __MODEL_H__

#include "Accelerator.h"
#include "System.h"
#include <string>
#include <vector>
class Models:public Accelerator, public System {

public:

	float time_a0;
	float time_a1;
	float time_a2;

	float pl_power_a0;
	float pl_power_a1;
	float pl_power_a2;


	int   ps_power_model_type;
	float ps_power_a0;
	float ps_power_a1;

	int   mem_power_model_type;
	float mem_power_a0;
	float mem_power_a1;


	int   x_max;                //maximum number of ports
	std::vector<int>   g_vector[5];  // maximum number of hardware thread for each compute device

	float v_min;
	int   f_factor_max;
	int   f_factor_min;


public:

	void  readModel(std::string file_name);
	void  init();
	float power();
	float pl_power();
	float ps_power();
	float mem_power();
	float time();
	float energy();
	float targetObject();
	int   find_f_factor_min();
	float g_index_max();
	void read_XG_from_file();
};

#endif //__MODEL_H__
