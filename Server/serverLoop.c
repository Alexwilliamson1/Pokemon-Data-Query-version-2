#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include "serverHeader.h"
#include "../Shared/sharedHeader.h"

void *clientHandler(void *arg) {
	threadArgs *args = arg;
	args -> numTypes = 0;
	args -> typeCapacity = 50;
	args -> type1s = malloc(args -> typeCapacity * sizeof(*(args -> type1s)));
	if (args -> type1s == NULL) {
		close(args -> clientSocket);
		free(args);
		return NULL;
	}
	char buffer[300];
	int bytesRcv;
	bool endLoop = false;

	//Counting connected clients:
	if (pthread_mutex_lock(&lock) != 0) {
		printf("\nThere was a problem locking the mutex.\n");
	}
	activeClients++;
	if (pthread_mutex_unlock(&lock) != 0) {
		printf("\nThere was a problem unlocking the mutex.\n");
	}
	
	//Confirming access to "pokemon.csv" with the client:	
	fileCheck(args);
	//Responding to client requests:
	while (!endLoop) {
		//Receiving a client user's input (a, b, or c):
		bytesRcv = recv(args -> clientSocket, buffer, sizeof(buffer), 0);
		if (bytesRcv <= 0) {
			printf("There was a problem receiving a letter option.\n");
			endLoop = true;
			break;
		}
		buffer[bytesRcv] = '\0';

		if (strcmp(buffer, "a") == 0) {
			//Receiving and saving a Pokemon type:
			receiveQuery(args);
			//Sending query results to the client:
			response(args);
		} else if (strcmp(buffer, "b") == 0) {
			//Continuing while the client creates a new file:
			continue;
		} else if (strcmp(buffer, "c") == 0) {
			//Disconnecting with the client:
			endLoop = true;
		}
	}

	if (pthread_mutex_lock(&lock) != 0) {
		printf("\nThere was a problem locking the mutex.\n");
	}
	activeClients--;
	if (activeClients == 0) {
		close(args -> serverSocket);
		endProgram = true;
	}
	if (pthread_mutex_unlock(&lock) != 0) {
		printf("\nThere was a problem unlocking the mutex.\n");
	}

	//Closing the client's socket and freeing memory:
	close(args -> clientSocket);
       	printf("Client's status: disconnected.\n");
	free(args -> copiedPokemon);	
	free(args -> type1s);
	free(args);
	return NULL;
}




