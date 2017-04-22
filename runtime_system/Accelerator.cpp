/*
 * Accelerator.cpp
 *
 *  Created on: 14 Dec 2015
 *      Author: enpower
 */


#include "Accelerator.h"


Accelerator::Accelerator():x(0), g_index(0), f_factor(0), v(0) {
	}

Accelerator::Accelerator(Accelerator &a) {
		this->x = a.x;
		this->g_index = a.g_index;
		this->f_factor = a.f_factor;
		this->v = a.v;
	}

Accelerator::Accelerator(int x_, int g_i, float f_fac, float v_): x(x_), g_index(g_i), f_factor(f_fac), v(v_) {}

void Accelerator::update(int x_, int g_i, float f_fac, float v_) {
	x = x_;
	g_index = g_i;
	f_factor = f_fac;
	v = v_;
}
