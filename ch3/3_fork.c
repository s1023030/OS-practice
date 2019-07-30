#include<sys/types.h>
#include <sys/wait.h>
#include<stdio.h>
#include<unistd.h>
int main(){
	pid_t pid;
	pid = fork();
	int status;
	if(pid<0){
		fprintf(stderr,"Fork Failed");
		return 1;
	}
	else if(pid==0){
		execlp("/bin/ls","ls",NULL);
	}
	else{
		pid=wait(&status);
		if(pid==-1){
			fprintf(stderr,"Error!!\n");
			return 1;
		}
		else{
			printf("Pid %d is completed!!\n",pid);
		}
	}
	return 0;
}