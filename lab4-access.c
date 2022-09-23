#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <error.h>
#include <stdlib.h>

#define BUF_SIZE 512
#define PRMS 0666

int main(int argc, char *argv[]){
	int n;
	int fd;
	char buf[BUF_SIZE];
	
	if(argc !=2)
		printf("usage: a.out <pathname>");
		
	//file exist check
	if(access(argv[1], F_OK) < 0){ //file doesn't exixt
		perror("F_OK");
		
		//create new file
		fd = open(argv[1], O_RDWR | O_CREAT| O_TRUNC, PRMS);
		if(fd == -1){
			printf("file open error\n");
			exit(1);
		}
		//write "hello world" to file
		n = write(fd,"hello world",11);
		//if n < 0, then print bytes of n
		if(n < 0){
			printf("write failed : n => %d\n", n);
			exit(1);
		}
			
	}
	else{ //file exist
		printf("read access OK\n");
		//open file
		fd = open(argv[1], O_RDONLY);
		if(n == -1){
			printf("open failed\n");
			exit(1);
		}
		else{
			n = read(fd,buf,20);//read 20-byte data
			if(n == -1){//failed
				printf("read error.\n");
				exit(1);
			}
			else{//success
				printf("read bytes from file: %d\n", n);
				printf("Result output: %s\n",buf);
			}
		}
			
	}
	
	close(fd);
	return 0;
}

