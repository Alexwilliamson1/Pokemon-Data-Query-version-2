#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "clientHeader.h"
#include "../Shared/sharedHeader.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

void socketSetup(int *clientSocket) {
	struct sockaddr_in serverAddress;
	int status;

	//Creating the client's socket:
	*clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*clientSocket < 0) {
		printf("There was a problem opening the client's socket.\n");
		exit(-1);
	}

  	//Configuring the server's socket address:
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
	serverAddress.sin_port = htons((unsigned short) SERVER_PORT);

	//Connecting the client and server sockets:
	status = connect(*clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
	
	if (status < 0) {
		printf("There was a problem connecting the client's socket.\n");
		exit(-1);
	}
}



