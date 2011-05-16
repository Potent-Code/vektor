#ifndef NET_H
#define NET_H

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>

static int sockfd;
static fd_set rd;

void init_network(void);
void recv_message(char *buffer);
void send_message(char *buffer);

#endif
