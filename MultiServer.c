#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 50

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
	socklen_t clientLength = 0;

	while(1)
	{
		memset(&clientAdrr, 0, sizeof(clientAdrr));
		int connectionServerSocket = accept(serverSocket, (struct sockaddr*)&clientAdrr, &clientLength);

		if(connectionServerSocket == -1)
		{
			printf("Error in acceptation!!\n");
			exit(1);
		}
		else
			printf("New client with is connected.\n");
		pid_t pid = fork();

		if(pid == -1)
		{
			close(connectionServerSocket);
			exit(1);
		}

		if(pid  == 0)
		{
			close(connectionServerSocket);
			char buff[BUFFER_SIZE];
			int readSize = 0;
			while ((readSize = recv(connectionServerSocket, buff, BUFFER_SIZE, 0)) > 0)
			{
				memset(buff, 0, BUFFER_SIZE);
				// recv(connectionServerSocket, buff, BUFFER_SIZE, 0);
				printf("%s\n", buff);
				if (buff[0] == 'q' || buff[0] == 'Q')
				{
					printf("Client is disconnected\n");
					close(connectionServerSocket);
					exit(1);
				}
				else
					send(connectionServerSocket, buff, strlen(buff), 0);
			}
			if (readSize < 0)
			{
				printf("Error reading from socket!!\n");
				exit(1);
			}
		}
		else
		{
			close(connectionServerSocket);
			break ;
		}
	}
	return 0;
}