#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
int server(int client_socket)
{
}

int main()
{
	int socket_fd;
	struct sockaddr_un name;
	int client_sent_quit_message;
	char *text;
	int quit=0;
	socket_fd=socket(AF_UNIX,SOCK_STREAM,0);
	name.sun_family=AF_UNIX;
	strcpy(name.sun_path,"server_socket");
	bind(socket_fd,(struct sockaddr*)&name,sizeof(name));
	listen(socket_fd,5);
//receive message when there is no quit message from client
	do
	{
		struct sockaddr_un client_name;
		socklen_t client_name_len=sizeof(client_name);
		int client_socket_fd;
		client_socket_fd=accept(socket_fd,(struct sockaddr*)&client_name,&client_name_len);
		int length;
		
		read(client_socket_fd,&length,sizeof(length));
		text=(char*)malloc(length);
		read(client_socket_fd,text,length);
		if(length!=0)printf("%s\n",text);
		quit=strcmp(text,"quit");
		free(text);
		close(client_socket_fd);
	}
	while(quit);
	close(socket_fd);
	unlink("server_socket");
	return 0;
}










