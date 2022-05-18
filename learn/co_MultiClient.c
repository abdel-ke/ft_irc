#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 50

void Write_Routine(int sock, char *buf)
{
	while (1)
	{
		scanf("%s", buf);
		send(sock, buf, strlen(buf), 0);
		if (buf[0] == 'q' || buf[0] == 'Q')
		{
			close(sock);
			printf("Client is disconnected\n");
			break;
		}
		memset(buf, 0, BUFFER_SIZE);
	}
	
}

void Read_Routine(int sock, char *buf)
{
	while (1)
	{
		recv(sock, buf, BUFFER_SIZE, 0);
		// printf("%s\n", buf);
		if (strlen(buf) == 0)
		{
			close(sock);
			// printf("Client is disconnected\n");
			break;
		}
		printf("Message from the server: %s\n", buf);
		memset(buf, 0, BUFFER_SIZE);
	}
}

int main()
{
	//1. create a socket for the client
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket < 0)
	{
		perror("Error creating socket");
		exit(1);
	}
	else
	{
		printf("socket created\n");
	}
	//2. connect to the server
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
	{
		perror("Error connecting to server");
		exit(1);
	}
	else
	{
		printf("connected to server\n");
	}
	char buffer[BUFFER_SIZE];
	pid_t pid = fork();
	if (pid == 0)
			Write_Routine(client_socket, buffer);
	else
			Read_Routine(client_socket, buffer);
}