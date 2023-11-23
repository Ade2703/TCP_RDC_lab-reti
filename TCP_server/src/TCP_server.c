/*
 Name        : Calculator_TCP_server.c
 Author      : De Padova Antonio
 Version     :
 Copyright   :
 Description : Calculator with TCP protocol server
 */

#include "header.h"

// Function to clear the console screen based on the operating system
void clear(){
#ifdef _WIN32
	system("cls"); // Clears the console screen on Windows
#else
    system("clear"); // Clears the console screen on Linux/Unix
#endif
}

char buffer[BUFFER_SIZE]; // Buffer to hold data received and sent

// Function to perform subtraction operation
void sub(float n1,float n2){
	float res=n1-n2;
    sprintf(buffer+strlen(buffer),"%.2f",res); // Appends the result to the buffer
}

// Function to perform multiplication operation
void mult(float n1,float n2){
	float res=n1*n2;
    sprintf(buffer+strlen(buffer),"%.2f",res); // Appends the result to the buffer
}

// Function to perform addition operation
void add(float n1,float n2){
	float res=n1+n2;
    sprintf(buffer+strlen(buffer),"%.2f",res); // Appends the result to the buffer
}


// Function to perform division operation
void division(float n1,float n2){
	float res=0;
	if(n2!=0){
		res=n1/n2;
		memset(buffer,'\0',BUFFER_SIZE); // Clears the buffer
		sprintf(buffer+strlen(buffer),"%.2f",res); // Appends the result to the buffer
	}else{
		strcat(buffer,"\tError - Division by zero\n"); // Handles division by zero error
	}
}

int main() {
    #ifdef _WIN32
    WSADATA wsaData; // Structure to handle Winsock data in Windows
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0){
        printf("Error initializing Winsock\n");
        return 1;
    }
    #endif

    int serverSocket,clientSocket; // Descriptors for server and client sockets
    struct sockaddr_in serverAddr,clientAddr; // Address structures for server and client
    socklen_t clientAddrSize=sizeof(clientAddr); // Size of client address structure
    int res;

    // Create a socket
    serverSocket=socket(AF_INET,SOCK_STREAM,0);
    if(serverSocket==-1){
        printf("Error creating socket\n");
        return 1;
    }

    // Configure server address
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_addr.s_addr=INADDR_ANY;
    serverAddr.sin_port=htons(PORT);

    // Bind the socket to the server address
    if(bind(serverSocket, (struct sockaddr*)&serverAddr,sizeof(serverAddr))==-1){
        printf("Error binding socket\n");
        return 1;
    }

    // Start listening for incoming connections
    listen(serverSocket, MAX_CLIENTS);

    while(1){
        clear(); // Clear the console screen

        // Accept incoming client connection
        clientSocket=accept(serverSocket,(struct sockaddr*)&clientAddr,&clientAddrSize);
        if(clientSocket==-1){
            printf("Error accepting connection\n");
            return 1;
        }

        // Get the client's IP address
        char* clientIP=inet_ntoa(clientAddr.sin_addr);
        printf("Connection successfully established with %s:%i\n",clientIP,PORT);

        while((res=recv(clientSocket,buffer,BUFFER_SIZE,0))>0){
            if(res==-1){
                printf("Error reading data\n");
                return 1;
            }

            float n1,n2;
            char operator;

            bool flag=false; //flag for the correct syntax of operands

            puts(buffer); // Print the received operation

            //Check that the operands are valid

            for(int i=1;i<BUFFER_SIZE;i++){
            	if(isalpha(buffer[i])!=0)
            		flag=true;
            }

            // Parse the received data to extract operator and operands
            if(sscanf(buffer,"%c %f %f",&operator,&n1,&n2)==3&&flag==false){
                memset(buffer,'\0',BUFFER_SIZE); // Clear the buffer
                // Perform the requested operation
                switch (operator) {
                    case '+':
                        add(n1, n2);
                        break;
                    case '-':
                        sub(n1, n2);
                        break;
                    case '*':
                        mult(n1, n2);
                        break;
                    case '/':
                        division(n1,n2);
                        break;
                    default:
                        strcat(buffer,"\tThe given operator is invalid\n"); // Handle invalid operator
                        break;
                }
            }else{
                strcat(buffer,"\t<--The given input is invalid. Please enter a valid mathematical operation (+, -, /, *)\n");
            }
            printf("The result is:\t%s\n",buffer);
            // Send the result back to the client
            send(clientSocket,buffer,strlen(buffer),0);
            memset(buffer,'\0',BUFFER_SIZE); // Clear the buffer
        }

        // Handle client disconnection
        if(res==0) {
            printf("The client has disconnected\n");
            closesocket(clientSocket);
        }else if(res==-1) {
            printf("Error receiving data\n");
            return 1;
        }
    }

    // Close the server socket
    #ifdef _WIN32
    closesocket(serverSocket);
    #else
    close(serverSocket);
    #endif

    // Clean up Winsock resources (only on Windows)
    #ifdef _WIN32
    WSACleanup();
    #endif

    return 0;
}
