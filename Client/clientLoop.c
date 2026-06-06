#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "clientHeader.h"
#include "../Shared/sharedHeader.h"

//Creating a command-line interface and processing user input:
void interfaceLoop(threadArgs *args, bool *endLoop, int *numFiles, char (*fileNames)[30], int *fileNamesLength) {
	array *data = args -> copiedPokemon;
	char userOption[50];

	//Outputting user options:
	userOptions(args -> clientSocket, userOption);
	//Running the corresponding functions for option a, b, or c:
	if (strcmp(userOption, "a") == 0) {
		if (args -> fileCreated == true) {
			data -> elements = malloc(data -> capacity * sizeof(pokemon*));
			args -> fileCreated = false;
		}
		//Requesting and receiving data from the server for one Pokemon type:
		request(args);
	} else if (strcmp(userOption, "b") == 0) {
		if (args -> numTypes == 0) {
			printf("\nPlease use option (a) to query the file before saving results.\n");
			return;
		}
		//Creating a file containing all new query results:
		getFileName(args, &fileNames, numFiles, fileNamesLength);	
		createFile(args);
		(*numFiles)++;
		//Freeing memory for new queries:
		reset(data);
		args -> fileCreated = true;
	} else if (strcmp(userOption, "c") == 0) {
		//If user queries were processed, but no file was created, free allocated memory:
		if (args -> fileCreated == false) {
			reset(data);
		}
		//Outputting statements:
		closingMessage(numFiles, fileNames);
		*endLoop = true;
	}
}


