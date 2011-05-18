#include "net.h"

void init_network(void)
{
	int port, opts;
	struct hostent *server;

	char *host = TEST_HOST;
	port = TEST_PORT;

	memset(&server_addr, 0, sizeof(server_addr));

	if((sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) <= 0)
	{
		perror("socket() failed");
		return;
	}

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
		return -1;
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
		return -1;
	}

	n = sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)&server_addr,(socklen_t)saddr_len);
	return n;
}
