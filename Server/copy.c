#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serverHeader.h"
#include "../Shared/sharedHeader.h"

//Copying and saving file data for one query:
int copy(array *arr, char *type1, char *line) {
	char field1[10];
	char field2[30];
	char field3[20];
	int returnValue;
	if (sscanf(line, "%9[^,], %29[^,], %19[^,]", field1, field2, field3) != 3) {
		printf("There was a problem reading a \"Type 1\" in the file.\n");
		return -1;
	}
	if (strcmp(type1, field3) == 0) {
		pokemon *newPokemon = malloc(sizeof(pokemon));
		if (!newPokemon) {
			printf("There was a problem allocating memory for \"newPokemon.\"\n.");
			return -1;
		}
		if (strstr(line, ",,")) {
			removeConsecutiveCommas(line);
			int fields = sscanf(line, "%9[^,], %29[^,], %19[^,], %4[^,], %4[^,], %4[^,], %4[^,], %4[^,], %4[^,], %4[^,], %9[^,], %9[^\n]", newPokemon -> number, newPokemon -> name, newPokemon -> type1, newPokemon -> total, newPokemon -> HP, newPokemon -> attack, newPokemon -> defense, newPokemon -> spatk, newPokemon -> spdef, newPokemon -> speed, newPokemon -> generation, newPokemon -> legendary);
			//Checking that all the fields in "line" were successfully copied:
			if (fields != 12) {
				printf("There was a problem copying the file data.\n");
			}
		}
		else {
			int fields = sscanf(line, "%9[^,], %29[^,], %19[^,], %9[^,], %4[^,], %4[^,], %4[^,], %4[^,], %4[^,], %4[^,], %4[^,], %9[^,], %9[^\n]", newPokemon -> number, newPokemon -> name, newPokemon -> type1, newPokemon -> type2, newPokemon -> total, newPokemon -> HP, newPokemon -> attack, newPokemon -> defense, newPokemon -> spatk, newPokemon -> spdef, newPokemon -> speed, newPokemon -> generation, newPokemon -> legendary);
			//Checking that all the fields in "line" were successfully copied:
			if (fields != 13) {
				printf("There was a problem copying the file data.\n");
			}
		}
		//Adding a "pokemon" variable to the array of query results:
		returnValue = addPokemon(arr, newPokemon);
		if (returnValue < 0) {
			free(newPokemon);
			return -1;
		}	
	}
	return 0;
}
