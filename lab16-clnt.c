#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#define NAME "socket"

//lab16-clnt.c
int main(){
	int sock,length,tolen;
	struct sockaddr_un name, to;
	char buf[1024] = "";
	
	length = sizeof(struct sockaddr_un);
	tolen = sizeof(struct sockaddr_un);
	sock = socket(PF_UNIX, SOCK_DGRAM, 0);
	name.sun_family = PF_UNIX;
	strcpy(name.sun_path, NAME);
	
//	bind(sock,(struct sockaddr*)&name,length);
	printf("socket->%s\n",NAME); 
	fgets(buf, 1024, stdin);
	printf("sendto-> %s\n",buf);
	sendto(sock,buf,1024,0,(struct sockaddr*)&name,tolen);

	unlink(NAME);
	close(sock);
}
