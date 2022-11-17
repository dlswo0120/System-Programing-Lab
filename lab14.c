/*
<lab14>

Popen()과 pclose()를 사용하여 “who | sort”를 실행 시킬 수 있는 프로그램을 작성하라.  

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE	 512
//lab14.c
int main(){
	int fd[2];
	pipe(fd);
	FILE* read_fp;
	FILE* write_fp;
	char buf[BUFSIZE+1];
	int chars_read;
	pid_t pid;
	int status;
	
	pid = fork();
	if(pid == -1){
		perror("fork");
		exit(1);
	}
	else if(pid == 0){//child
		close(fd[1]);
		read(fd[0],buf,sizeof(buf));
		write_fp = popen("sort","w");//"sort","w"
		if(write_fp != NULL){
			fwrite(buf, sizeof(char),strlen(buf),write_fp);
			pclose(write_fp);
			exit(EXIT_SUCCESS);	
		}
	}
	else{//parent
		close(fd[0]);
		read_fp = popen("who","r");
		if(read_fp != NULL){
			chars_read = fread(buf,sizeof(char),BUFSIZE,read_fp);
			if(chars_read > 0){
				//printf("output was:-\n%s\n",buf);
				write(fd[1],buf,sizeof(buf));
			} 
			pclose(read_fp);
		}
		
	}
	wait(&status);
	exit(EXIT_SUCCESS);
}
