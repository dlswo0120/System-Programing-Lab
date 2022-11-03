#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>


//lab12.c
int main(){
	printf("child.c open success!\n");
	printf("go to sleep....");
	sleep(30);
}


