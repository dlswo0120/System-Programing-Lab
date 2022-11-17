#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_SIZE 512
//lab13.c
//./a.out 

int main(int argc, char* argv[]){
        pid_t pid;
	int fd[2];
	char buf[MAX_SIZE];
	int status;
	int n;
	if(pipe(fd) < 0){
		perror("pipe");
		exit(1);
	}
	
	pid = fork();
	if(pid == -1){
		perror("fork"); //fork failed
		exit(1);
	}
	else if(pid == 0){
		//printf("child process\n");
		close(fd[1]);
		read(fd[0],buf,MAX_SIZE);
		//printf("received : %s\n",buf);
		execlp(buf,buf,"| grep","telnet",(char*)0);
	}
	else{
		//printf("parent process\n");
		close(fd[0]);
	        execlp("/bin/ps","ps","-ef",(char*)0);


		//write(fd[1],buf,sizeof(buf));
	}
	wait(&status);
	return 0;
}
