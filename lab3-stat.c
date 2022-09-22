#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

int main(){
	struct stat st;
	
	if(stat("testfile", &st) == -1){
		printf("failed\n");
		exit(1);
	}
	printf("inode number: %ld\n", st.st_ino);
	
	printf("\t First create time: %s", ctime(&st.st_ctime));
	printf("\t Last update time: %s", ctime(&st.st_mtime));
	printf("\t Last access time: %s", ctime(&st.st_atime));
	
	
	return 0;
}



