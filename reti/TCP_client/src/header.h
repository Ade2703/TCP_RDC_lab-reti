/*
 Name        : header.h
 Author      : De Padova Antonio
 Version     :
 Copyright   :
 Description : Header file for Calculator with TCP protocol
 */

#ifndef HEADER_H_
#define HEADER_H_

#ifdef _WIN32
#include <winsock.h> // Import Winsock library for Windows platform
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#define closesocket close // Define closesocket for Unix/Linux
#include <termios.h>
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SERVER_ADDR "127.0.0.1" // Set the server's IP address
#define PORT 80 // Define the communication port number
#define BUFFER_SIZE 1024 // Size of the data buffer for sending/receiving data

#endif /* HEADER_H_ */
