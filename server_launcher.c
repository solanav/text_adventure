#include "server.h"

int main()
{
	int server_socket;
	int thread1_status;

	pthread_t thread1;

	start_server(9090, &server_socket);
	thread1_status = pthread_create(&thread1, NULL, start_listen, &server_socket);
	
	if (thread1_status != 0)
	{
		printf("Failed to start listening thread.\n");
		return -1;
	}

	printf("Now listening for clients.\n");

	while (1)
	{
		
	}

	pthread_join(thread1, NULL);

	return 0;
}
