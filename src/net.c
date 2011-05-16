#include "net.h"

void init_network(void)
{
	int port, opts;
	struct sockaddr_in server_addr;
	struct hostent *server;

	char *host = "theturks.sytes.net";
	port=57157;

	memset(&server_addr,'\0',sizeof(server_addr));

	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	server=gethostbyname(host);
	
	server_addr.sin_family=AF_INET;
	memmove(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
	server_addr.sin_port = htons(port);

	connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));

	FD_ZERO(&rd);

	FD_SET(sockfd,&rd);

	opts = fcntl(sockfd,F_GETFL,0);
	fcntl(sockfd,F_SETFL,opts|O_NONBLOCK);
}

void recv_message(char *buffer)
{
	if(sockfd>0)
	{
		int n;
		char tmp_buff[1024];
		struct timeval tv;
		
		FD_ZERO(&rd);
		FD_SET(sockfd,&rd);
	
		memset(tmp_buff,0,sizeof(tmp_buff));
	
		tv.tv_sec = 0;
		tv.tv_usec = 1000;

		select(sockfd+1,&rd,NULL,NULL,&tv);
		n=read(sockfd,tmp_buff,sizeof(tmp_buff));
		if(n>0)
		{
			strncpy(buffer+strlen(buffer),tmp_buff,strlen(tmp_buff));
		}
	}
}

void send_message(char *buffer)
{
	int n;
	char tmp_buff[1024];
	struct timeval tv;

	if(sockfd <= 0)
	{
		return;
	}

	FD_ZERO(&rd);
	FD_SET(sockfd,&rd);

	memset(tmp_buff,0,sizeof(tmp_buff));

	tv.tv_sec = 0;
	tv.tv_usec = 1000;

	select(sockfd+1,&rd,NULL,NULL,&tv);
	n = write(sockfd,tmp_buff,sizeof(tmp_buff));
}
