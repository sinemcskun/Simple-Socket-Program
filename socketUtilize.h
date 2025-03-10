#ifndef SOCKETUTILIZE_SOCKETUTILIZE_H
#define SOCKETUTILIZE_SOCKETUTILIZE_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>



struct sockaddr_in* createIPv4Address(char *ip, int port);

int createTCPIpv4Socket();


#endif //SOCKETUTILIZE_SOCKETUTILIZE_H