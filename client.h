#ifndef CLIENT_H_
#define CLIENT_H_

// Include
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

// Define
#define STDSIZE 1024

#define USERNAME_R 100
#define POSITION_R 101

// Functions
int connect_to_server(char *, int, int *);
int custom_request(int *, int);

int get_response(int *);

#endif // CLIENT_H_
