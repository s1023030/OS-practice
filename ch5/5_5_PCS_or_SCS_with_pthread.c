#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM_THREADS 20
#define COUNT_TIME 1
long long int sum=0;
long long int partSum[MAX_NUM_THREADS] = {0};

struct thread_data {
	int num;
    int start;
    int end;
};
void *runner(void *param);
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
	
	for(i=1;i<=MAX_NUM_THREADS;i++){
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
	int i,scope;
	int interval=numToSum/numOfThreads;
	
	sum=(long long int)0;
	for(i=0;i<numOfThreads;i++){
		partSum[i] = 0;
	}
	pthread_t tid[numOfThreads]; 
	pthread_attr_t attr;
	struct thread_data* thread_array = malloc(numOfThreads * sizeof(struct thread_data));
	
	pthread_attr_init(&attr);
	
	if(pthread_attr_getscope(&attr,&scope)!=0){
		fprintf(stderr,"Unable to get scheduling scope\n");
	}
	else{
		if(scope==PTHREAD_SCOPE_PROCESS){			//PCS Scheduling
			printf("PTHREAD_SCOPE_PROCESS\n");
		}
		else if(scope==PTHREAD_SCOPE_SYSTEM){		//SCS Scheduling
			printf("PTHREAD_SCOPE_SYSTEM\n");
		}
		else{
			fprintf(stderr,"Illegal scope value.\n");
		}
	}
	
	// set the scheduling algorithm to SCS
	pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);
	
	for(i=0;i<numOfThreads;i++){
		thread_array[i].num=i;
		if(i==0){
			thread_array[i].start=1;
			thread_array[i].end=interval;
		}
		else if(i==numOfThreads-1){
			thread_array[i].start=(i*interval)+1;
			thread_array[i].end=numToSum;
		}
		else{
			thread_array[i].start=(i*interval)+1;
			thread_array[i].end=(i+1)*interval;
		}
		pthread_attr_init(&attr);
		pthread_create(&tid[i],&attr,runner,(void*)&thread_array[i]);
	}
	for(i=0;i<numOfThreads;i++){
		pthread_join(tid[i],NULL);
	}
	free(thread_array);
	for(i=0;i<numOfThreads;i++){
		sum+=partSum[i];
	}
}
void *runner(void *param){
	int lower=((struct thread_data*) param) -> start, upper= ((struct thread_data*) param) -> end;
	int num=((struct thread_data*) param) -> num;
	int i;
	for (i = lower; i <= upper; i++){
		partSum[num] += (long long int)i;
	}
	pthread_exit (0);
}