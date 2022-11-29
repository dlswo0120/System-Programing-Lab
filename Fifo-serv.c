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
