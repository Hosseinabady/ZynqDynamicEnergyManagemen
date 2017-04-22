/*
 * sdepc.cpp
 *
 *  Created on: 11 Dec 2015
 *      Author: enpower
 */

//#define TIMING_CONSTRAINT
#include "sdepc.h"

Sdepc::Sdepc() {
}


Sdepc::Sdepc(std::string file_name) {
	readModel(file_name);
	active_accelerator.update(x, g_index, find_f_factor_min(), 1.0);
	// TODO Auto-generated constructor stub

}

Sdepc::~Sdepc() {
	// TODO Auto-generated destructor stub
}


void Sdepc::setThreadId(unsigned int tid) {
	thread_id = tid;
}

unsigned int Sdepc::getThreadId() {
	return thread_id;
}

void Sdepc::setActiveAccelerator(Accelerator acc) {
	this->active_accelerator = acc;
}
Accelerator Sdepc::getActiveAccelerator() {
	return this->active_accelerator;
}



void Sdepc::monitorSystem() {
/*
	std::ostringstream os_tid;
	//os_tid << thread_id;

	os_tid << 23435; //just for debugging




	std::string pid = os_tid.str();
	std::string command("perf stat -t ");
	command = command + pid + " sleep 1";


	redi::ipstream proc(command, redi::pstreams::pstderr);
	std::string line;
	std::cout << "command  : " <<command << '\n';

	// read child's stdout
	while (std::getline(proc.out(), line)) {
	//	std::cout << "line  : " <<line << '\n';
		std::size_t found = line.find( "CPUs utilized");

		if (found!=std::string::npos) {
		//			std::cout << "stdout: " << line << '\n';

			const char* p;
			p = strtok( (char*)line.c_str(), " \t" );
			p = strtok( NULL, " \t" );
			p = strtok( NULL, " \t" );
			p = strtok( NULL, " \t" );
			p = strtok( NULL, " \t" );

			char* pEnd;
			thread_cpu_util = strtod (p, &pEnd);
			std::cout << "cpu utilization : " << thread_cpu_util << '\n';
		}
	}
	//only for debugging
*/

	std::cout << " enter maximum execution time = ";
	std::cin >> target_maximum_exe_time;

	std::cout << " enter CPU utilization = ";
	std::cin >> thread_cpu_util;
}



void Sdepc::optimisation(){
//	init();

	int x_group = x_max;
	x = x_group;
	int g_index_group=g_index_max();
	g_index = g_index_group;
	int v_group = 1;
	v = v_group;
	int f_factor_group = find_f_factor_min();

	x = x_group;
	g_index = g_index_group;
	v = v_group;
	f_factor = f_factor_group;
	U = thread_cpu_util;


	int flag = 0;
	//throughput synthesis
	float O = targetObject();
	float normal_energy = O;
	float Onew = O;

//find the best bitstream
	for (int i_x = 0; i_x < x_max; i_x++) {
		x = i_x+1;
		for (int i_g = 0; i_g < g_index_max(); i_g++) {

			g_index = i_g;
			v = 1;
			f_factor = find_f_factor_min();
			Onew = targetObject();
			if(x == 1 && g_vector[x-1][g_index] == 6)
				std::cout << "energy_1_6 = " << Onew << std::endl;
			float exe_time = time();
			if (Onew < O
#ifdef TIMING_CONSTRAINT
					&& (exe_time < target_maximum_exe_time)
#endif// TIMING_CONSTRAINT
) {
				O = Onew;
				x_group = x;
				g_index_group=g_index;
				v_group = v;
				f_factor = f_factor_group;

			}
		}
	}

	std::cout << " U_group = " << U<< std::endl;
	std::cout << " X_group = " << x_group  << std::endl;
	std::cout << " g_index_group = " << g_index_group << std::endl;
	std::cout << " G_group = " << g_vector[x_group-1][g_index_group] << std::endl;
	std::cout << " V_group = " << v_group << std::endl;
	std::cout << " f_factor_group = " << f_factor_group << std::endl;


//find the best voltage and frequency

	x = x_group;
	g_index = g_index_group;
	v = 1;
	f_factor = find_f_factor_min();

	O = targetObject();
	//voltage scaling
	flag = 0;
	Onew = O;
	while(((Onew <= O) || (fabs(Onew-O) < TOLERANCE_ERROR_DELTA))
	#ifdef TIMING_CONSTRAINT
				&& (time() < target_maximum_exe_time)
	#endif// TIMING_CONSTRAINT
			  ) {
			v = v - 0.01;
			flag = 1;
			if (v < v_min)
				break;
			f_factor = find_f_factor_min();
			Onew = targetObject();

		}
		if (flag == 1)
			v = v + 0.01;

		f_factor = find_f_factor_min();

		O = targetObject();

		//frequency scaling
		flag = 0;
		Onew = O;
		while(((Onew <= O) || (fabs(Onew-O) < TOLERANCE_ERROR_DELTA))
	#ifdef TIMING_CONSTRAINT
				&& (time() < target_maximum_exe_time)
	#endif// TIMING_CONSTRAINT
			  ) {
			f_factor = f_factor + 1;

			flag = 1;
			if (f_factor > f_factor_max)
				break;
			Onew = targetObject();
		}
		if (flag == 1) {
			f_factor = f_factor - 1;
		}

		std::cout << " U = " << U << std::endl;
		std::cout << " X = " << x << std::endl;
		std::cout << " G = " << g_vector[x-1][g_index] << std::endl;
		std::cout << " V = " << v << std::endl;
		std::cout << " f_factor = " << f_factor << std::endl;
		std::cout << " f = " << 1000.0/f_factor << std::endl;
		std::cout << " efficieny = " << (normal_energy-Onew)/normal_energy  << std::endl;



/*
	int flag = 0;
	//throughput synthesis
	float O = targetObject();
	float Onew = O;
	while(((Onew <= O) || (fabs(Onew-O) < TOLERANCE_ERROR_DELTA))
#ifdef TIMING_CONSTRAINT
			&& (time() < target_maximum_exe_time)
#endif//#ifdef TIMING_CONSTRAINT
	) {
		x = x - 1;
		flag = 1;
		if (x == 0)
			break;
		g_index=g_index_max();
		f_factor = find_f_factor_max();
		Onew = targetObject();
	}
	if (flag == 1)
		x = x+1;

	g_index = g_index_max();
	f_factor = find_f_factor_max();
	O   = targetObject();

	//logic synthesis
	Onew = O;
	flag = 0;
	while(((Onew <= O) || (fabs(Onew-O) < TOLERANCE_ERROR_DELTA))
#ifdef TIMING_CONSTRAINT
			&& (time() < target_maximum_exe_time)
#endif //TIMING_CONSTRAINT
		  ) {
		g_index=g_index - 1;
		flag = 1;
		if (g_index == -1) {
			g_index = 0;
		    flag = 0;
		    break;
		}
		f_factor = find_f_factor_max();
		Onew = targetObject();
	}
	if (flag == 1)
		g_index = g_index + 1;
	f_factor = find_f_factor_max();
	O = targetObject();
		//voltage scaling
	flag = 0;
	Onew = O;
	while(((Onew <= O) || (fabs(Onew-O) < TOLERANCE_ERROR_DELTA))
#ifdef TIMING_CONSTRAINT
			&& (time() < target_maximum_exe_time)
#endif// TIMING_CONSTRAINT
		  ) {
		v = v - 0.01;
		flag = 1;
		if (v < v_min)
			break;
		f_factor = find_f_factor_max();
		Onew = targetObject();

	}
	if (flag == 1)
		v = v + 0.01;

	f_factor = find_f_factor_max();

	O = targetObject();

	//frequency scaling
	flag = 0;
	Onew = O;
	while(((Onew <= O) || (fabs(Onew-O) < TOLERANCE_ERROR_DELTA))
#ifdef TIMING_CONSTRAINT
			&& (time() < target_maximum_exe_time)
#endif// TIMING_CONSTRAINT
		  ) {
		f_factor = f_factor + 1;

		flag = 1;
		if (f_factor > f_factor_max)
			break;
		Onew = targetObject();
	}
	if (flag == 1) {
		f_factor = f_factor - 1;
	}



	std::cout << " U = " << U << std::endl;
	std::cout << " X = " << x << std::endl;
	std::cout << " G = " << g_vector[x-1][g_index] << std::endl;
	std::cout << " V = " << v << std::endl;
	std::cout << " f_factor = " << f_factor << std::endl;
	std::cout << " f = " << 1000.0/f_factor << std::endl;

	std::cout << " exe_time = " << time() << std::endl;
	std::cout << " energy = " << energy() << std::endl;
	*/
}



void Sdepc::reconfigurePL() {

	if (x != active_accelerator.x || g_index != active_accelerator.g_index ) {

		std::string command("cat ");

		command = command + "  accelerator_X";

		std::ostringstream convertX;
		convertX << x;
		command = command + convertX.str();
		command = command + "_G";

		std::ostringstream convertG;
		convertG << g_vector[x-1][g_index];
		command = command + convertG.str();
		command = command + ".bin";

		command = command + " > /dev/xdevcfg";

		std::cout << " command  = " << command << std::endl;

//		redi::ipstream reconf_command(command, redi::pstreams::pstdout);

		std::string pid_line;
		//std::getline(reconf_command.err(), pid_line);
		std::cout << " command out = " << pid_line << std::endl;

		std::cout << " The PL reconfigured " <<  std::endl;

	}

	if (v != active_accelerator.v)  {
		float volt = v;
		std::cout << " Old voltage = " << active_accelerator.v << std::endl;
		std::cout << " New voltage = " << volt << std::endl;
		if (volt < 1.0 && volt > 0.800) {
//			set_VCCINT_voltage(v);
			std::cout << " VCCINT  voltage has changed to = " << volt << std::endl;
		}
	}

	if (f_factor != active_accelerator.f_factor)  {
		std::cout << " Old frequency = " << active_accelerator.f_factor << std::endl;
		std::cout << " New frequency = " << f_factor << std::endl;
//		frequency_set(0, f, 2);
	}

	active_accelerator.update(x, g_index, f_factor, v);
}


unsigned int Sdepc::reconfigurableRequired(){
	unsigned int rec_flag = 0;

	if (x != active_accelerator.x)
		rec_flag = rec_flag | THROUGHPUT_SCALING;
	if (g_index != active_accelerator.g_index)
		rec_flag = rec_flag | LOGIC_SCALING;

	if (v != active_accelerator.v)
		rec_flag = rec_flag | VOLTAGE_SCALING;

	if (f_factor != active_accelerator.f_factor)
		rec_flag = rec_flag | FREQUENCY_SCALING;

	return rec_flag;
}


