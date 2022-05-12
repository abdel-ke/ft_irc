#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 50


int main()
{
	//1. create a socket for the server
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0)
	{
		perror("Error creating socket");
		exit(1);
	}
	else
	{
		printf("socket created\n");
	}
	//2. set the socket options
	int opt = TRUE;
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	//3. bind the socket to a port
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = INADDR_ANY;
	if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
	{
		perror("Error binding socket");
		exit(1);
	}
	else
	{
		printf("socket is binded to port no. 8080\n");
	}
	//4. listen for connections
	if (listen(server_socket, 4) < 0)
	{
		perror("Error listening");
		exit(1);
	}
	else
	{
		printf("socket is listening...\n");
	}
	//5. accept the connection
	int client_socket = 0;
	struct sockaddr_in client_address;
	while (1)
	{
		memset(&client_address, 0, sizeof(client_address));
		socklen_t client_address_length = 0;
		int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
		if (client_socket < 0)
		{
			perror("Error accepting connection");
			exit(1);
		}
		else
			printf("connection accepted\n");
		pid_t pid = fork();
		if (pid < 0)
		{
			perror("Error forking");
			exit(1);
		}
		else if (pid == 0)
		{
			//child process
			close(server_socket);
			char buffer[BUFFER_SIZE];
			int read_size = 0;
			while ((read_size = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0)
			{
				buffer[read_size] = '\0';
				printf("%s\n", buffer);
				if (buffer[0] == 'q' || buffer[0] == 'Q')
				{
					printf("client ID %d is disconnected\n", client_socket);
					close(client_socket);
					exit(15);
				}
				else
					send(client_socket, buffer, read_size, 0);
			}
			if (read_size < 0)
			{
				perror("Error reading from socket");
				exit(1);
			}
			close(client_socket);
			exit(0);
		}
		else
		{
			//parent process
			close(client_socket);
		}
	}
	
}