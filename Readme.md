1) creation d'une socket
#include <sys/socket.h>

int socket(int famille, int type, int protocole);

la fonction socket() retourne:
	-1	en cas d'erreur
	>=0	descripteur de socket

int famille:
	PF_INET: famille de socket IPv4 TCP/IP
		IPv4 = Internet Protocol version 4
		TCP/IP = Transmission Control Protocol / Internet Protocol
	PF_INET6: famille de socket IPv6 TCP/IP
		IPv6 = Internet Protocol version 6
	PF_APPLETALK: famille de socket AppleTalk
		AppleTalk = AppleTalk Protocol
	PF_UNIX: famille de socket Unix
	PF_IPX: famille de socket IPX
		protocole nouvelles versions de TCP/IP
int type:
#include <netinet/in.h>
#include <arpa/inet.h>
	SOCK_STREAM: socket TCP mode connecté (client)
	SOCK_DGRAM: socket UDP mode non connecté (serveur)

int protocole:
	IPPROTO_TCP: protocole TCP
	IPPROTO_UDP: protocole UDP
	0: protocole par défaut

Noter:
	PF_INET + SOCK_STREAM = IPPROTO_TCP
	PF_INET + SOCK_DGRAM = IPPROTO_UDP

PF_INET Vs AF_INET
	PF_INET pour socket()
	AF_INET pour bind() et connect()
	AF_INET pour listen() et accept()

coté client:
	int sd = socket(AF_INET, SOCK_STREAM, 0); SOCK_STREAM = TCP, 0 = protocole par défaut
coté serveur:
	int fd = socket(AF_INET, SOCK_STREAM, 0);

2) Utilisation de la socket : bind()
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int bind(int ss, const struct sockaddr *localaddr, socklen_t addrlen);
	ss: descripteur de socket nouvellement créé
	localaddr: adresse de socket local et on utilise sockaddr_in pour cela
		sockaddr_in: structure de socket
			sin_family: famille de socket
			sin_port: port de socket
			sin_addr: adresse de socket
				sin_addr.s_addr: adresse IP
			Exemple:
				struct sockaddr_in localaddr;
				localaddr.sin_family = AF_INET;
				localaddr.sin_port = htons(80); htons = host to network short
				localaddr.sin_port = 0; // 0 port alloué automatiquement(dynamiquement)
				localaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); inet_addr = internet address
					htons: convertit un entier en notation binaire
					inet_addr: convertit une adresse IP en notation binaire
	addrlen: taille de l'adresse de socket local (sizeof(struct sockaddr))
Les différentes possibilités de bind() sont:
	A) en specifiant l'adresse IP et le port
	B) en specifiant l'adresse IP et en laissanant le system choisir un numero de port libre
		inutilite (sin_port = 0). Numero de port au dessus des ports réservés
	C) en utilisant l'adresse IP: INADDR_ANY qui signifie que le socket peut etre utilisé par n'importe quelle adresse IP de la machine locale (localhost)(s'il en existe plusieurs)

2) Utilisation de la socket : listen()
#include <sys/socket.h>
int listen(int Ss, int backlog);
la fonction renvoi 0 en cas de succes, -1 en cas d'erreur
les parametres sont:
	Ss: socket créé avec la fonction socket();
	backlog: indique le nombre maximum de demande de connection mises en attentes.(ch7al mn wahd aytconnecta)

3) Utilisation de la socket : accept()
#include <sys/socket.h>
int accept(int Ss, struct sockaddr *addr, socklen_t *addrlen);
la fonction renvoi 0 en cas de succes, -1 en cas d'erreur
les parametres sont:
	Ss: socket créé avec la fonction socket();
	addr: adresse de socket du client
	addrlen: taille de l'adresse de socket du client

4) échange des donnêes : send()
#include <sys/socket.h>
int send(int Ss, const void *msg, size_t len, int flags);
la fonction renvoi le nombre de bytes envoyés en cas de succes, -1 en cas d'erreur
les parametres sont:
	Ss: socket créé avec la fonction socket();
	msg: message à envoyer
	len: taille du message
	flags:
		MSG_OOB: message de type out of band
		MSG_PEEK: ne modifie pas le buffer de réception
		MSG_DONTROUTE: ne fait pas le routage
		0: indique un envoi normal (par défaut)