#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>

int main()
{
	struct addrinfo *addr_info;
	struct addrinfo **res;
	getaddrinfo("abdel-ke.com", "http", addr_info, res);
}