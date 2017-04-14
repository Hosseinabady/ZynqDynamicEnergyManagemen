#ifndef ICP_H
#define ICP_H
//#define __OPENCV__


#ifdef __OPENCV__
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif

#include "icp_accel.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <cstdlib>

void initialize_sw(void);
void updateMapColor_sw(void);
void initialisePopulation_sw(void);
void updateFitnesses_sw(void);
void transformGA_sw(const transformation &t);
void showScansGA_sw(void);
void runIteration_sw(void);
void runGA_sw(void);
bool fixNewScans_sw(void);
void updateGAMap_sw(void);
void fixNewGeneration_sw(void);
void fixLastGeneration_sw(void);
void readScans_sw(char *log);
void expandMap_sw(unsigned int id);

#ifdef __OPENCV__
void showMap(void);
#endif

#endif

