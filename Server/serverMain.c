//Including the libraries:
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "serverHeader.h"
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../Shared/sharedHeader.h"

//Initializing global variables:
pthread_mutex_t lock;
int activeClients = 0;
bool endProgram = false;

int main() {
	pthread_mutex_init(&lock, NULL);
	printf("This is the server for Pokemon Data Query.  Use a client to send requests for data.\n\n");
			
	int serverSocket;
	struct sockaddr_in clientAddress;
	socklen_t addrSize; 
	bool terminate;
	//Configuring the sockets using transmission control protocol (TCP):
	socketSetup(&serverSocket);
	//Accepting incoming client socket connections and running a thread for each connected client:
	while(1) {
		addrSize = sizeof(clientAddress);
		int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &addrSize);
		pthread_mutex_lock(&lock);
		terminate = endProgram;
		pthread_mutex_unlock(&lock);

		if (clientSocket < 0) {
			if (terminate) {
				break;
			}
			continue;
		}
		
		printf("Client's status: connected.\n");	
		
		threadArgs *args = malloc(sizeof(threadArgs));
		if (args == NULL) {
			close(clientSocket);
			break;
		}
		args -> clientSocket = clientSocket;
		args -> serverSocket = serverSocket;

		pthread_t thread;
		if (pthread_create(&thread, NULL, clientHandler, args) != 0) {
			close(clientSocket);
			free(args);
			continue;
		}
		pthread_detach(thread);
	}
	//Destroying the mutex:
	pthread_mutex_destroy(&lock);
	printf("Server's status: shutting down.\n");
	return 0;
}





