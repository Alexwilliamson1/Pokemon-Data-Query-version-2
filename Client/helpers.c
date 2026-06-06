//Including the libraries:
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <pthread.h>
#include "clientHeader.h"
#include "../Shared/sharedHeader.h"

//Writing one "pokemon" structure to a file:
void writePokemonData(pokemon *field, FILE *file, int num) {
	fprintf(file, "%d.  ", num);
	fprintf(file, "Number: %s, ", field -> number);
	fprintf(file, "Name: %s, ", field -> name);
	fprintf(file, "Type 1: %s, ", field -> type1);
	fprintf(file, "Type 2: %s, ", field -> type2);
	fprintf(file, "Total: %s, ", field -> total);
 	fprintf(file, "HP: %s, ", field -> HP);
	fprintf(file, "Attack: %s, ", field -> attack);
	fprintf(file, "Defense: %s, ", field -> defense);
	fprintf(file, "Sp. Atk: %s, ", field -> spatk);
	fprintf(file, "Sp. Def: %s, ", field -> spdef);
	fprintf(file, "Speed: %s, ", field -> speed);
	fprintf(file, "Generation: %s, ", field -> generation);
	fprintf(file, "Legendary: %s", field -> legendary);
	fprintf(file, "\n\n");
}

//Checking if a given string is a Pokemon type in "pokemon.csv":
int isType(char *type) {
	char types[] = "Grass, Fire, Water, Bug, Normal, Poison, Electric, Ground, Fairy, Fighting, Psychic, Rock, Flying, Ice, Dark, Ghost, Steel, Dragon";
	char temp[200];
	strcpy(temp, types);
	char *token = strtok(temp, ",");
	int found = 0;
	while (token != NULL) {
		while (*token == ' ') {
			token++;
		}
		if (strcmp(token, type) == 0) {
			found = 1;
			break;
		}
		token = strtok(NULL, ",");
	}
	if (found) {
		return 1;
	} else {
		return 0;
	}
}

//Checking if the server can access "pokemon.csv":
void csvFileCheck(int *clientSocket) {
	char fileName[30];
	char buffer[80];
	int bytesRcv;	
	int bytesSent;	
	printf("\nThe data is stored in a file named \"pokemon.csv\" and is only accessible by the server.  To verify that the server can access the file, type \"pokemon.csv.\"  Follow all responses by pressing the Return key.\n\n");
	bool nameSpelling = false;
	while (!nameSpelling) {
		printf("File name: ");
		fgets(fileName, sizeof(fileName), stdin);
		fileName[strcspn(fileName, "\n")] = '\0';
		if (strcmp(fileName, "pokemon.csv") != 0) {
			printf("\nPlease check your spelling and re-type the file name.\n\n");
		} else {
			nameSpelling = true;
		}
	}

	//Sending a file name to the server:
	bytesSent = sendAll(*clientSocket, fileName, strlen(fileName));
	if (bytesSent <= 0) {
		printf("There was a problem sending the file name.\n");
	}
	//Receiving a message from the server:
	bytesRcv = recv(*clientSocket, buffer, sizeof(buffer) - 1, 0);
	if (bytesRcv <= 0) {
		printf("There was a problem receiving the message.");
	}
	buffer[bytesRcv] = '\0';
	printf("\n%s\n", buffer);
}

void userOptions(int clientSocket, char option[]) {
	int bytesSent;
	char buffer[80];
	//Outputting statements:
	printf("\nYou have the following options: to query the data file by Pokemon type, type \"a\";");
	printf("  to save query results in a file, type \"b\";");
	printf("  and if you are finished making queries, type \"c.\" \n\n");
	bool isOption = false;
	while (!isOption) {
		printf("Option: ");
		fgets(option, 49, stdin);
		option[strcspn(option, "\n")] = '\0';
		if ((strcmp(option, "a") == 0) || (strcmp(option, "b") == 0) || (strcmp(option, "c") == 0)) {
		       isOption = true;
		} else {
			printf("\nPlease type \"a,\" \"b,\" or \"c.\"\n\n");
		}
	}
	strcpy(buffer, option);
	// To send a letter, "a," "b," or "c" to the server:
	bytesSent = sendAll(clientSocket, buffer, strlen(buffer));
       	if (bytesSent <= 0) {
		printf("There was a problem sending a letter to the server.\n");
	}
}

//Saving a file name:
void getFileName(threadArgs *args, char (**fileNames)[30], int *numFiles, int *fileNamesLength) {
	char fileName[30];
	bool fileCond1 = false;
	bool fileCond2 = false;
	printf("\nType the name of the file, ending in \".txt\" and with a maximum of 20 characters, within which you would like all new query results saved.\n\n");
	while (!(fileCond1 && fileCond2)) {
		printf("File name: ");
		fgets(fileName, sizeof(fileName), stdin);
		fileName[strcspn(fileName, "\n")] = '\0';
		size_t length = strlen(fileName);
		if (length >= 4 && strcmp(fileName + length - 4, ".txt") == 0) {
			fileCond1 = true;			
		} else {
			printf("\nPlease type a file name that ends with \".txt.\"\n\n");
		}
		if (strlen(fileName) <= 20) {
			fileCond2 = true;
		} else {
			printf("\nPlease type a file name with a maximum length of 20 characters.\n\n");
		}
	}
	strcpy(args -> newFile, fileName);
	if (*numFiles >= *fileNamesLength) {
		*fileNamesLength += 20;
		char (*temp)[30];
		temp = realloc(*fileNames, *fileNamesLength * sizeof(**fileNames));
		if (temp == NULL) {
			printf("There was a problem re-allocating memory for \"fileNames.\"\n");
			return;
		}
		*fileNames = temp;
	} 
	strcpy((*fileNames)[*numFiles], fileName);
}

//Outputting the names of new files in the user's directory:
void closingMessage(int *numFiles, char (*fileNames)[30]) {
	int length = *numFiles * 25;
	char fileNameList[length];
	fileNameList[0] = '\0';
	char lastFileName[25];
	if (*numFiles == 0) {
		printf("\n0 files have been added to your working directory.  Thank you for using Pokemon Data Query.");
	} if (*numFiles == 1) {
		printf("\nThe file \"%s\" has been added to your working directory.  Thank you for using Pokemon Data Query.", fileNames[0]);

	} else if (*numFiles == 2) {
		printf("\nThe files \"%s\" and \"%s\" have been added to your working directory.  Thank you for using Pokemon Data Query.", fileNames[0], fileNames[1]);
	} else if (*numFiles > 2) {
		strcpy(lastFileName, fileNames[*numFiles - 1]);
		for (int i = 0; i < *numFiles - 1; i++) {
			strcat(fileNameList, "\"");
			strcat(fileNameList, fileNames[i]);
			strcat(fileNameList, ",\" ");
		}
		printf("\nThe files %sand \"%s\" have been added to your working directory.  Thank you for using Pokemon Data Query.", fileNameList, lastFileName);
	}
}
	

