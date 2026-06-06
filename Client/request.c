#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include "clientHeader.h"
#include "../Shared/sharedHeader.h"

//Requesting and receiving data for one query:
void request(threadArgs* args) {
	array *data = args -> copiedPokemon;
	char buffer[80]; 
	char type[80]; 
        int sizeBuffer;	
	int netSize;
	int bytesRcv;	
	int bytesSent;
	printf("\nType a type of Pokemon.  Types include: Grass, Fire, Water, Bug, Normal, Poison, Electric, Ground, Fairy, Fighting, Psychic, Rock, Flying, Ice, Dark, Ghost, Steel, and Dragon.  Capitalize the first letter in your response.\n\n");
	int typeCheck = 0;
	while (typeCheck == 0) {
		printf("Type of Pokemon: ");
		fgets(type, sizeof(type), stdin);
		type[strcspn(type, "\n")] = '\0';
		if (strlen(type) > 0 && islower((unsigned char)type[0])) {
			type[0] = toupper((unsigned char)type[0]);
		}
		typeCheck = isType(type);
		if (typeCheck == 0) {
			printf("\nPlease type one of the types listed above.\n\n");
		} 
	}
	strcpy(buffer, type);
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
	strcpy(args -> type1s[args -> numTypes], type);
	args -> numTypes++;

	// To send a type 1 of Pokemon to the server:
	bytesSent = sendAll(args -> clientSocket, buffer, strlen(buffer));
	if (bytesSent <= 0) {
		printf("There was a problem sending a type 1.\n");
	}
	// To receive the number of Pokemon being sent:
	bytesRcv = recvAll(args -> clientSocket, &netSize, sizeof(int));
	if (bytesRcv <= 0) {
		printf("There was a problem receiving the number of Pokemon\n.");
	}
	sizeBuffer = ntohl(netSize);
	sizeBuffer = sizeBuffer + data -> size;
	if (sizeBuffer > data -> capacity) {
		pokemon **temp = realloc(data -> elements, sizeBuffer * sizeof(pokemon *));
		if (temp == NULL) {
			printf("There was a problem re-allocating memory for the \"pokemon\" in \"pokemonsArray.\"\n");
		}
		data -> elements = temp;				
		data -> capacity = sizeBuffer;
	}
	//Receiving the data for one query:
	for (int i = data -> size; i < sizeBuffer; ++i) {
		pokemon *p = malloc(sizeof(pokemon));
		bytesRcv = recv(args -> clientSocket, p, sizeof(pokemon), 0);
		if (bytesRcv <= 0) {
			printf("There was a problem receiving a Pokemon.");
			free(p);
			break;
		}
		data -> elements[i] = p;
	}
	data -> size = sizeBuffer;
}


