/*
<lab16>
Socket() 시스템 호출을 이용하여 간단한 메시지를 교환하는 client/server 프로그램을 작성하라 :
Domain은 PF_UNIX, socket type은 SOCK_DGRAM, 프로토콜은 0을 이용
교환할 간단한 메시지는 “This is a message from the client”
서버 프로그램은 다음 페이지에 나와 있음
Client 프로그램을 작성할 것*/
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
