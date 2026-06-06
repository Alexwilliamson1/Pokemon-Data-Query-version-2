#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include "sharedHeader.h"

//Creating a dynamically allocated "array" object for saving query data:
array *pokemonArray(int capacity) {
        array *arr = (array*)malloc(sizeof(array));
        if (arr == NULL) {
        	printf("There was a problem regarding the memory allocation of \"arr.\"\n");
        	return NULL;
        }
        arr -> elements = (pokemon**)malloc(capacity * sizeof(pokemon*));
        if (arr -> elements == NULL) {
        	printf("There was a problem regarding the memory allocation of the \"elements\" of \"arr.\"\n");
        	free(arr);
        	return NULL;
        }
        arr -> size = 0;
        arr -> capacity = capacity;
        return arr;
}

//Freeing allocated memory for an array of "pokemon" structures and resetting the values of "array" structure members:
void reset(array *arr) {
  	for (int i = 0; i < arr -> size; ++i) {
  		free(arr -> elements[i]);
  	}
  	free(arr -> elements);
  	arr -> elements = NULL;
 	arr -> size = 0;
	arr -> capacity = 50;
}

//A function to call "recv" until the number of bytes specified by "length" have been received:
int recvAll(int socket, void *buffer, size_t length) {
	size_t total = 0;
	char *ptr = (char *)buffer;

	while (total < length) {
		int bytes = recv(socket, ptr + total, length - total, 0);
		if (bytes <= 0) {
			return bytes;
		}
		total += bytes;
	}
	return total;
}

//A function to call "send" until the number of bytes specified by "length" have been sent:
int sendAll(int socket, const void *buffer, size_t length) {
	size_t total = 0;
	const char *ptr = (const char *)buffer;

	while (total < length) {
		int bytes = send(socket, ptr + total, length - total, 0);
		if (bytes <= 0) {
			return bytes;
		}
		total += bytes;
	}
	return total;
}


