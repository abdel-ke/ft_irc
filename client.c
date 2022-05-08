#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main()
{
	// 1. create a socket for the client.
	int clientSockFD = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSockFD != -1)
		printf("connect client socket ID: %d\n", clientSockFD);
	else
	{
		printf("F ailed to create a socket.\n");
		exit(1);
	}
	// 2. connect the client to a specific server
	struct sockaddr_in serverAdd;
	memset(&serverAdd, 0, sizeof(serverAdd));

	serverAdd.sin_family = AF_INET;
	serverAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAdd.sin_port = htons(1337);

	if (connect(clientSockFD, (struct sockaddr*)&serverAdd, sizeof(serverAdd)) == 0)
		printf("Connect successfully.\n");
	else
	{
		printf("Failed to connect.\n");
		exit(1);
	}
	// 3. send data to the server
	char buff[1024] = "Hello, I am Abdelhamid\n";
	send(clientSockFD, buff, strlen(buff), 0);
	// 4. receive data from the server
	memset(buff, 0, 1024);
	recv(clientSockFD, buff, 1024, 0);
	printf("The received data: %s\n", buff);

	return (0);
}