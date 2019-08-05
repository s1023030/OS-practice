/*
Add -fopenmp while compiling the code 
*/

#include <stdio.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM_THREADS 10
#define COUNT_TIME 1
long long int sum=0;
long long int partSum[MAX_NUM_THREADS] = {0};

void calSum(int numToSum,int numOfThreads);
int main(int argc, char *argv[])
{
	clock_t start,end;
	double time=0.0;
	int numToSum=atoi(argv[1]);
	int i,j;

	if (argc != 2) {
		fprintf(stderr,"usage: a.out <integer value>\n");
		return -1;
	}
	if (numToSum < 0) {
		fprintf(stderr,"%d must be >= 0\n",numToSum);
		return -1;
	}
    omp_set_dynamic(0);
	for(i=1;i<=6;i++){
		start = clock();
		for(j=0;j<COUNT_TIME;j++){
			calSum(numToSum,i);
		}
		end = clock();
		time= (end - start)/(double)(CLOCKS_PER_SEC);
		printf("Using %d threads.\n",i);
		printf("sum = %lld .\n",sum);
		printf("Using %lf .\n",time);
		printf("==========================\n");
	}
	return 0;
}
void calSum(int numToSum,int numOfThreads){
	int i,tid,lower[numOfThreads],upper[numOfThreads];
	int interval=numToSum/numOfThreads;
    omp_set_num_threads(numOfThreads);
	sum=(long long int)0;
	for(i=0;i<numOfThreads;i++){
		partSum[i] = 0;
		if(i==0){
            lower[i]=1;
            upper[i]=interval;
        }
        else if(i==numOfThreads-1){
            lower[i]=(i*interval)+1;
            upper[i]=numToSum;
        }
        else{
            lower[i]=(i*interval)+1;
            upper[i]=(i+1)*interval;
        }
	}
    #pragma omp parallel for private(tid)
	for(i=0;i<numOfThreads;i++){
		int j,now=i;
		for(j=lower[now];j<=upper[now];j++){
			partSum[now]+=(long long int)j;
		}
	}
	for(i=0;i<numOfThreads;i++){
		sum += partSum[i];
	}
}
