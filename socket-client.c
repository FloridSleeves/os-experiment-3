#include<stdio.h>
#include<string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
void write_text(int socket_fd,const char* text)
{
	int length=strlen(text)+1;
	write(socket_fd,&length,sizeof(length));
	write(socket_fd,text,length);
	
}

int main(int argc,char * const argv[])
{
	const char* const message=argv[1];
	int socket_fd;
	struct sockaddr_un name;

	socket_fd=socket(AF_UNIX,SOCK_STREAM,0);
	name.sun_family=AF_UNIX;
	
	strcpy(name.sun_path,"server_socket");
	int res=connect(socket_fd,(struct sockaddr*)&name,sizeof(name));
	if(res==-1)
	{
		printf("Connect failed.\n");
		exit(1);
	}
	write_text(socket_fd,message);
	close(socket_fd);
	return 0; 
	
	
}





