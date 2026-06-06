# Pokemon-Data-Query-version-2

## Description:

One can use this program to query a file of Pokemon data and save the results in .txt files.  The Pokemon data includes attributes, such as the name, type, and attack points, for over 700 Pokemon.  This program searches Pokemon by their type.  

This version of the program uses a client-server model so that multiple users on different devices can query the data file at the same time and do so remotely from the server where the file is stored.  To simulate this scenario on one device, a script “run.sh” is provided, which will open a command-line interface for the server and each user.  

This program uses multi-threading, sockets, dynamic memory allocation, and file reading and writing to send data back and forth between the clients and server.  The server runs a separate thread for each client and stops running automatically when all clients have disconnected their sockets.

## Requirements:

To run this program, one requires a Linux, macOS, or other POSIX-compatible operating system.  Windows users must first install Windows Subsystem for Linux (WSL), MSYS2, Cygwin, or other software that runs a Unix-like environment.  One also requires a GCC or Clang C compiler with C11 support, POSIX threads and sockets support, GNU Make, and the file pokemon.csv.

## Instructions for building and running the program:

The program is organized into three directories (folders): Server, Client, and Shared.  Outside of these directories are: a makefile, the script “run.sh,” and the file “pokemon.csv.”  To run the program on one device, one can put all the directories and files in the same parent directory and use the “run.sh” shell script provided.  

To run “run.sh,” open a command-line interface and navigate to the script’s directory.  Use the command “chmod +x run.sh” to obtain permission to run the file, then “./run.sh” to run it.  More than one client can be opened from the command line by typing a number after “./run.sh.”  For example, running “./run.sh 3” will open one window for the server and three windows for the clients.  Each new window will display an introductory message for using the program.

To run the program on more than one device, save the Server and Shared directories, makefile and pokemon.csv in the same directory on the server’s device and the Client and Shared directories and makefile in the same directory on each client’s device.

Using more than one device also requires manual compilation and execution.  To build and run the server, use the commands “make build_server” and “./server_app” and to build and run a client, use the commands “make build_client” and “./client_app.”  Note that the server must run before the clients.

## Notes:

This program was tested on macOS 15.7 using Clang.  The server and clients use IP address 127.0.0.1 and port 6000 and communicate using Transmission Control Protocol (TCP).  
