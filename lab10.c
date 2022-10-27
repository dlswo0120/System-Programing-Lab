#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
//lab10.c
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
		printf("Parent: Waiting for children\n");
		printf("----------------------------------\n");
	
		
		printf("Parent: Second Child wait(%d)\n",pid[1]);
		//waitpid pid[1] 
		waitpid(pid[1], &status, 0);
		//good terminated
		if(WIFEXITED(status)){
			printf("good terminated\n");
			printf("return value %d\n",WEXITSTATUS(status));
		}
		else if(WIFSIGNALED(status)){//get signaled
			printf("get signaled \n");
			printf("siganl number %d\n",WTERMSIG(status));
		}
		printf("----------------------------------\n");
		printf("Parent: First Child wait(%d)\n",pid[0]);
		
		//waitpid pid[0]
		waitpid(pid[0], &status, 0);
		//good terminated
		if(WIFEXITED(status)){
			printf("good terminated\n");
			printf("return value %d\n",WEXITSTATUS(status));
		}
		else if(WIFSIGNALED(status)){//get signaled
			printf("get signaled \n");
			printf("siganl number %d\n",WTERMSIG(status));
		}	
	}
	exit(0);
	return 0;
}
