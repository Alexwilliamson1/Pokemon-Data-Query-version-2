#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "serverHeader.h"
#include "../Shared/sharedHeader.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

void socketSetup(int *serverSocket) {
	struct sockaddr_in serverAddress;
	int status;

	printf("Server's status: ");
	*serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*serverSocket < 0) {
		printf("there was a problem opening the server's socket.\n");
		exit(-1);
	}

	memset(&serverAddress, 0, sizeof(serverAddress)); 
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons((unsigned short) SERVER_PORT);

  	status = bind(*serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
  	if (status < 0) {
    		printf("there was a problem binding the server's socket.\n");
    		exit(-1);
  	}

  	status = listen(*serverSocket, 5);
  	if (status < 0) {
    		printf("there was a problem listening on the server's socket.\n");
    		exit(-1);
  	}
	
	printf("running.\n");
}



