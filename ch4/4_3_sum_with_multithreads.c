#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int sum=0;
int numOfThreads=5;
struct thread_data {
    int start;
    int end;
};
void *runner(void *param);
int main(int argc, char *argv[])
{
	pthread_t tid[numOfThreads]; 
	pthread_attr_t attr[numOfThreads];
	int numToSum=atoi(argv[1]);
	struct thread_data* thread_array = malloc(numOfThreads * sizeof(struct thread_data));
	if (argc != 2) {
		fprintf(stderr,"usage: a.out <integer value>\n");
		return -1;
	}
	if (atoi(argv[1]) < 0) {
		fprintf(stderr,"%d must be >= 0\n",atoi(argv[1]));
		return -1;
	}
	if (atoi(argv[1]) < numOfThreads) {
		fprintf(stderr,"Arg must be >= %d\n",numOfThreads);
		return -1;
	}
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
	printf("sum = %d\n",sum);
	return 0;
}
void *runner(void *param)
{
	int lower=((struct thread_data*) param) -> start, upper= ((struct thread_data*) param) -> end;
	int i;
	for (i = lower; i <= upper; i++)
		sum += i;
	pthread_exit (0);
}