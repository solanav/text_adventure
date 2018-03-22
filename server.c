#include "server.h"

void * start_listen(int *server_socket)
{
	socklen_t len;
	struct sockaddr_storage addr;
	int client_socket, code;

	len = sizeof addr;

	restart:

	listen(*server_socket, 50);
	client_socket = accept(*server_socket, (struct sockaddr*)&addr, &len);
	
	printf("[%s] connected to the server...\n", get_ip_addr(addr));

	while (1)
	{
		recv(client_socket, &code, sizeof(code), MSG_WAITALL);
		
		printf("[%s] sent code [%d]\n", get_ip_addr(addr), code);
		
		if (code == 404) break;
	}
	
	goto restart;
	
	return NULL;
}

char *get_ip_addr(struct sockaddr_storage addr)
{
	struct sockaddr_in *s;
	s = (struct sockaddr_in *) &addr;
	return inet_ntoa(s->sin_addr);
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
