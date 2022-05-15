#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	// 1. create a socket for the server
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0)
	{
		perror("socket");
		exit(1);
	}
	else printf("socket created\n");
	// 2. bind the socket to a specific port number
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1337);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	int bind_result = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (bind_result < 0)
	{
		perror("bind Failed\n");
		exit(1);
	}
	else
		printf("binded\n");
	// 3. listen to the clients connections requests
	int listen_result = listen(server_socket, 5);
	if (listen_result < 0)
	{
		perror("listen Failed");
		exit(1);
	}
	else printf("listening\n");
	// 4. accept the connection request
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
	if (client_socket < 0)
	{
		perror("accept Failed");
		exit(1);
	}
	else printf("accepted\n");
	// 5. send or receive data from the client
	char buffer[1024];
	int recv_result = recv(client_socket, buffer, sizeof(buffer), 0);
	if (recv_result < 0)
	{
		perror("recv Failed");
		exit(1);
	}
	else printf("received %s\n", buffer);
	// 6. close the socket
	close(client_socket);
	close(server_socket);
	return 0;
}