CC = gcc
CFLAGS = -Wall -pthread

SERVER_SRC = Server/serverMain.c Server/response.c Server/helpers.c Server/copy.c Server/socketSetup.c Server/serverLoop.c Shared/helpers.c

CLIENT_SRC = Client/clientMain.c Client/helpers.c Client/socketSetup.c Client/createFile.c Client/request.c Client/clientLoop.c Shared/helpers.c

.PHONY: all clean build_server build_client

all: build_server build_client

build_server: 
	$(CC) $(CFLAGS) $(SERVER_SRC) -o server_app  

build_client: 
	$(CC) $(CFLAGS) $(CLIENT_SRC) -o client_app  

clean:
	rm -f server_app client_app
