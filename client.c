#include "client.h"

int connect_to_server(char ip[STDSIZE], int port, int *cts_socket)
{
	int		connect_status;
	struct	sockaddr_in server_sockaddr;

	printf("Trying to connect to %s:%d\n", ip, port);

	*cts_socket = socket(AF_INET, SOCK_STREAM, 0);

	server_sockaddr.sin_family		= AF_INET;
	server_sockaddr.sin_port		= htons(port);
	server_sockaddr.sin_addr.s_addr	= inet_addr(ip);
	
	connect_status = connect(*cts_socket, (struct sockaddr *) &server_sockaddr, sizeof(server_sockaddr));
	
	if (connect_status != 0)
	{
		printf("Couldn't connect to the IP and PORT provided.\n");
		return -1;
	}

	printf("Connected to server.\n");
		
	return 0;
}

int custom_request(int *socket, int request)
{
	int send_status;

	while (request < 0)
	{
		printf("Custom request: ");
		scanf("%d", &request);
	}

	send_status = send(*socket, &request, sizeof(request), 0);
	
	if (send_status == -1)
	{
		printf("Error while sending the custom request.");
		return -1;
	}
	
	printf("Sent %d %d/%lu\n", request, send_status, sizeof(request));

	return 0;
}

int disconnect(int *socket)
{	
	if(!socket) return -1;

	custom_request(socket, 404);

	return 0;
}

int get_response(int *socket)
{
	int response;

	recv(*socket, &response, sizeof(response), MSG_WAITALL);
	printf("Server responded with code [%d]", response);
	
	return response;
}
