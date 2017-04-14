#ifndef ICP_ACCEL_H
#define ICP_ACCEL_H

#define MAX_SCAN 500
#define MAX_DATA_SIZE    1000

#define LASERRAYS 361
#define POPULATION 2000 //me 1000 kalo, std 5000 arketo-15000 elafra veltiwsi alla poli argo
#define ANAPOSO 10 //15 std, 18-20 ginetai me bestf=40, 30 genies, 3000 population
#define DIASPORA 20//20
#define DIASPORAANGLE 30000.0//30000.0
#define DIASPORAANGLEdiv2 15000.0//30000.0
#define DIASPORAANGLEPLUS 0.16667
//10000.0/DIASPORAANGLE/2

#define d_LASERANG 180.0
#define d_LASERANGRAD 3.14159265
#define d_LASERMAX 8.30//7.30

#define ocgd 0.07 //0.03

#define EXPANSION 300				//me ti rithmisi gia gwnies kales kai 3000 population, 6 anaposo, 20,30000 diaspores kai 0.2 gwnia kalo 						//alla kanei lathos stis eutheies (0.07 ocgd) xwris 90-270

//me 90-270 x10 kai allagmenoi oi rithmoi xrwmatismou-kalitero stin eutheia xeirotero stis 							//gwnies

struct point{
	int x, y;
	float theta;
	float thetacos;
	float thetasin;
	float getDist(const point &p);
	void transform(point *p, int dx, int dy, float theta);
};

struct laserScan{
	float scan[LASERRAYS];
	point p[LASERRAYS];
};


struct transformation{
	int dx, dy;
	float theta;
	const transformation & operator+=(const transformation &op2);
	void clear(void);
};

struct pair{
	point p1, p2;
};

struct person{
	transformation t;
	float fitness;
};

struct laserScanLog{
	laserScan scans[MAX_SCAN];
	int size;
};

//#define MAP_SIZE 1000000

typedef unsigned long long int u64;

struct double_unsigned_char_data{
	unsigned char a[8];
/*
    unsigned char a0;
 	unsigned char a1;
	unsigned char a2;
	unsigned char a3;
	unsigned char a4;
	unsigned char a5;
	unsigned char a6;
	unsigned char a7;
*/
};
typedef union wide_data_type{
	struct double_unsigned_char_data unsigned_char_data;
	u64                              data;

}WIDE_DATA_TYPE;


#define LFSR_WIDTH 32

void initialisePopulation_hw(void);

#pragma SDS data zero_copy(map_sw[0:(MAX_SCAN*MAX_SCAN)], p_x[0:LASERRAYS], p_y[0:LASERRAYS])
void runIteration_hw(
	unsigned char             map_sw[MAX_SCAN*MAX_SCAN],
	//u64            map_sw[MAX_SCAN*MAX_SCAN/8],

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
#endif

