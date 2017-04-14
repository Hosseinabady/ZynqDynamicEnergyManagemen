#define __OPENCV__
//#define __SOFTWARE__
#include "icp.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdio.h>
#include "accel.h"
#include "time.h"
#include <unistd.h>
extern "C" {
#include <measurement.h>
#include <set_frequency.h>
#include <monitoring.h>
}

#ifdef __OPENCV__
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif
using namespace std;


std::string vccint_power;
std::string vccpint_power;
std::string vcc1v5_power;
int software_selected;
void read_power();
void refresh_hardware(int *accel_status);
int run_command(char cmd[1000]);
void runIteration_hw(
		unsigned char   map_sw[MAX_SCAN*MAX_SCAN],

		int            *robotPose_dx,
		int            *robotPose_dy,
		float          *robotPose_theta,

		int            *bestTransformation_dx,
		int            *bestTransformation_dy,
		float          *bestTransformation_theta,

		int            *old_sw_dx,
		int            *old_sw_dy,
		float          *old_sw_theta,

		int             p_x[LASERRAYS],
		int             p_y[LASERRAYS]
		);


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

//#ifdef __SOFTWARE__
//	map_sw = (unsigned char *)malloc(MAX_SCAN*MAX_SCAN*sizeof(unsigned char));
//#else
	map_sw = (unsigned char *)fpgacl_malloc(MAX_SCAN*MAX_SCAN*sizeof(unsigned char));
//#endif
	input_scans = (float *)malloc(MAX_SCAN*LASERRAYS*sizeof(float));



	robotPose_sw.dx = 0;
	robotPose_sw.dy = 0;
	robotPose_sw.theta = 0;


	MAPSIZEX_sw = MAPSIZEY_sw = 400;//724;
	STARTX_sw = STARTY_sw = 100;//362;

#ifdef __OPENCV__
	mapTitle = "PL power";
	mapDisplay = cvCreateImage(cvSize(MAPSIZEX_sw, MAPSIZEY_sw), IPL_DEPTH_8U, 3);
	cvNamedWindow(mapTitle.c_str(), CV_WINDOW_AUTOSIZE);
#endif

	for (unsigned int i = 0; i<MAPSIZEX_sw; i++)
	for (unsigned int j = 0; j<MAPSIZEY_sw; j++)
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



	for (i = 0; i<POPULATION; i++)	{

		popul_sw[i].fitness = 0;

		temp.dx = robotPose_sw.dx + popul_sw[i].t.dx;
		temp.dy = robotPose_sw.dy + popul_sw[i].t.dy;
		temp.theta = robotPose_sw.theta + popul_sw[i].t.theta;

		sinth = sin(temp.theta);
		costh = cos(temp.theta);

		for (unsigned int j = 0; j<LASERRAYS; j += ANAPOSO){
			expansionRight = false;
			tempx = original_sw.p[j].x;
			tempy = original_sw.p[j].y;


			tttx = tempx*costh - tempy*sinth + temp.dx;
			ttty = tempx*sinth + tempy*costh + temp.dy;


			/*while(!expansionRight){
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
	while (counter<19){ //19 std, 30 kalitero mallon
		bestFitness_sw = 0;
		bestTransformation_sw.dx = bestTransformation_sw.dy = bestTransformation_sw.theta = 0;

		updateFitnesses_sw();
		fixNewGeneration_sw();
		counter++;

	}

}

bool fixNewScans_sw(void){
	usleep(10000);
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

#ifdef __OPENCV__
	FILE *fOut;
	fOut = fopen("output.txt", "w");
#endif
	v_sw = -10000;





	old_sw.dx = old_sw.dy = old_sw.theta = 0;
	while (!done){
//		hardware_start_one_iteration = getTimestamp();
#ifdef __OPENCV__
//		POWER_MONITORING_PROLOGUE();
#endif
//		std::cout << "\n";

//#ifdef __SOFTWARE__
//		if (counter > 50) {
//			software_selected = 1;
//			std::cout << "software selected" << std::endl;
//		}



		if (software_selected == 1) {
			runIteration_sw();
		} else {
//#else
			for (int i = 0; i <LASERRAYS; i++) {
				p_x[i] = original_sw.p[i].x;
				p_y[i] = original_sw.p[i].y;
			}

			hardware_start = getTimestamp();
//			POWER_MONITORING_PROLOGUE();
			runIteration_hw(
					map_sw,
					&robotPose_sw.dx,
					&robotPose_sw.dy,
					&robotPose_sw.theta,
					&bestTransformation_sw.dx,
					&bestTransformation_sw.dy,
					&bestTransformation_sw.theta,
					&old_sw.dx,
					&old_sw.dy,
					&old_sw.theta,
					p_x, p_y
					);
//			POWER_MONITORING_EPILOGUE();

			hardware_end = getTimestamp();
			hardware_execution_time = (hardware_end-hardware_start)/(1000);
			printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);

	}



//#endif//__SOFTWARE__

#ifdef __OPENCV__
		read_power();
#endif // __OPENCV__
		robotPose_sw.dx += bestTransformation_sw.dx;
		robotPose_sw.dy += bestTransformation_sw.dy;
		robotPose_sw.theta += bestTransformation_sw.theta;


		old_sw.dx = bestTransformation_sw.dx;
		old_sw.dy = bestTransformation_sw.dy;
		old_sw.theta = bestTransformation_sw.theta;

#ifdef __OPENCV__
		POWER_MONITORING_EPILOGUE();
#endif
		updateMapColor_sw();
		done = fixNewScans_sw();



		counter++;
#ifdef __OPENCV__
		showMap();
#endif
//		std::cout << "\nCounter: " << counter << "/" << lscans_sw.size << "\n";
//		hardware_end_one_iteration = getTimestamp();


//		hardware_execution_time_one_iteration = (hardware_end_one_iteration-hardware_start_one_iteration)/(1000);
//		printf("one iteration hardware execution time  %.6lf ms elapsed\n", hardware_execution_time_one_iteration);
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
	CvFont *font= new CvFont;
	cvInitFont(font,CV_FONT_HERSHEY_SIMPLEX ,0.3f,0.3f,1,1,1);
//	cvPutText(mapDisplay,vccint_power.c_str(),  cvPoint(10,50),font,CV_RGB(0,0,0));
//	cvPutText(mapDisplay,vccpint_power.c_str(), cvPoint(10,60),font,CV_RGB(0,0,0));
//	cvPutText(mapDisplay,vcc1v5_power.c_str(),  cvPoint(10,70),font,CV_RGB(0,0,0));
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
	for (unsigned int i = 1; i<POPULATION / 4; i++){//elitism 2, me std 20 kalo
		popul_sw[i].t.dx = (bestTransformation_sw.dx) + rand() % DIASPORA / 2 - DIASPORA / 4;
		popul_sw[i].t.dy = (bestTransformation_sw.dy) + rand() % DIASPORA / 2 - DIASPORA / 4;
		popul_sw[i].t.theta = (bestTransformation_sw.theta) + rand() % 10000 / DIASPORAANGLE - DIASPORAANGLEPLUS;
	}


	for (unsigned int i = POPULATION / 4; i<POPULATION / 2; i++){//elitism 2, me std 20 kalo
		popul_sw[i].t.dx = (old_sw.dx) + rand() % DIASPORA / 2 - DIASPORA / 4;
		popul_sw[i].t.dy = (old_sw.dy) + rand() % DIASPORA / 2 - DIASPORA / 4;
		popul_sw[i].t.theta = (bestTransformation_sw.theta) + rand() % 10000 / DIASPORAANGLE - DIASPORAANGLEPLUS;
	}

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

	strcpy(log_file_name, "log_power_monitor_overhead_");
	file_power_profile_create(log_file_name);

	software_selected = 0;
	int accel_status = 0;
//#ifndef __SOFTWARE__
	refresh_hardware(&accel_status);
//#endif
	initialize_sw();


	readScans_sw((char *)"scans/scans_simple_corner2");


	//#ifndef __SOFTWARE__
	p_x = (int *)fpgacl_malloc(LASERRAYS*sizeof(int));
	p_y = (int *)fpgacl_malloc(LASERRAYS*sizeof(int));
	//#endif

#ifdef __OPENCV__
	cvWaitKey(0);
#endif
//	POWER_MONITORING_PROLOGUE();
//	hardware_start = getTimestamp();
	runGA_sw();
//	hardware_end = getTimestamp();
//	POWER_MONITORING_EPILOGUE();

//	hardware_execution_time = (hardware_end-hardware_start)/(1000);
//	printf("hardware execution time  %.6lf ms elapsed\n", hardware_execution_time);

	std::cout << "Finished!\n";
#ifdef __OPENCV__
	cvWaitKey(0);
#endif

//#ifdef __SOFTWARE__
//	free(map_sw);
//	free(p_x);
//	free(p_y);
//#else
	fpgacl_free(map_sw);
	fpgacl_free(p_x);
	fpgacl_free(p_y);

//#endif

	free(input_scans);

	return 0;
}




void runIteration_hw(
		unsigned char   map_sw[MAX_SCAN*MAX_SCAN],

		int            *robotPose_dx,
		int            *robotPose_dy,
		float          *robotPose_theta,

		int            *bestTransformation_dx,
		int            *bestTransformation_dy,
		float          *bestTransformation_theta,

		int            *old_sw_dx,
		int            *old_sw_dy,
		float          *old_sw_theta,

		int             p_x[LASERRAYS],
		int             p_y[LASERRAYS]
		)
 {

//	printf("runIteration_hw before write\n");
	accel_write(
		map_sw,
		p_x,
		p_y,

		robotPose_dx,
		robotPose_dy,
		robotPose_theta,

		old_sw_dx,
		old_sw_dy,
		old_sw_theta,


		bestTransformation_dx,
		bestTransformation_dy,
		bestTransformation_theta
			)
;

	accel_start();
	sleep(10);  //interrupt

//	printf("runIteration_hw after write\n");
	accel_read(
			robotPose_dx,
			robotPose_dy,
			robotPose_theta,
			bestTransformation_dx,
			bestTransformation_dy,
			bestTransformation_theta);
//	printf("runIteration_hw after read\n");

 }




int run_command(char cmd[1000]) {
	FILE *pp;
	int status = 0;
	pp = popen(cmd, "r");
	if (pp != NULL) {
	    while (1) {
	      char *line;
	      char buf[1000];
	      line = fgets(buf, sizeof buf, pp);
	      if (line == NULL) break;
	      if (line[0] == 'd') printf("%s", line); /* line includes '\n' */
	    }
	    status = -1;
	}
	pclose(pp);
	return status;
}

void refresh_hardware(int *accel_status) {
	char cmd[100];

	sprintf(cmd, "chmod u+x initial.sh");
	run_command(cmd);

	sprintf(cmd, "chmod u+x clean.sh");
	run_command(cmd);

	if (*accel_status == 0) {

		printf("refresh_hardware: check point 1\n");
		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		accel_prologue();

		sprintf(cmd, "cat smg_slam_version_2.bin > /dev/xdevcfg");
		run_command(cmd);

		*accel_status = 1;

	} else {

		printf("refresh_hardware: check point 2\n");

		accel_epilogue();

		sprintf(cmd, "./clean.sh");
		run_command(cmd);

		sprintf(cmd, "./initial.sh");
		run_command(cmd);

		sprintf(cmd, "cat  smg_slam_version_2.bin > /dev/xdevcfg");
		run_command(cmd);

		accel_prologue();
	}
}


void read_power() {

	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *token;
	FILE *fp=fopen(log_file_name, "r");
	if (fp == 0) {
		printf("%s file cannot open \n", log_file_name);
		return;
	}

	while ((read = getline(&line, &len, fp)) != -1) {
		if (strstr(line, "vccint_power_average") != NULL) {
			token = strtok(line, " =");
			token = strtok(NULL, " =");
			vccint_power.assign("VCCINT = ");
			vccint_power.append(token);

		}

		if (strstr(line, "vcc1v5_power_average") != NULL) {
			token = strtok(line, " =");
			token = strtok(NULL, " =");

			std::string vcc1v5_power_string;
			vcc1v5_power_string.assign(token);
			float vcc1v5_power_value = std::stof(vcc1v5_power_string);
			vcc1v5_power_value = vcc1v5_power_value - 0.57;
			vcc1v5_power.assign("VCCP1V5 = ");
			vcc1v5_power.append(std::to_string(vcc1v5_power_value));

		}

		if (strstr(line, "vccpint_power_average") != NULL) {
			token = strtok(line, " =");
			token = strtok(NULL, " =");
			std::string vccpint_power_string;
			vccpint_power_string.assign(token);
			float vccpint_power_value = std::stof(vccpint_power_string);
			vccpint_power_value = vccpint_power_value - 0.318;

			vccpint_power.assign("VCCPINT = ");
			vccpint_power.append(std::to_string(vccpint_power_value));

		}

	}



    fclose(fp);
    fp=fopen(log_file_name, "w");
    fclose(fp);

}
