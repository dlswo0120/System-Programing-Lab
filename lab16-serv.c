#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define NAME "socket"

//lab16-serv.c
int main(){
	int sock,length,fromlen;
	struct sockaddr_un name, from;
	char buf[1024];
	
	length = sizeof(struct sockaddr_un);
	
	sock = socket(PF_UNIX, SOCK_DGRAM, 0);
	name.sun_family = PF_UNIX;
	strcpy(name.sun_path, NAME);
	bind(sock,(struct sockaddr*)&name,length);
	printf("socket->%s\n",NAME); 
	recvfrom(sock,buf,1024,0,(struct sockaddr*)&from,&fromlen);
	printf("->%s\n",buf); //text
	
	unlink(NAME);
	close(sock);
}

