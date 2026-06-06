#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <pthread.h>
#include "serverHeader.h"
#include "../Shared/sharedHeader.h"

//Receiving a type of Pokemon from the client:
void receiveQuery(threadArgs* args) {
	int bytesRcv;
	char buffer[30];
	bytesRcv = recv(args -> clientSocket, buffer, sizeof(buffer) - 1, 0);
	if (bytesRcv < 0) {
		printf("There was a problem receiving a type of Pokemon in \"mainA.\"\n");
	}
	buffer[bytesRcv] = '\0';
	if (args -> numTypes >= args -> typeCapacity) {
		args -> typeCapacity += 50;
		char (*temp)[25];
		temp = realloc(args -> type1s, args -> typeCapacity * sizeof(*(args -> type1s)));
		if (temp == NULL) {
			printf("There was a problem re-allocating memory for \"data -> type1s.\"\n");
			return;
		}
		args -> type1s = temp;
	}
	strncpy(args -> type1s[args -> numTypes], buffer, sizeof(args -> type1s[args -> numTypes]) - 1);
	args -> type1s[args -> numTypes][sizeof(args -> type1s[args -> numTypes]) - 1] = '\0';
	args -> numTypes++;
}

//Adding "pokemon" structures to a dynamic array in the "array" structure:
int addPokemon(array *arr, pokemon *new_pokemon) {
	int C_OK = 0;
	int C_NOK = -1;
	if (arr -> size >= arr -> capacity) {
		int newCapacity = arr -> capacity * 2;
		pokemon **temp = realloc(
			arr -> elements, 
			newCapacity * sizeof(pokemon *)
		);

		if (temp == NULL) {
			return C_NOK;
		}
		arr -> elements = temp;
		arr -> capacity = newCapacity;
	}
	arr -> elements[arr -> size] = new_pokemon;
	arr -> size++;
  	return C_OK;
}

//Checking if "pokemon.csv" can be opened for reading and sending a status update to the client:
void fileCheck(threadArgs *args) {
	int bytesRcv;
	int bytesSent;
	char buffer[300];
	//Receiving a filename:
	bytesRcv = recv(args -> clientSocket, buffer, sizeof(buffer) - 1, 0);
	if (bytesRcv < 0) {
		printf("There was a problem receiving the file name.");
	}
	buffer[bytesRcv] = '\0';

	FILE* file = fopen(buffer, "r");
    	if (file == NULL) {
		strcpy(buffer, "The server failed to access the file.");
	} else {
		strcpy(args -> csvFile, buffer);
		fclose(file);
		strcpy(buffer, "The server confirms access to the file.");
	}
	bytesSent = sendAll(args -> clientSocket, buffer, strlen(buffer)); 
	if (bytesSent <= 0) {
		printf("There was a problem sending a message to the client.\n");
	}
}

//Removing consecutive commas from a line of text:
void removeConsecutiveCommas(char *str) {
    int len = strlen(str);
    int i, j;

    for (i = 0, j = 0; i < len; i++) {
        if (str[i] != ',' || (str[i] == ',' && str[i + 1] != ',')) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}



