#ifndef ICP_ACCEL_H
#define ICP_ACCEL_H
#define G 40

#define MAX_SCAN 500
#define MAX_DATA_SIZE    1000

#define LASERRAYS 361
#define POPULATION 4000 //me 1000 kalo, std 5000 arketo-15000 elafra veltiwsi alla poli argo
#define ANAPOSO 10 //15 std, 18-20 ginetai me bestf=40, 30 genies, 3000 population
#define DIASPORA 20//20
#define DIASPORAANGLE 30000.0//30000.0

#define DIASPORAANGLEPLUS 10000.0/DIASPORAANGLE/2

#define d_LASERANG 180.0
#define d_LASERANGRAD 3.14159265
#define d_LASERMAX 8.30//7.30

#define ocgd 0.07 //0.03

#define EXPANSION 300				//me ti rithmisi gia gwnies kales kai 3000 population, 6 anaposo, 20,30000 diaspores kai 0.2 gwnia kalo 						//alla kanei lathos stis eutheies (0.07 ocgd) xwris 90-270

//me 90-270 x10 kai allagmenoi oi rithmoi xrwmatismou-kalitero stin eutheia xeirotero stis 							//gwnies

typedef unsigned long int u32;

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









#endif

