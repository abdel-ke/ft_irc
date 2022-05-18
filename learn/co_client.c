#include <stdio.h> //printf
#include <stdlib.h> //exit
#include <string.h> //strlen

#include <sys/types.h> //socket
#include <sys/socket.h> // socket
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_addr


int main()
{
	// create a socket for client
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("socket");
		exit(1);
	}
	else printf("socket created\n");
	// create a socket address
	struct sockaddr_in servaddr;
	// set the address
	memset(&servaddr, 0, sizeof(servaddr));
	// set the port
	servaddr.sin_family = AF_INET;
	// set the ip
	servaddr.sin_port = htons(1337);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// connect to server
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("connect");
		exit(1);
	}else printf("connected\n");
	// send data to server
	char sendbuf[1024];
	char recvbuf[1024];
	while (1)
	{
		printf("input: ");
		// get the data from user
		fgets(sendbuf, sizeof(sendbuf), stdin);
		if (strncmp(sendbuf, "exit", 4) == 0)
			break;
		// send the data to server
		send(sockfd, sendbuf, strlen(sendbuf), 0);
		// receive the data from server
		recv(sockfd, recvbuf, sizeof(recvbuf), 0);
		// print the data
		printf("recv: %s\n", recvbuf);
	}
	close(sockfd);
	return 0;
}
