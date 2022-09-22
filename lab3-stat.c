/*<lab03>

stat() 시스템 호출을 이용하여 파일의 정보를 출력한다 : 
주어진 하나의 파일의 inode 번호를 출력한다
해당 파일의 처음 생성 날짜/시간, 마지막으로 업데이트 된 날짜/시간, 마지막으로 접근한 날짜/시간을 출력한다

 */

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



