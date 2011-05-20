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
#include <poll.h>

#define TEST_HOST "theturks.sytes.net"
#define TEST_PORT 57157

extern int sockfd;
extern struct sockaddr_in server_addr;
extern struct pollfd net_read;
extern struct pollfd net_write;

void init_network(void);
int recv_message(char *buffer);
int send_message(char *buffer);

#endif
