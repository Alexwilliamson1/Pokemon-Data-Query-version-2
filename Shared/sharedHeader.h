#ifndef SHARED_HEADER_H
#define SHARED_HEADER_H

#include <pthread.h>
#include <stdbool.h>

//Global variables:
extern pthread_mutex_t lock;
extern int activeClients;
extern bool endProgram;

//A structure for the data for one Pokemon:
typedef struct {
	char number[10];
	char name[30];
	char type1[20];
	char type2[10];
	char total[5];
	char HP[5];
	char attack[5];
	char defense[5];
	char spatk[5];
	char spdef[5];
	char speed[5];
	char generation[10];
	char legendary[10];
} pokemon;

//An "array" structure to store query results:
typedef struct { 
	int size;
	int capacity;
	pokemon **elements;
} array;

//A structure for thread arguments:
typedef struct {
	array *copiedPokemon;
	char (*type1s)[25];
	int typeCapacity;
	int numTypes;
	char newFile[20];
	char csvFile[25];
	int clientSocket;
        int serverSocket;	
	bool fileCreated;
} threadArgs;

//Shared functions:
array* pokemonArray(int);
void reset(array*);
int recvAll(int, void*, size_t);
int sendAll(int, const void*, size_t); 

#endif



