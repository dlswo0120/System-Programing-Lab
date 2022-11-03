/*
<lab11>
아래와 같은 프로그램을 작성하라 : 
아래의 signal handle(int_handler(int sig))를  등록/호출한다
Parent 프로세스는 child 프로세스를 fork()한다
Child 프로세스는 while(1)을 실행한다(사실상 infinite loop 실행)
Parent는 kill system call을 사용하여 child에게 SIGINT 시그널을 보낸다
시그널을 받은 child 는 종료 status 값을 가지고 exit 한다 
Parent는 wait 시스템 호출을 이용하여 child의 종료를 기다린다. 종료하는 child에 대하여 WIFEXITED 매크로를 호출하여 정상종료인지 확인하고, WEXITSTATUS 매크로를 호출하여 종료 status 값을 출력한다.  
 
void int_handler(int sig) {
    safe_printf("Process %d received signal %d\n", getpid(), sig);
    exit(0);
}

*/

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
