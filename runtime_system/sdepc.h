/*
 * sdepc.h
 *
 *  Created on: 11 Dec 2015
 *      Author: enpower
 */

#ifndef SDEPC_H_
#define SDEPC_H_

#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include "pstream.h"
#include <sstream>
#include "Accelerator.h"
#include "Models.h"


#define TOLERANCE_ERROR_DELTA 0.0001


#define LOGIC_SCALING       0x0001
#define THROUGHPUT_SCALING  0x0002
#define FREQUENCY_SCALING   0x0004
#define VOLTAGE_SCALING     0x0008

class Sdepc:public Models {
private:

	unsigned int thread_id;
	float        thread_cpu_util;
	float        target_maximum_exe_time;

	Accelerator  active_accelerator;


public:
	Sdepc();
	Sdepc(std::string file_name);
	virtual ~Sdepc();

	void setActiveAccelerator(Accelerator acc);
	Accelerator getActiveAccelerator();

	void setNewAccelerator(Accelerator acc);
	Accelerator getNewAccelerator();


	void setThreadId(unsigned int tid);
	unsigned int getThreadId();


	void monitorSystem();

	void optimisation();

	void reconfigurePL();

	unsigned int reconfigurableRequired();
};

#endif /* SDEPC_H_ */
