#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

void writer(const char *message,int count,FILE *stream)
{
//write the message to the stream and send it through pipe
	for(;count >0;count--)
	{
		fprintf(stream,"%s\n",message);
		fflush(stream);
		sleep(1);
	}
}

void reader(FILE *stream)
{//read out of stream and print the content on screen
	char buffer[1024];
	while(!feof(stream)&&!ferror(stream)&&fgets(buffer,sizeof(buffer),stream)!=NULL)
		fputs(buffer,stdout);

}



int main()
{
	int fds[2];
	pid_t pid;
	pipe(fds);//create the pip
	pid=fork();
	if(pid==(pid_t)0)
	{//child process
		FILE *stream;
		close(fds[1]);//close the end of write(parent process)
		stream=fdopen(fds[0],"r");
		reader(stream);
		close(fds[0]);
		
	}
	else
	{
		FILE *stream;
		close(fds[0]);
		stream=fdopen(fds[1],"w");
		writer("Hello,world",5,stream);//write "hello,world" for 5 times
		close(fds[1]);

	}
	return 0;
}
