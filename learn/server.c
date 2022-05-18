#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main()
{
	// 1. create a socket for the server
	int serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocketFD != -1)
		printf("Server Socket ID: %d\n", serverSocketFD);
	else
	{
		printf("Failed to create a Socket.n\n");
		exit(1);
	}
	// 2. bind this socket to a specific port number
	struct sockaddr_in serverAdd;
	memset(&serverAdd, 0, sizeof(serverAdd));
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAdd.sin_port = htons(1337);
	if (bind(serverSocketFD, (struct sockaddr*)&serverAdd, sizeof(serverAdd)) == 0)
		printf("Server is binned to port no. 1337\n");
	else
	{
		printf("Binding failed\n");
		exit(1);
	}
	// 3. listen to the clients connection requests
	if (listen(serverSocketFD, 1) == 0)
		printf("Listenning....\n");
	else
	{
		printf("Failed to listen\n");
		exit(1);
	}
	// 4. accept the connection request
	struct sockaddr_in connectedClientAdd;
	memset(&connectedClientAdd, 0, sizeof(connectedClientAdd));
	socklen_t clinetAddlength = 0;
	int connectionServerSockFD = accept(serverSocketFD, (struct sockaddr*)&connectedClientAdd, &clinetAddlength);
	if (connectionServerSockFD == -1)
	{
		printf("Failed to accept a connection request\n");
		exit(1);
	}
	else
		printf("Accept a request at socket ID: %d\n", connectionServerSockFD);
	// 5. send or receive data from the client
	char receivMsg[1024];
	memset(receivMsg, 0, sizeof(receivMsg));
	recv(connectionServerSockFD, receivMsg, 1024, 0);
	// 6. close the socket
	close(serverSocketFD);
	close(connectionServerSockFD);

	return (0);
}