#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
typedef struct{
	double x,y;
}point;
point zero={0.0,0.0};
double calDistance(point a,point b){
	return sqrt(pow((a.x-b.x),2.0)+pow((a.y-b.y),2.0));
}
double d_rand()
{
	double min=-1.0,max=1.0;
    double scale = rand() / (double) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}
bool inCircle(point tPoint){
	return calDistance(zero,tPoint)<=1.0;
}
int main(int argc, char *argv[])
{
	srand(time(NULL));
	int tid,i,numInCircle=0;
	int numPoints=atoi(argv[1]);
	if (argc != 2) {
		fprintf(stderr,"usage: a.out <integer value>\n");
		return -1;
	}
	#pragma omp parallel for private(tid)
	for(i=0;i<numPoints;i++){
		point tmpPoint={d_rand(),d_rand()};
		if(inCircle(tmpPoint)){
			numInCircle+=1;
		}
	}
	printf("%lf\n",4.0*(double)numInCircle/(double)numPoints);
	return 0;
}