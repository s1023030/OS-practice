#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include<limits.h>
int calAverage(int* arr,int num){
	int i,value;
	int sum=0;
	for(i=0;i<num;i++){
		value=*(arr+i);
		sum+=value;
	}
	return (sum/num);
}

int calMax(int* arr,int num){
	int i,value;
	int max=INT_MIN;
	for(i=0;i<num;i++){
		value=*(arr+i);
		if(value>max){
			max=value;
		}
	}
	return max;
}

int calMin(int* arr,int num){
	int i,value;
	int min=INT_MAX;
	for(i=0;i<num;i++){
		value=*(arr+i);
		if(value<min){
			min=value;
		}
	}
	return min;
}

int main()
{
	int i,j;
	int num,tmpInt;
	scanf("%d",&num);
	int store[num];
	for(i=0;i<num;i++){
		scanf("%d",&tmpInt);
		store[i]=tmpInt;
	}
	
	int tid;
	#pragma omp parallel private(tid)
    {
		#pragma omp sections
		{
			#pragma omp section
			{
				printf("Average: %d\n",calAverage(store,num));
			}
			#pragma omp section
			{
				printf("Maximum: %d\n",calMax(store,num));
			}
			#pragma omp section
			{
				printf("Minimum: %d\n",calMin(store,num));
			}
		}
	}
	
	return 0;
}