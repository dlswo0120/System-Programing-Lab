/* <lab08>

부모 프로세스는 smple.txt에 있는 문자열의 길이 만큼 자식 프로세스들을 생성한 후, waitpid 를 사용하여 생성된 순서대로 거두어 들이는 프로그램을 작성하라. 이때?자식?프로세스는?자신의?순서만큼?문자열을?복사해서?output.txt에?작성하고?종료해야?한다.

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <error.h>
#include <fcntl.h>
#include <string.h>

//10.24 complete
#define BUFSIZE 512
int main(int argc, char *argv[]){
	int fd, fd2;
	int n; 
	char buf[BUFSIZE];
	int len, count=0;
	pid_t pid;
	
	//read sample.txt in directory
	fd = open("./sample.txt", O_RDONLY);
	if(fd == -1){
		printf("file open error\n");
		exit(1);
	}
	//create output.txt	
	fd2 = open("output.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);
	if(fd2 == -1){
		printf("file open error\n");
		exit(1);
	}
	//read -> system = n
	n = read(fd, buf, BUFSIZE);
	if(n == -1){
		perror("read failed");
		exit(1);
	}
	len = strlen(buf); // system = 6
	printf("read buf is : %s\n", buf); // print "system"
	printf("length: %d\n", len); // printf 6
	printf("------------------------\n");
	
	while(count < len ){
		pid = vfork();
		if(pid == -1){
			perror("fork failed\n");
			exit(1);
		}
		else if(pid == 0){ //child
			printf("child: %ld\n",(long)getpid());
			count++;
			if((write(fd2,buf,count)) == -1){//write  
				perror("write failed");
				exit(1);
			}
			if((write(fd2,"\n",1)) == -1){//enter
				perror("write enter failed");
				exit(1);
			}
		}
		else{
			printf("parent pid : %ld\n",(long)getpid());
		}
	}
		close(fd);
		close(fd2);
		return 0;	
}
