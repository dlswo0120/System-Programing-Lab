#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

//lab11.c
static void int_handler(int n);

int main(){
	int status;
	pid_t pid;
	pid = fork();
	
	if(pid < 0){
		printf("fork failed");
		exit(1);
	}
	else if(pid == 0){ //child
		printf("child : %ld\n",(long)getpid());
		
		while(1){ //infinite loop
			printf("Hello world!\n");
			sleep(1);
			signal(SIGINT, int_handler);
		}
		
	}
	else{//parent
		//int stat_val;
		printf("Parent : %d\n",getppid());
		
		sleep(5);
		printf("kill system call....\n");
		kill(pid, SIGINT);
		
		wait(&status);
		if(WIFEXITED(status)){
			printf("good terminated\n");
			printf("return value %d\n",WEXITSTATUS(status));
		}
		else
			printf("Child terminated abnormally\n");
	}
	return 0;
}

void int_handler(int sig){
	printf("Process %d received signal %d\n",getpid(),sig);
	exit(0);
}
