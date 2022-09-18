/*lab01

open(), close(), read(), write() 시스템 호출을 이용하여, 한 파일의 내용을 다른 파일에 복사하는 copy.c 프로그램을 작성하라

Afile의 크기가 512byte보다 작으면 한 번에 다 read()한 후 bfile에 write하고, 만약 512byte보다 크면 512byte씩 나누어서 반복하여 read(),  write()한다  
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 512
#define PRMS 0666

int main(){
	char buffer[BUFF_SIZE];
	int fda, fdb; 
	int n; 
	ssize_t nread;
	
	
	//open afile
	fda =open("afile",O_RDWR|O_CREAT|O_TRUNC, PRMS);

	if(fda == -1){ //file open check
		printf("afile open error \n");
		exit(1);
	}
	
	n = read(0,buffer,BUFF_SIZE);//read data bytes
	n = write(fda,buffer,n);//write to afile
	//afile empty check
	if(n == 0){
		printf("afile is empty\n");
		exit(1);
	}
	// afile write error check
	if(n < 0){
		printf("afile write error\n");
		exit(1);
	}
	//complete open afile and write memory
	//open bfile
	fdb =open("bfile", O_RDWR|O_CREAT|O_TRUNC, PRMS);
	if(fdb == -1){
		printf("bfile open error\n");
		exit(1);
	}
	
	if(n > BUFF_SIZE){
		while(nread = read(fda,buffer,BUFF_SIZE) > 0){
			if(n = write(fdb,buffer,nread) < 0){
				perror("write\n");
				exit(1);
			}
		}
	}		

	n = write(fdb,buffer,n);//write to bfile
	
	//bfile empty check
	if(n == 0){
		printf("bfile is empty\n");
		exit(1);
	}
	
	//write error check
	if(n < 0){
		printf("bfile write error\n");
		exit(1);
	}
	//complete open afile and write memory
	close(fda);
	close(fdb);
	return 0;
}

	
