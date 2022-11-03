#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>


//lab11.c
int main(){
	pid_t pid;
	pid = fork();
	if(pid < 0){
		perror("fork failed");
		exit(1);
	}
	else if(pid == 0){
		execlp("child.c", "child.c",(char*)0);
	}
	else{
		printf("parent: child initiated\n");
		sleep(10);
		if(!kill(pid,SIGTERM)) //kill child
			perror("kill");
		printf("parent: child terminated\n");
		
	}
	return 0;
}
