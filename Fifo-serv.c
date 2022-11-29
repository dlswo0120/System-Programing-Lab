/*
<lab15>
FIFO를 이용하여 다음과 같은 프로그램을 작성하라
Fifo-serv 프로그램에서는 “myfifo”라는 이름의 FIFO를 생성한다
Fifo-clnt 프로그램에서는 stdin으로 부터 한번에 최대 1024byte 크기의 데이터를 읽어들인 후, 데이터를 “myfifo”에 쓴다
Fifo-serv 에서 “myfifo”에 쓰여진 데이터를 읽어서 stdout에 출력한다
Mkfifo, open, close, read, write 등의 system call을 사용하면 작성할 수 있다
테스트 입력으로 다음을 사용한다 : 
This is junior-level 
System Programming course
Fall semester of year 2022
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

//lab15.c
#define BUFSIZE 1024

int main(){
	int fd;
	char buf[BUFSIZE];
	int res = mkfifo("/tmp/myfifo",0777);
	if(res == 0) printf("FIFO created\n");

	while(1){
		if( (fd = open("myfifo",O_RDWR)) == -1){
			perror("open");
			exit(1);
		}
		memset(buf,'\0',BUFSIZE);
		read(fd, buf, sizeof(buf));
		write(STDOUT_FILENO, buf, sizeof(buf));
	}
	
	close(fd);
	//exit(EXIT_SUCCESS);
	return 0;
	
	
}
