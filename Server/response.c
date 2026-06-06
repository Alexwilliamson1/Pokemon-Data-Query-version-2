#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include "serverHeader.h"
#include "../Shared/sharedHeader.h"

//Sending requested data to the client:
void response(threadArgs *args) {
	int bytesSent;
	args -> copiedPokemon = pokemonArray(50);
	array *results = args -> copiedPokemon;
	char *type1 = args -> type1s[args -> numTypes - 1];
	char *csvFile = args -> csvFile;
	char line[200];
	//Opening "pokemon.csv" to be read:
	FILE* file = fopen(csvFile, "r");
    	if (file == NULL) {
		printf("There was a problem opening the file \"pokemon.csv.\"\n");
		return;
	}
	//Setting the starting position of the file read:
	fseek(file, 0, SEEK_SET);
	//Copying the fila data for a Pokemon if its Type 1 field matches the user's query:
	while (fgets(line, sizeof(line), file) != NULL) {
		//Adding query results to the "results" array:
		copy(results, type1, line);		
	}
	//Sending the size of the array of "pokemon":
	int netSize = htonl(results -> size);
	bytesSent = sendAll(args -> clientSocket, &netSize, sizeof(int));
	if (bytesSent <= 0) {
		printf("There was a problem sending the number of %s Pokemon being sent.\n", type1);
	}
	//Sending the array of "pokemon" to the client:
	for (int i = 0; i < results -> size; ++i) {
		pokemon *p = results -> elements[i];
		bytesSent = sendAll(args -> clientSocket, p, sizeof(pokemon));
		if (bytesSent <= 0) {
			printf("There was a problem sending the data for a Pokemon.\n");
		}
	}
	//Closing "pokemon.csv"::
	fclose(file);
	//Freeing the memory allocated for the "array" variable: 
  	for (int i = 0; i < results -> size; ++i) {
  		free(results -> elements[i]);
  	}
  	free(results -> elements);
}





