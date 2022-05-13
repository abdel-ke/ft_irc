#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define TRUE 1
#define FALSE 0
#define BUDDER_SIZE 50

int main()
{
	//1. create a socket for the server
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket != -1)
		printf("IF SERVERSOCKET\n");
	else
	{
		printf("Error in socket!!\n");
		exit(1);
	}

	//2. Set the server options
	int opt = TRUE;
	setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	//3. bind this socket to a specific port number
	struct sockaddr_in	serverAdd;
	memset(&serverAdd, 0, sizeof(serverAdd));
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAdd.sin_port = htons(1337);

	if (bind(serverSocket, (struct sockaddr*)&serverAdd, sizeof(serverAdd)) == 0)
		printf("Server is bined to port no. 1337.\n");
	else
	{
		printf("Error Binding.\n");
		exit(1);
	}
	//4. listen to the clients connection reqursts
	if (listen(serverSocket, 4) == 0)
		printf("Listenning...\n");
	else
	{
		printf("Error Listenning.\n");
		exit(1);
	}
	//5. accept the connection request
	struct sockaddr_in clientAdrr;
	int clientLeng = 0;
	
}