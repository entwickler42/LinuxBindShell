#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main(unsigned int argc, const char* argv[])
{
	int cs,pid;
	char sch, rch;
	struct sockaddr_in server;

	if(argc != 3)
	{
		cout << "WRONG NUMBER OF PARAMETERS" << endl;
		return 0;
	}

	server.sin_family 		= AF_INET;
	server.sin_port	  		= htons(atoi(argv[2]));
	server.sin_addr.s_addr	= inet_addr(argv[1]);
	memset(server.sin_zero,0,8);

	cs = socket(AF_INET,SOCK_STREAM,0);
	if((connect(cs,(struct sockaddr*)&server,sizeof(struct sockaddr_in)))!=-1)
	{
		cout << "CONNECTED TO HOST: " << argv[1] << ":" << argv[2] << endl;
		if((pid==fork())==0) while(recv(cs,&rch,1,0)>0) cout << rch;
		else if(pid != -1) 	 while(read(0,&sch,1) > 0) send(cs,&sch,1,0);

	}else cout << "CAN NOT CONNECT HOST: " << argv[1] << ":" << argv[2] << endl;

	close(cs);
	return 0;
}
