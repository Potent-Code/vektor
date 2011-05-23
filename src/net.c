#include "net.h"

int sockfd;
struct sockaddr_in server_addr;
struct pollfd net_read;
struct pollfd net_write;

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

	if((server = gethostbyname2(host,AF_INET)) == NULL)
	{
		perror("gethostbyname2() failed");
		return;
	}
	
	memcpy(&server_addr.sin_addr, server->h_addr_list[0], server->h_length);
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(port);
	net_read.fd = sockfd;
	net_read.events = POLLIN;
	net_read.revents = 0;
	net_write.fd = sockfd;
	net_write.events = POLLOUT;
	net_write.revents = 0;
}

int recv_message(char *buffer)
{
	int n;
	int saddr_len = sizeof(server_addr);

	if(sockfd <= 0)
	{
		return -1;
	}
	// check if data is ready to be recieved
	if(poll(&net_read, 1, 50) > 0)
	{
		n = recvfrom(sockfd,buffer,150,0,(struct sockaddr *)&server_addr,&saddr_len);
	}
	else
	{
		return -1;
	}
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

	if(poll(&net_write,1, 50) > 0)
	{
		n = sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)&server_addr,(socklen_t)saddr_len);
	}
	return n;
}
