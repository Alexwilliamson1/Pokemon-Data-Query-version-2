#ifndef serverHeader
#define serverHeader

//Including the libraries:
#include <pthread.h>
#include <stdbool.h>
#include <sys/socket.h>
#include "../Shared/sharedHeader.h"

//Declaring functions:
int copy(array*, char*, char*);
void response(threadArgs*);
int addPokemon(array*, pokemon*);
void removeConsecutiveCommas(char*);
void socketSetup(int*);
void receiveQuery(threadArgs*);
void fileCheck(threadArgs*);
void *clientHandler(void*);

#endif
