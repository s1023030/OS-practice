#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long int sum=0;
struct thread_data {
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
	int i;
	
	if (argc != 2) {
		fprintf(stderr,"usage: a.out <integer value>\n");
		return -1;
	}
	if (numToSum < 0) {
		fprintf(stderr,"%d must be >= 0\n",numToSum);
		return -1;
	}
	
	for(i=2;i<=6;i++){
		start = clock();
		calSum(numToSum,i);
		end = clock();
		time= (double)(end - start)/1000.0;
		printf("Using %lf second.\n",time);
		printf("==========================\n");
	}
	
	
	return 0;
}
void calSum(int numToSum,int numOfThreads){
	sum=(long long int)0;
	pthread_t tid[numOfThreads]; 
	pthread_attr_t attr[numOfThreads];
	struct thread_data* thread_array = malloc(numOfThreads * sizeof(struct thread_data));
	int i;
	int interval=numToSum/numOfThreads;
	for(i=0;i<numOfThreads;i++){
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
		pthread_attr_init(&attr[i]);
		pthread_create(&tid[i],&attr[i],runner,(void*) &thread_array[i]);
	}
	for(i=0;i<numOfThreads;i++){
		pthread_join(tid[i],NULL);
	}
	free(thread_array);
	printf("sum = %lld .\n",sum);
}
void *runner(void *param){
	int lower=((struct thread_data*) param) -> start, upper= ((struct thread_data*) param) -> end;
	int i;
	for (i = lower; i <= upper; i++){
		sum += (long long int)i;
	}
	pthread_exit (0);
}