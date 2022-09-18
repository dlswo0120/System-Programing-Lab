/*lab02

lseek() 시스템 호출을 사용하여, 파일의 원하는 부분을 출력하도록 만든다 : 
테스트용 입력 파일“test.txt”에 “abcdefghijklmnop”를 저장한다
lseek 를 사용하여 파일의 시작에서 10개의 character를 건너뛴 후 부터의 내용을 출력한다
lseek 를 사용하여 파일의 끝에서 앞쪽으로 5개의 character를 건너뛴 후 그 내용을 출력한다*/


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <error.h>

#define PRMS 0666

int main(){
	int fd;
	int n;
	char buf[] = "abcdegfhijklmnop"; 
	
	//test.txt file open and check
	fd = open("test.txt", O_RDWR|O_CREAT|O_TRUNC, PRMS);
	if(fd == -1){
		printf("file open error\n");
		exit(1);
	}
	
	n = sizeof(buf); 
	n = write(fd, buf, n);
	
	lseek(fd,0,SEEK_SET); //file porinter set 
	
	lseek(fd, 10, SEEK_CUR);//file porinter set 
	
	n = read(fd, buf,n); 
	printf("read text.txt bytes is %d\n",n); // n = 7 = klmnop
	lseek(fd, 1,SEEK_CUR); //file porinter set 
	
	//First result print
	printf("First result: %s\n",buf);

	n = write(fd,buf,n);

	lseek(fd,-6,SEEK_END); //file porinter set 
	n = read(fd, buf,n);
	printf("read text.txt bytes is %d\n",n);// n = 6 = lmnop
	//write to test.txt 
	n = write(fd,buf,n);
	
	//Second result print
	printf("Second result: %s\n",buf); 
	
	close(fd);	
	return 0;
}

