#include "net.h"

void init_network(void)
{
	int port, opts;
	struct hostent *server;

	char *host = TEST_HOST;
	port = TEST_PORT;

	memset(&server_addr, '\0', sizeof(server_addr));

	sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if((server = gethostbyname(host)) == NULL)
	{
		perror("gethostbyname() failed");
		return;
	}
	
	memcpy(&server_addr.sin_addr, server->h_addr_list[0], server->h_length);
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(port);

}

int recv_message(char *buffer)
{
	int n;

	if(sockfd <= 0)
	{
		return;
	}

	n=recv(sockfd,buffer,strlen(buffer),0);
	return n;
}

int send_message(char *buffer)
{
	int n;
	int saddr_len = sizeof(server_addr);

	if(sockfd <= 0)
	{
		return;
	}

	n = sendto(sockfd,buffer,strlen(buffer),0,&server_addr,saddr_len);
	return n;
}
