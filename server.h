#ifndef CLIENT_H_
#define CLIENT_H_

// Include

	// Standard
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	// Sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

	// Threads
#include <pthread.h>

// Define
#define STDSIZE 1024

// Functions
void * start_listen();
char * get_ip_addr(struct sockaddr_storage);
int start_server(int, int *);
void respond_with_code(int *, int);

// Structs

#endif // CLIENT_H_
