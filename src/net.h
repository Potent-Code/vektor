/* network communication
 * by Ryan Lucchese
 * December 21 2010 */

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

#include "log.h"

#define TEST_HOST "zeno1337.com"
#define TEST_PORT 57157

extern void init_network(void);
extern int recv_ready(void);
extern int send_ready(void);
extern int recv_message(char *buffer);
extern int send_message(char *buffer);

extern int sockfd;
extern struct sockaddr_in server_addr;
extern struct pollfd net_read;
extern struct pollfd net_write;

#endif
