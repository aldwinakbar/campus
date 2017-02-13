#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <net/if.h>

void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in6 serv_addr;
    struct hostent *server;
    char buffer[256] = "This is a string from client!";

   	if(argc < 2){
     printf("Specify a IPv6\n");
     printf("usage: programname ipv6 port interface \n");
     exit(1);
	}
	
   if(argc < 3){
     printf("Specify a port number\n");
     printf("usage: programname ipv6 port interface \n");
     exit(1);
	}
 
   if(argc < 4){
     printf("Specify a interface\n");
     printf("usage: programname ipv6 port interface \n");
     exit(1);
	}
	
    portno = atoi(argv[2]);

    printf("\nIPv6 TCP Client Started...\n");
    
    //Sockets Layer Call: socket()
    sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    //Sockets Layer Call: gethostbyname2()
    server = gethostbyname2(argv[1],AF_INET6);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin6_flowinfo = 0;
    serv_addr.sin6_family = AF_INET6;
    memmove((char *) &serv_addr.sin6_addr.s6_addr, (char *) server->h_addr, server->h_length);
    serv_addr.sin6_port = htons(portno);
	
	/* specify the interface we are going to use */
	serv_addr.sin6_scope_id=if_nametoindex(argv[3]);
  
    //Sockets Layer Call: connect()
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    
    //Sockets Layer Call: send()
    n = send(sockfd,buffer, strlen(buffer)+1, 0);
    if (n < 0)
        error("ERROR writing to socket");

    memset(buffer, 0, 256);
    
    //Sockets Layer Call: recv()
    n = recv(sockfd, buffer, 255, 0);
    if (n < 0)
        error("ERROR reading from socket");
    printf("Message from server: %s\n", buffer);

    //Sockets Layer Call: close()
    close(sockfd);
        
    return 0;
}
