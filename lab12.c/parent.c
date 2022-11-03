/*
<lab12>
두 개의 프로그램 parent.c(실행 파일 이름은 parent)와 child.c(child)를 다음과 같이 작성한다 : 
parent에서는 자식 프로세스(child)를 fork()와 exec() 시스템 호출을 이용하여 시작한다
parent에서 “parent: child initiated”라고 출력한다  
child에서는 30sec 동안 sleep() 한다 
30sec가 되기 전에 parent에서 자식 프로세스에게 kill()을 사용하여 SIGTERM을 보낸다
child가 terminate된 후 parent에서 다음과 같이 출력한다 “parent: child terminated”

*/
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
