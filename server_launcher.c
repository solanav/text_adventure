#include "server.h"

int main()
{
	int server_socket;
	int thread1_status, thread2_status;

	pthread_t thread1, thread2;

	start_server(9090, &server_socket);
	thread1_status = pthread_create(&thread1, NULL, start_listen, &server_socket);
	thread2_status = pthread_create(&thread2, NULL, start_listen, &server_socket);
	
	if (thread1_status != 0 || thread2_status != 0)
	{
		printf("Failed to start listening to one of the threads.\n");
		return -1;
	}

	printf("Now listening for both clients.\n");

	while (1)
	{
		/* This needs a better way to be done */	
	}

	pthread_join(thread1, NULL);

	return 0;
}
