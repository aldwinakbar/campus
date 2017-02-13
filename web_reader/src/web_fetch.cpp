#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#define SOURCE_START_IDENTIFIER "0.tcp.ngrok.io"
#define SOURCE_START_IDENTIFIER2 "<html>" 		//this is the name of the identifier that the
#define	MAX_BUFFER 3000
void getForwardingPort(char *datain);

int main(int argc , char *argv[])
{
	if(argc != 4){
		printf("Usage %s : hostname file_location port\n",argv[0]);
		return(0);
	}

    int socket_desc;
    struct sockaddr_in server;
    char server_reply[MAX_BUFFER];
    char message[MAX_BUFFER];
    int port_number;
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    port_number = atoi(argv[3]);

    server.sin_addr.s_addr = inet_addr("127.0.01");
    server.sin_family = AF_INET;
    server.sin_port = htons( port_number );

    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    char port_data_http[] = "50002";
    //sprintf(message,"POST %s HTTP/1.1\nHost: %s\nContent-length: 10\nContent-Type: application/x-www-form-urlencoded\nConnection: close\n\nport=%s\n",argv[2],argv[1],port_data_http);
    sprintf(message,"GET %s HTTP/1.1\r\nHost: %s\r\n\r\n",argv[2],argv[1]);
    //sprintf(message,"POST /mikon.php HTTP/1.1\nHost: 127.0.0.1\nContent-length: 12\nContent-Type: application/x-www-form-urlencoded\nConnection: close\n\nuid=a1s2d3f4\n");
    //sprintf(message,"GET /mikon.php?uid=a1s2d3f4 HTTP/1.1\r\nHost: 192.168.43.53\r\n\r\n");
    //sprintf(message,"GET /mikon.php HTTP/1.1\r\nHost: 192.168.1.4\r\n\r\n");

    puts("Connected\n");
    printf("Message size %d\n",(int)strlen(message));

    //Send some data
    if( send(socket_desc , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");

    //Receive a reply from the server
    if( recv(socket_desc, server_reply , MAX_BUFFER , 0) < 0)
    {
        puts("recv failed");
    }
    puts("Reply received\n");
    puts(server_reply);
    //getForwardingPort(server_reply);
    close(socket_desc);

    return 0;
}

void getForwardingPort(char *datain){

	char *source;
	char forward_port[8];
	int i;
    source = strstr(datain,SOURCE_START_IDENTIFIER);

	if(source == NULL)
	{
		source = strstr(datain,SOURCE_START_IDENTIFIER2);
	}

	//printf("%s\n",source);
	i = 0;
	while (i < 5 ){

		forward_port[i] = source[i+15];
		i++;
	}
	printf("%s\n",forward_port);


}
