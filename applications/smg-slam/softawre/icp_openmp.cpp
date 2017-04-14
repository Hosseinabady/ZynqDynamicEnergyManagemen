//#define __OPENCV__
//#define __SOFTWARE__
#include "icp.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdio.h>

#include <sys/time.h>
/*
extern "C" {
#include <measurement.h>
#include <set_frequency.h>
#include <monitoring.h>
}
*/
#ifdef __OPENCV__
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif
using namespace std;

double getTimestamp() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}


void refresh_hardware(int *accel_status);
int run_command(char cmd[1000]);

int *p_x;
int *p_y;
double hardware_start;
double hardware_end;
double hardware_execution_time;

double software_start;
double software_end;
double software_execution_time;


double hardware_start_one_iteration;
double hardware_end_one_iteration;
double hardware_execution_time_one_iteration;

double software_start_one_iteration;
double software_end_one_iteration;
double software_execution_time_one_iteration;


using namespace std;

laserScanLog lscans_sw;
laserScan    previous_sw;
laserScan    original_sw;
laserScan    transformed_sw;
transformation T_sw;



float  *input_scans;
int    *input_x;
int    *input_y;
float  *input_theta;

#ifdef __OPENCV__
std::string mapTitle;
IplImage *mapDisplay;
#endif

unsigned int nextScanIndex_sw;
unsigned int MAPSIZEX_sw, MAPSIZEY_sw, STARTX_sw, STARTY_sw;

person popul_sw[POPULATION];
float bestFitness_sw;
transformation bestTransformation_sw;
transformation old_sw;
transformation robotPose_sw;

float v_sw;
int flag_sw;
int flag2_sw;
float max3_sw, max4_sw, min3_sw, min4_sw;

unsigned char *map_sw;//[MAX_SCAN][MAX_SCAN];
unsigned char data_sw[MAX_DATA_SIZE];

void initialize_sw(void){


//	map_sw = (unsigned char *)sds_alloc(MAX_SCAN*MAX_SCAN*sizeof(unsigned char));
//	input_scans = (float *)sds_alloc(MAX_SCAN*LASERRAYS*sizeof(float));


	map_sw = (unsigned char *)malloc(MAX_SCAN*MAX_SCAN*sizeof(unsigned char));
	input_scans = (float *)malloc(MAX_SCAN*LASERRAYS*sizeof(float));



	robotPose_sw.dx = 0;
	robotPose_sw.dy = 0;
	robotPose_sw.theta = 0;


	MAPSIZEX_sw = MAPSIZEY_sw = 400;//724;
	STARTX_sw = STARTY_sw = 100;//362;

#ifdef __OPENCV__
	mapTitle = "Global Map";
	mapDisplay = cvCreateImage(cvSize(MAPSIZEX_sw, MAPSIZEY_sw), IPL_DEPTH_8U, 3);
	cvNamedWindow(mapTitle.c_str(), CV_WINDOW_AUTOSIZE);
#endif
	unsigned int i;
	unsigned int j;
#pragma omp for private (j)
	for (i = 0; i<MAPSIZEX_sw; i++)
		for (j = 0; j<MAPSIZEY_sw; j++)
			map_sw[i*MAX_SCAN + j] = 127;

}


void readScans_sw(char *log){
	using namespace std;
	laserScan singleScan;

	ifstream myfile(log);

	unsigned int counter;
	int k = 0;
	string num;
	while (!myfile.eof()){
		counter = 0;
		while (counter != 361){
			num.clear();
			unsigned char c = '.';
			do{
				c = myfile.get();
				num += c;
			} while (c != ',');
			num.erase(num.size() - 1, 1);
			counter++;
			istringstream snum(num);
			snum >> singleScan.scan[counter - 1];
		}
		myfile.get();
		myfile.get();

		lscans_sw.scans[k++] = singleScan;
	}
	lscans_sw.size = k;
	cout << k << " scans loaded\n";
	myfile.close();

	previous_sw = lscans_sw.scans[0];
	original_sw = lscans_sw.scans[1];

	nextScanIndex_sw = 2;
	//int max,max2=0;
	for (unsigned int i = 0; i<LASERRAYS; i++){
		previous_sw.p[i].theta = -d_LASERANGRAD / 2 + i*d_LASERANGRAD / LASERRAYS;
		previous_sw.p[i].x = previous_sw.scan[i] / ocgd*cos(previous_sw.p[i].theta);
		previous_sw.p[i].y = previous_sw.scan[i] / ocgd*sin(previous_sw.p[i].theta);
		original_sw.p[i].theta = -d_LASERANGRAD / 2 + i*d_LASERANGRAD / LASERRAYS;
		original_sw.p[i].x = original_sw.scan[i] / ocgd*cos(original_sw.p[i].theta);
		original_sw.p[i].y = original_sw.scan[i] / ocgd*sin(original_sw.p[i].theta);

	}
	transformed_sw = original_sw;

	for (int i = 0; i <lscans_sw.size; i++) {
		for (unsigned int j = 0; j<LASERRAYS; j++){
			input_scans[i*LASERRAYS + j] = lscans_sw.scans[i].scan[j];
		}
	}

}


void initialisePopulation_sw(void){
	//	srand(time(0));

	if (bestTransformation_sw.theta>0.15 || bestTransformation_sw.theta<-0.15){
		popul_sw[0].t.dx = 0;
		popul_sw[0].t.dy = 0;
		popul_sw[0].t.theta = 0;
		flag2_sw = 0;
	}
	else{
		popul_sw[0].t.dx = rand() % DIASPORA - DIASPORA / 2;
		popul_sw[0].t.dy = rand() % DIASPORA - DIASPORA / 2;
		popul_sw[0].t.theta = rand() % 10000 / DIASPORAANGLE - DIASPORAANGLEPLUS;
		flag2_sw = 1;
	}
#pragma omp for
	for (unsigned int i = 1; i<POPULATION; i++){
		popul_sw[i].t.dx = rand() % DIASPORA - DIASPORA / 2;
		popul_sw[i].t.dy = rand() % DIASPORA - DIASPORA / 2;
		popul_sw[i].t.theta = rand() % 10000 / DIASPORAANGLE - DIASPORAANGLEPLUS;
	}
}

void updateFitnesses_sw(void){
	int tempx, tempy;
	unsigned int i;
	float sinth, costh, tttx, ttty;
	transformation temp;
	bool expansionRight;


#pragma omp for
	for (i = 0; i<POPULATION; i++)	{

		popul_sw[i].fitness = 0;

		temp.dx = robotPose_sw.dx + popul_sw[i].t.dx;
		temp.dy = robotPose_sw.dy + popul_sw[i].t.dy;
		temp.theta = robotPose_sw.theta + popul_sw[i].t.theta;

		sinth = sin(temp.theta);
		costh = cos(temp.theta);
//#pragma omp parallel for default(none)
		for (unsigned int j = 0; j<LASERRAYS; j += ANAPOSO){
			expansionRight = false;
			tempx = original_sw.p[j].x;
			tempy = original_sw.p[j].y;


			tttx = tempx*costh - tempy*sinth + temp.dx;
			ttty = tempx*sinth + tempy*costh + temp.dy;


			/*			while(!expansionRight){
			expansionRight=true;
			if(tttx>=(int)(MAPSIZEX_sw-STARTX_sw)){
			expandMap_sw(0);	expansionRight=false; std::cout<<"Expand right\n";
			}
			if(tttx<=-((int)STARTX_sw)){
			expandMap_sw(2);	expansionRight=false; std::cout<<"Expand left\n";
			}
			if(ttty>=(int)(MAPSIZEY_sw-STARTY_sw)){
			expandMap_sw(1);	expansionRight=false; std::cout<<"Expand down\n";
			}
			if(ttty<=-((int)STARTY_sw)){
			expandMap_sw(3);	expansionRight=false; std::cout<<"Expand up\n";
			}
			}
			*/
			tttx += STARTX_sw;
			ttty += STARTY_sw;
			popul_sw[i].fitness += (255 - map_sw[(unsigned int)tttx*MAX_SCAN + (unsigned int)ttty]) / 255.0;

		}
		if (bestFitness_sw<popul_sw[i].fitness){
			bestFitness_sw = popul_sw[i].fitness;
			bestTransformation_sw = popul_sw[i].t;
			if ((bestTransformation_sw.theta<0.2 && bestTransformation_sw.theta>-0.2)){
				flag_sw = 1;  //0.2
			}
			else { flag_sw = 0; }
		}

	}

}

void runIteration_sw(void){
	initialisePopulation_sw();


	int counter = 0;
//#pragma omp parallel for default(none)
	for (counter = 0; counter < 19; counter++) { //while (counter<19){ //19 std, 30 kalitero mallon
		bestFitness_sw = 0;
		bestTransformation_sw.dx = bestTransformation_sw.dy = bestTransformation_sw.theta = 0;

		updateFitnesses_sw();
		fixNewGeneration_sw();
//		counter++;

	}

}

bool fixNewScans_sw(void){

	if (nextScanIndex_sw == lscans_sw.size) return true;
	previous_sw = original_sw;
	original_sw = lscans_sw.scans[nextScanIndex_sw];
	++nextScanIndex_sw;

	for (unsigned int i = 0; i<LASERRAYS; i++){
		original_sw.p[i].theta = -d_LASERANGRAD / 2 + i*d_LASERANGRAD / LASERRAYS;
		original_sw.p[i].x = original_sw.scan[i] / ocgd*cos(original_sw.p[i].theta);
		original_sw.p[i].y = original_sw.scan[i] / ocgd*sin(original_sw.p[i].theta);

	}


	transformed_sw = original_sw;
	return false;
}

void runGA_sw(void){
	bool done = false;
	unsigned int counter = 0;
	FILE *fOut;

	fOut = fopen("output.txt", "w");

	v_sw = -10000;



	old_sw.dx = old_sw.dy = old_sw.theta = 0;

	while (!done){

//		std::cout << "\n";


		runIteration_sw();

		robotPose_sw.dx += bestTransformation_sw.dx;
		robotPose_sw.dy += bestTransformation_sw.dy;
		robotPose_sw.theta += bestTransformation_sw.theta;


		old_sw.dx = bestTransformation_sw.dx;
		old_sw.dy = bestTransformation_sw.dy;
		old_sw.theta = bestTransformation_sw.theta;



		updateMapColor_sw();
		done = fixNewScans_sw();


		counter++;
#ifdef __OPENCV__
		showMap();
#endif
//		std::cout << "\nCounter: " << counter << "/" << lscans_sw.size << "\n";
	}
#ifdef __OPENCV__
	std::string outFileName = "map10.png";
	for (int i = 0; i < MAPSIZEX_sw; i++){
		for (int j = 1; j<MAPSIZEY_sw; j++){           // save array to after.txt
			fprintf(fOut, "%u", map_sw[i, j]);
			if (j == MAPSIZEY_sw - 1){
				fprintf(fOut, "\n");
			}
			else{
				fprintf(fOut, ",");
			}
		}
	}
	fclose(fOut);
#endif //__OPENCV__
	//		showMap();
	//		if(!cvSaveImage(outFileName.c_str(),mapDisplay)) printf("Could not save: %s\n",outFileName.c_str());
}

#ifdef __OPENCV__
void showMap(void){
	//To be deleted
	cvReleaseImage(&mapDisplay);
	mapDisplay = cvCreateImage(cvSize(MAPSIZEX_sw, MAPSIZEY_sw), IPL_DEPTH_8U, 3);


	CvScalar pixel;
	for (unsigned int k = 0; k<MAPSIZEX_sw; k++){
		for (unsigned int j = 0; j<MAPSIZEY_sw; j++){
			pixel.val[0] = pixel.val[1] = pixel.val[2] = map_sw[k*MAX_SCAN+j];
			cvSet2D(mapDisplay, j, k, pixel);
		}
	}

	pixel.val[0] = 0;
	pixel.val[1] = 0;
	pixel.val[2] = 255;

	unsigned int xx, yy;

	xx = robotPose_sw.dx + STARTX_sw;
	yy = robotPose_sw.dy + STARTY_sw;

	cvSet2D(mapDisplay, yy, xx, pixel);
	cvSet2D(mapDisplay, yy, xx - 1, pixel);
	cvSet2D(mapDisplay, yy, xx + 1, pixel);
	cvSet2D(mapDisplay, yy + 1, xx, pixel);
	cvSet2D(mapDisplay, yy - 1, xx, pixel);

	cvShowImage(mapTitle.c_str(), mapDisplay);
	cvWaitKey(10);
}


#endif

void fixNewGeneration_sw(void){
	popul_sw[0].t.dx = bestTransformation_sw.dx;//elitism
	popul_sw[0].t.dy = bestTransformation_sw.dy;
	popul_sw[0].t.theta = bestTransformation_sw.theta;
	unsigned int k, l;
	bool done = false;
	unsigned int coun = 0;
#pragma omp  for
	for (unsigned int i = 1; i<POPULATION / 4; i++){//elitism 2, me std 20 kalo
		popul_sw[i].t.dx = (bestTransformation_sw.dx) + rand() % DIASPORA / 2 - DIASPORA / 4;
		popul_sw[i].t.dy = (bestTransformation_sw.dy) + rand() % DIASPORA / 2 - DIASPORA / 4;
		popul_sw[i].t.theta = (bestTransformation_sw.theta) + rand() % 10000 / DIASPORAANGLE - DIASPORAANGLEPLUS;
	}

#pragma omp  for
	for (unsigned int i = POPULATION / 4; i<POPULATION / 2; i++){//elitism 2, me std 20 kalo
		popul_sw[i].t.dx = (old_sw.dx) + rand() % DIASPORA / 2 - DIASPORA / 4;
		popul_sw[i].t.dy = (old_sw.dy) + rand() % DIASPORA / 2 - DIASPORA / 4;
		popul_sw[i].t.theta = (bestTransformation_sw.theta) + rand() % 10000 / DIASPORAANGLE - DIASPORAANGLEPLUS;
	}
//#pragma omp parallel for
	for (unsigned int i = POPULATION / 2; i<POPULATION; i++){//mutation
		done = false;	coun = 0;
		while (!done){
			k = rand() % POPULATION;
			//l=rand()%POPULATION;
			if (popul_sw[k].fitness>popul_sw[i].fitness){
				popul_sw[i].t.dx = popul_sw[k].t.dx + rand() % DIASPORA / 2 - DIASPORA / 4;
				popul_sw[i].t.dy = popul_sw[k].t.dy + rand() % DIASPORA / 2 - DIASPORA / 4;
				popul_sw[i].t.theta = popul_sw[k].t.theta + rand() % 10000 / DIASPORAANGLE / 2 - DIASPORAANGLEPLUS / 2;
				done = true;
			}
			coun++;
			if (coun == 5) done = true;
		}
	}
}

void updateMapColor_sw(void){
	int R = 0;
	float TH = -d_LASERANG / 2.0;
	int dmeasure;
	while (TH<d_LASERANG / 2.0){

		int xt, yt, measid;
		measid = (TH + d_LASERANG / 2.0) / d_LASERANG*LASERRAYS;

		xt = transformed_sw.p[measid].x;
		yt = transformed_sw.p[measid].y;

		dmeasure = (int)((float)original_sw.scan[measid] / ocgd);

		while (R<d_LASERMAX / ocgd - 3){


			float xpoint, ypoint;
			xpoint = R*cos(robotPose_sw.theta + (float)measid / (float)LASERRAYS*d_LASERANGRAD - d_LASERANGRAD / 2) + robotPose_sw.dx + STARTX_sw;
			ypoint = R*sin(robotPose_sw.theta + (float)measid / (float)LASERRAYS*d_LASERANGRAD - d_LASERANGRAD / 2) + robotPose_sw.dy + STARTY_sw;
			if (dmeasure>R || (xt == 0 && yt == 0)){

				int tt = map_sw[(unsigned int)xpoint*MAX_SCAN + (unsigned int)ypoint];


				if (flag_sw == 0){

					if (tt >= 127){ tt += (255 - tt)*0.2; }//02
					else{ tt += (255 - tt)*0.05; }//005

				}
				else{
					if (tt >= 127){ tt += (255 - tt)*0.05; }//005
					else{ tt += (255 - tt)*0.02; }//002

				}


				map_sw[(unsigned int)xpoint*MAX_SCAN + (unsigned int)ypoint] = tt;
			}

			if (dmeasure + 1>R && dmeasure - 2<R){
				int tt = map_sw[(unsigned int)xpoint*MAX_SCAN + (unsigned int)ypoint];

				if (flag_sw == 1){
					if (tt >= 127){ tt += (0 - tt)*0.2; }//02
					else{ tt += (0 - tt)*0.3; }		//03				//me to default kalo stis gwnies, kako stis eutheies otan 													//einai
				}								//0.5, 0.05, 0.2, 0.01, 0.4, 0.8, 0.4, 0.8 kalitero stin 													//eutheia

				else{
					if (tt >= 127){ tt += (0 - tt)*0.4; }//04
					else{ tt += (0 - tt)*0.7; }//07

				}

				map_sw[(unsigned int)xpoint*MAX_SCAN + (unsigned int)ypoint] = tt;
			}

			R++;
		}
		TH += 1;
		R = 1;
	}
}





extern char log_file_name[1000];

int main(){

//	strcpy(log_file_name, "log_power_monitor_overhead_");
//	file_power_profile_create(log_file_name);


	int accel_status = 0;

	initialize_sw();


	readScans_sw((char *)"scans/scans_simple_corner");

#ifdef __OPENCV__
	cvWaitKey(0);
#endif
//	POWER_MONITORING_PROLOGUE();
	software_start = getTimestamp();
	runGA_sw();
	software_end = getTimestamp();
//	POWER_MONITORING_EPILOGUE();

	software_execution_time = (software_end-software_start)/(1000);
	printf("software execution time  %.6lf ms elapsed\n", software_execution_time);

	std::cout << "Finished!\n";
#ifdef __OPENCV__
	cvWaitKey(0);
#endif


	free(map_sw);
	free(p_x);
	free(p_y);

	free(input_scans);

	return 0;
}




