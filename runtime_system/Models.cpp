/*
 * Models.cpp
 *
 *  Created on: 14 Dec 2015
 *      Author: enpower
 */


#include "Models.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

void Models::readModel(std::string file_name) {


	std::ifstream infile(file_name.c_str());

	std::string line;

	int model_flag     = 0;
	int exe_time_flag  = 0;
	int pl_power_flag  = 0;
	int ps_power_flag  = 0;
	int mem_power_flag = 0;

	while (std::getline(infile, line))
	{
	    if (line.find("<models") != std::string::npos) {
	    	model_flag = 1;
	    }

	    if (line.find("</models>") != std::string::npos) {
	    	model_flag = 0;
	    }

	    if (line.find("<exe_time") != std::string::npos) {
	    	exe_time_flag = 1;
	    }
	    if (line.find("</exe_time>") != std::string::npos) {
	    	exe_time_flag = 0;
	    }

	    if (line.find("<pl_power") != std::string::npos) {
	    	pl_power_flag = 1;
	    }
	    if (line.find("</pl_power>") != std::string::npos) {
	    	pl_power_flag = 0;
	    }

	    if (line.find("<ps_power") != std::string::npos) {
	    	ps_power_flag = 1;
	    	std::istringstream iss(line);
	    	std::string name;
	    	std::string type;
	    	std::string equ;
	    	iss >> name >> type >> equ >> ps_power_model_type;
	    	//std::cout << "ps_model_type = " << ps_model_type << std::endl;
	    }
	    if (line.find("</ps_power>") != std::string::npos) {
	    	ps_power_flag = 0;
	    }

	    if (line.find("<mem_power") != std::string::npos) {
	    	mem_power_flag = 1;
	    	std::istringstream iss(line);
	    	std::string name;
	    	std::string type;
	    	std::string equ;
	    	iss >> name >> type >> equ >> mem_power_model_type;
	    	//std::cout << "mem_model_type = " << mem_model_type << std::endl;
	    }
	    if (line.find("</mem_power>") != std::string::npos) {
	    	mem_power_flag = 0;
	    }

	    if (line.find("<a0>") != std::string::npos) {
	    	std::getline(infile, line);
	    	std::istringstream iss(line);
	    	if (exe_time_flag) {
	    		iss >> time_a0;
	    		//std::cout << "time_a0 = " << time_a0 << std::endl;
	    	}

	    	if (pl_power_flag) {
	    		iss >> pl_power_a0;
	    		//std::cout << "pl_power_a0 = " << pl_power_a0 << std::endl;
	    	}

	    	if (ps_power_flag) {
	    		iss >> ps_power_a0;
	    		//std::cout << "ps_power_a0 = " << ps_power_a0 << std::endl;
	    	}

	    	if (mem_power_flag) {
	    		iss >> mem_power_a0;
	    		//std::cout << "mem_power_a0 = " << mem_power_a0 << std::endl;
	    	}

	    }

	    if (line.find("<a1>") != std::string::npos) {
	    	std::getline(infile, line);
	    	std::istringstream iss(line);
	    	if (exe_time_flag) {
	    		iss >> time_a1;
	    		//std::cout << "time_a1 = " << time_a1 << std::endl;
	    	}

	    	if (pl_power_flag) {
	    		iss >> pl_power_a1;
	    		//std::cout << "pl_power_a1 = " << pl_power_a1 << std::endl;
	    	}

	    	if (ps_power_flag) {
	    		iss >> ps_power_a1;
	    		//std::cout << "ps_power_a1 = " << ps_power_a1 << std::endl;
	    	}

	    	if (mem_power_flag) {
	    		iss >> mem_power_a1;
	    		//std::cout << "mem_power_a1 = " << mem_power_a1 << std::endl;
	    	}

	    }

	    if (line.find("<a2>") != std::string::npos) {
	    	std::getline(infile, line);
	    	std::istringstream iss(line);
	    	if (exe_time_flag) {
	    		iss >> time_a2;
	    		//std::cout << "time_a2 = " << time_a2 << std::endl;
	    	}

	    	if (pl_power_flag) {
	    		iss >> pl_power_a2;
	    		//std::cout << "pl_power_a2 = " << pl_power_a2 << std::endl;
	    	}

	    }


	}


	read_XG_from_file();
	x = x_max;




	g_index = g_index_max();
	v = 1.0;

}
void Models::init() {
	x = x_max;
	v_min = 0.85;

	v=1;

	g_index = g_index_max();

	f_factor_min = 10;
	f_factor = f_factor_min;
	f_factor_max = 100;
}

float Models::power() {

	float p = pl_power() + ps_power() + mem_power();
	return p;
}

float Models::pl_power() {
	float pl_power_model=0;
	float f = 1000.0/f_factor;
	int g = g_vector[x-1][g_index];
	pl_power_model = pl_power_a0*v+pl_power_a1*x*v*v*f+pl_power_a2*x*g*v*v*f;

	return pl_power_model;
}


float Models::ps_power() {
	float ps_power_model=0;
	float f = 1000.0/f_factor;
	float u = U/100;
	int g=g_vector[x-1][g_index];
	if (ps_power_model_type == 1)
		ps_power_model = ps_power_a0+ps_power_a1*u/(f*g*x);
	if (ps_power_model_type == 2)
		ps_power_model = ps_power_a0+ps_power_a1*(f*g*x)/u;
	if (ps_power_model_type == 3)
		ps_power_model = 1/(ps_power_a0+ps_power_a1*(f*g*x)/u);
	if (ps_power_model_type == 4)
		ps_power_model = 1/(ps_power_a0+ps_power_a1*u/(f*g*x));

	return ps_power_model;

}


float Models::mem_power() {
	float mem_power_model=0;
	float u = U/100;
	float f = 1000.0/f_factor;
	int g=g_vector[x-1][g_index];
	if (mem_power_model_type == 1)
		mem_power_model = mem_power_a0+mem_power_a1*u/(f*g*x);
	if (mem_power_model_type == 2)
		mem_power_model = mem_power_a0+mem_power_a1*(f*g*x)/u;
	if (mem_power_model_type == 3)
		mem_power_model = 1/(mem_power_a0+mem_power_a1*(f*g*x)/u);
	if (mem_power_model_type == 4)
		mem_power_model = 1/(mem_power_a0+mem_power_a1*u/(f*g*x));

	return mem_power_model;
}

float Models::time() {
	float t;
	float f = 1000.0/f_factor;
	float u = U/100;
	int g=g_vector[x-1][g_index];
	t = time_a0/u+time_a1/(u*x*f) + time_a2/(u*x*g*f);
	return t;

}

float Models::energy() {
	return power()*time();
}

float Models::targetObject() {
	//return energy();
	return energy()*time()*time();
}

int Models::find_f_factor_min() {
	std::string line;
	std::ifstream myfile ("max_freq.txt");
	f_factor_max = 0;
	if (myfile.is_open()) {
		while ( getline (myfile,line) ) {
			std::istringstream iss(line);
			std::string SDEPCX;
			int         sdepcx;

			std::string SDEPCG;
			int         sdepcg;

			std::string VOLTAGE;
			float       vol;

			std::string MAX_FREQ_FACTOR;
			int         max_freq_factor;

			std::string EQUAL_TOKEN;
			std::string COMMA_TOKEN;

			iss >> SDEPCX >> EQUAL_TOKEN  >> sdepcx >> COMMA_TOKEN;
			iss >> SDEPCG >> EQUAL_TOKEN  >> sdepcg >> COMMA_TOKEN;
			iss >> VOLTAGE >> EQUAL_TOKEN >> vol >> COMMA_TOKEN;
			iss >> MAX_FREQ_FACTOR >> EQUAL_TOKEN >> max_freq_factor;
			int g = g_vector[x-1][g_index];
			if (sdepcx == x && sdepcg == g && fabs(vol - v) < 0.01) {
				f_factor_max = max_freq_factor;
			}
	    }
	    myfile.close();
	}
	return f_factor_max;
}

float Models::g_index_max() {
	return g_vector[x-1].size()-1;
}


void Models::read_XG_from_file() {
	std::string line;
	std::ifstream myfile ("max_freq.txt");
	f_factor_max = 0;
	if (myfile.is_open()) {
		while ( getline (myfile,line) ) {
			std::istringstream iss(line);
			std::string SDEPCX;
			int         sdepcx;

			std::string SDEPCG;
			int         sdepcg;

			std::string VOLTAGE;
			float       vol;

			std::string MAX_FREQ_FACTOR;
			int         max_freq_factor;

			std::string EQUAL_TOKEN;
			std::string COMMA_TOKEN;

			iss >> SDEPCX >> EQUAL_TOKEN  >> sdepcx >> COMMA_TOKEN;
			iss >> SDEPCG >> EQUAL_TOKEN  >> sdepcg >> COMMA_TOKEN;
			iss >> VOLTAGE >> EQUAL_TOKEN >> vol >> COMMA_TOKEN;
			iss >> MAX_FREQ_FACTOR >> EQUAL_TOKEN >> max_freq_factor;


			int find_flag = 0;
			for (unsigned int i = 0; i < g_vector[sdepcx-1].size(); i++) {
				if (g_vector[sdepcx-1][i] == sdepcg) {
					find_flag = 1;
				}
			}
			if (find_flag == 0) {
				g_vector[sdepcx-1].push_back(sdepcg);
			}
	    }
	    myfile.close();
	}

	x_max = 1;
	for (unsigned int i = 0; i < 5; i++) {
		if ( g_vector[i].size() > 0 )
			x_max = i+1;
	}
}
