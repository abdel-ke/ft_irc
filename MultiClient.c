#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 50

void	read_Routine(int sock, char *buff);
void	write_Routine(int sock, char *buff);

int main()
{
	//1. create a socket for the client
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket)
		printf("Client's Socket: %d\n", clientSocket);
	else
	{
		printf("Error Creating socket!!\n");
		exit(1);
	}
	//2. connect to the server.
	//specify the server address to connect to.
	struct sockaddr_in passivServerAdd;
	memset(&passivServerAdd, 0, sizeof(passivServerAdd));
	passivServerAdd.sin_family = AF_INET;
	passivServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
	passivServerAdd.sin_port = htons(1337);
	if (connect(clientSocket, (struct sockaddr*)&passivServerAdd, sizeof(passivServerAdd)) != 0)
	{
		printf("Error connection!!\n");
		exit(1);
	}
	else
		printf("Welcome to our echo system: \n");
	char buff[BUFFER_SIZE];
	pid_t pid = fork();
	if (pid == 0)
		write_Routine(clientSocket, buff);
	else
		read_Routine(clientSocket, buff);
}

void	write_Routine(int sock, char *buff)
{
	while(1)
	{
		scanf("%s", buff);
		send(sock, buff, BUFFER_SIZE, 0);
		if (buff[0] == 'q' || buff[0] == 'Q')
		{
			close(sock);
			printf("Client is disconnected\n");
			return ;
		}
		memset(buff, 0, BUFFER_SIZE);
	}
}
 
void	read_Routine(int sock, char *buff)
{
	while(1)
	{
		recv(sock, buff, BUFFER_SIZE, 0);
		if (strlen(buff) == 0)
		{
			close(sock);
			return ;
		}
		printf("Message from the server: %s\n", buff);
		memset(buff, 0, BUFFER_SIZE);
	}
}
