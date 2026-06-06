#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "clientHeader.h"
#include "../Shared/sharedHeader.h"

void* createFile(void* arg) {
	threadArgs *args = (threadArgs *)arg;
	array *data = args -> copiedPokemon;
	char *newFile = args -> newFile;
	int size = data -> size;
	int numTypes = args -> numTypes;
	char types[300] = "";
	char lastType[20] = "";
	char firstLine[200];
	types[0] = '\0';
	strcpy(lastType, args -> type1s[numTypes - 1]);
	if (numTypes == 1) {
		snprintf(firstLine, sizeof(firstLine), "Search results for %s Pokemon: %d found.\n", lastType, size);
	} else {
		for (int i = 0; i < numTypes - 1; i++) {
			strcat(types, args -> type1s[i]);
			if (numTypes == 2) {
				strcat(types, " ");
			}
			if (numTypes > 2) {
				strcat(types, ", ");
			}
		}
		snprintf(firstLine, sizeof(firstLine), "Search results for %sand %s Pokemon: %d found.\n", types, lastType, size);
	}
	
	if (strlen(newFile) > 0) {
		//Creating a file to be written to:
		FILE* file = fopen(newFile, "w");
		if (file == NULL) {
			printf("There was a problem creating a new file.  Please type the name of the file again.\n");
			exit(1);
		}
		fprintf(file, "%s\n", firstLine);
		//Writing the created array to the file opened for writing:
		for (int i = 0; i < size; ++i) {
			writePokemonData(data -> elements[i], file, i + 1);
		}
		args -> numTypes = 0;	
		fclose(file);
	}
	return NULL;
}
