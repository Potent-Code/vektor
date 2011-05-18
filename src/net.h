#ifndef NET_H
#define NET_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define TEST_HOST "theturks.sytes.net"
#define TEST_PORT 57157

int sockfd;
socklen_t saddr_len;
struct sockaddr_in server_addr;

void init_network(void);
int recv_message(char *buffer);
int send_message(char *buffer);

#endif
