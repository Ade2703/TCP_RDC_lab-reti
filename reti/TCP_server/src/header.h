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
typedef int socklen_t; // Type definition for socklen_t on Windows platform
#include <winsock.h> // Include Winsock library for Windows
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
#include <stdbool.h>
#include <ctype.h>

#define MAX_CLIENTS 5 // Maximum number of allowed clients
#define BUFFER_SIZE 1024 // Size of the buffer for data transmission
#define PORT 80 // Port number designated for communication

#endif /* HEADER_H_ */
