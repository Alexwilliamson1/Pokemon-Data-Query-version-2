#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "clientHeader.h"
#include "../Shared/sharedHeader.h"

int main() {
	threadArgs *args = malloc(sizeof(threadArgs));
	array *data = pokemonArray(50);
	args -> copiedPokemon = data;
	int clientSocket;
	int fileNamesLength = 20;
	char (*fileNames)[30] = malloc(fileNamesLength * sizeof(*(fileNames)));
	int numFiles = 0;
	bool endLoop = false;
	for (int i = 0; i < 15; i++) {
		fileNames[i][0] = '\0';
	}
	
	socketSetup(&clientSocket);
	args -> clientSocket = clientSocket;

	printf("This is the client for Pokemon Data Query, a program for looking up and saving data about Pokemon.\n");

	//Confirming that the server has access to "pokemon.csv":	
	csvFileCheck(&clientSocket);

	while (1) {
		//Creating a continuous command-line interface:
		interfaceLoop(args, &endLoop, &numFiles, fileNames, &fileNamesLength);
		if (endLoop) {
			break;
		}
  	}
	//Freeing memory, destroying the mutex, and closing the socket connection with the server:
    free(args -> type1s);	
	free(data);
	free(args);
	free(fileNames);
  	close(clientSocket);	
}
