#ifndef C_HEADER_H
#define C_HEADER_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include "../Shared/sharedHeader.h"

//Client functions:
void *createFile(void*);
void writePokemonData(pokemon*, FILE*, int); 
void socketSetup(int*);
int isType(char*);
void request(threadArgs*);
void getFileName(threadArgs*, char(**fileNames)[30], int*, int*);
void closingMessage(int*, char(*fileNames)[30]);
void userOptions(int, char*);
void csvFileCheck(int*);
void interfaceLoop(threadArgs*, bool*, int*, char(*fileNames)[30], int*);

#endif



