/*
 Name        : Calculator_TCP_client.c
 Author      : De Padova Antonio
 Version     :
 Copyright   : 
 Description : Calculator with TCP protocol client
 */

#include "header.h" // Include necessary header file

// Function to clear the console screen based on platform
void clear(){
#ifdef _WIN32
	system("cls"); // Clear screen using 'cls' command for Windows
#else
    system("clear"); // Clear screen using 'clear' command for Linux/Unix
#endif
}

char* buffer; // Declare a global char pointer variable named 'buffer'

// Main function
int main() {
#ifdef _WIN32
	WSADATA wsaData; // Structure for handling Winsock data in Windows
	SOCKET clientSocket; // Socket variable specific to Windows
#else
    int clientSocket; // Socket variable for Unix/Linux
#endif

	struct sockaddr_in serverAddr; // Structure to hold server address information

#ifdef _WIN32
	// Initialize Winsock for Windows
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Error initializing Winsock\n");
		return 1;
	}
#endif

	// Create a socket
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket==-1){
		printf("Error creating socket\n");
		return 1;
	}

	// Configure server address
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=inet_addr(SERVER_ADDR); // Set the server IP address
	serverAddr.sin_port=htons(PORT); // Set the server port

	// Connect to the server
	if (connect(clientSocket,(struct sockaddr*) &serverAddr,
			sizeof(serverAddr))==-1){
		printf("Error connecting to the server\n");
		return 1;
	}

	// Main loop for sending/receiving data
	while (1){
		char* userChoice=malloc(sizeof(char[BUFFER_SIZE])); // Allocate memory for user's choice
		clear(); // Invoke function to clear the console screen

		buffer=malloc(sizeof(char[BUFFER_SIZE])); // Allocate memory for the buffer to store input
		puts("Please input a string for operation (<operator> <operand> <operand>)");


		do{
			fgets(buffer,BUFFER_SIZE,stdin); // Read user input from console
		}while(buffer[0]=='\n'); // Continue until receiving a non-empty input
		buffer[strlen(buffer)-1]='\0'; // Remove newline character
		fflush(stdin);

		// Send the user input to the server
		send(clientSocket,buffer,strlen(buffer),0);

        memset(buffer,'\0',BUFFER_SIZE); // Clear the buffer before receiving

		// Receive the result from the server
		recv(clientSocket,buffer,BUFFER_SIZE,0);

		printf("The result is:\t%s\n",buffer); // Print the result received from the server

		puts("In order to exit the program type \"=\"  or else any other key to continue");
		fgets(userChoice,BUFFER_SIZE,stdin); // Read user choice

		// Check if the user wants to exit
		if (userChoice[0]=='='&&strlen(userChoice)==2){
			clear();
			puts("Program terminated successfully");
			break; // Exit the loop and terminate the program
		}else{
			fflush(stdin);
		}
	}

#ifdef _WIN32
	closesocket(clientSocket); // Close the socket used in Windows
#else
    close(clientSocket); // Close the socket used in Unix/Linux
#endif

#ifdef _WIN32
	WSACleanup(); // Clean up Winsock resources in Windows
#endif

	return 0; // Return 0 to indicate successful execution
}
