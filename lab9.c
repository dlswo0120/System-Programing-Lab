/*
<lab9>

Fork()와 wait()를 이용하여 다음의 프로그램을 작성하라:
부모 프로세스는 두 개의 자식 프로세스를 생성한다: Child 1, Child 2
각각의 자식 프로세스는 execl()을 이용하여 “echo” 커맨드를 실행하면서 “This is Child 1(또는 Child 2)”를 출력한다 
부모 프로세스는 wait() 를 실행하며 자식 프로세스들이 끝나기를 기다린다. Wait()를 실행하기 전 “Parent: Waiting for children” 하고 출력한다 
자식 프로세스들이 끝나면 부모는 “Parent: All Children terminated” 하고 출력한다


*/

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
