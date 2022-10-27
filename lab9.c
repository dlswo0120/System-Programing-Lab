#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
//lab9.c
int main(){
	int status;
	
	pid_t pid[2];
	pid[0] = fork();
	
	if(pid[0] == -1){
		perror("fork failed");
		exit(1);
	}
	else if(pid[0] == 0){ // child

		execl("/bin/echo", "echo","This is child1",(char*)0);

	}
	else{//parent
		pid[1] = fork();
		if(pid[1] == -1){
			perror("fork failed");
			exit(1);
		}
		else if(pid[1] == 0){ // child
			execl("/bin/echo", "echo","This is child2",(char*)0);
		}
		printf("Parent: Waiting for children");
		printf("----------------------------------\n");
		int stat_val;
		

		wait(&stat_val);// wait 1
		if(WIFSIGNALED(status)){
			printf("get signal\n");
			printf("signal number: %d\n",WTERMSIG(status));
		}
		wait(&stat_val);//  wait 2
		
		if(WIFEXITED(stat_val)){
			printf("Parent: All Children terminated");
		}
		else
			printf("child terminated abnormally\n");
			
	}
	
	return 0;
}
