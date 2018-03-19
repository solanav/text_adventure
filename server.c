#include "server.h"

void * start_listen(int *server_socket)
{
	int client_socket;
	int code;
		
	listen(*server_socket, 50);
	client_socket = accept(*server_socket, NULL, NULL);
	
	/* Main loop */
	while (1)
	{
		recv(client_socket, &code, sizeof(code), MSG_WAITALL);
		
		printf("\nCode [%d] received\n", code);
	}

	return NULL;
}

int start_server(int port, int *server_socket)
{
	int bind_status;
	struct sockaddr_in server_sockaddr;

	*server_socket = socket(AF_INET, SOCK_STREAM, 0);

	server_sockaddr.sin_family		= AF_INET;
	server_sockaddr.sin_port		= htons(port);
	server_sockaddr.sin_addr.s_addr = INADDR_ANY;

	bind_status = bind(*server_socket, (struct sockaddr *) &server_sockaddr, sizeof(server_sockaddr));
	
	if (bind_status != 0)
	{
		printf("Error when binding to localhost:%d %d\n", port, bind_status);
		return -1;
	}

	printf("Binded correctely to localhost:%d\n", port); 

	return 0;
}

void respond_with_code(int *socket, int code)
{
	send(*socket, &code, sizeof(code), 0);
}
