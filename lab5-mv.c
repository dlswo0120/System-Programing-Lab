/*lab05

 Link()와 unlink() 시스템 호출을 사용하여 파일의 이름을 바꾸는 Linux의 mv 커맨드를 구현할 것 
  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "error.h"


int main(){
	int fd, len;
	int count;
	
	//file open
	fd = open("mvfile", O_RDWR|O_CREAT|O_TRUNC, 0666);
	if(fd == -1){
		printf("open error\n");
		exit(1);
	}
	//write message to mvfile
	len = write(fd,"mv mvfile newmvfile!",20);
	if(len != 20)perror("write");
	
	//link 
	if(count = (link("mvfile", "newmvfile")) < 0 ){
		printf("link error");
		exit(1);
		
	}else{
		printf("link count increases : %d\n",count); // 0
	}
	//unlink
	unlink("mvfile");
	close(fd);
	
	//Retry file open
	fd = open("mvfile",O_RDWR);
	if(fd == -1)perror("open2");
	close(fd);
	return 0;
}


