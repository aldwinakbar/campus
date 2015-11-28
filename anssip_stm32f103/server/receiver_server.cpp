#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#define	MAX_BUFFER 6000

int main(int argc , char *argv[])
{
	int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
    int port_number = 50005;
     
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1){
        printf("Could not create socket");
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port_number);
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
		perror("bind failed. Error");
        return 1;
    }   
    listen(socket_desc , 255);
    
	while(1){
		
		// ################# Create connection to send to Database ################# 
		struct sockaddr_in to_php_server;
		char php_message[MAX_BUFFER];
		char server_reply[MAX_BUFFER];
		int http_port = 80;
		int socket_to_php = socket(AF_INET , SOCK_STREAM , 0);
		if (socket_to_php == -1){
			printf("Could not create socket");
		}
	 
		to_php_server.sin_addr.s_addr = inet_addr("127.0.0.1");
		to_php_server.sin_family = AF_INET;
		to_php_server.sin_port = htons( http_port );
		//Connect to remote server
		if (connect(socket_to_php , (struct sockaddr *)&to_php_server , sizeof(to_php_server)) < 0){
			puts("connect error");
        return 1;
		}	
		// ################# Create connection to send to Database ################# 
		
    
		puts("Waiting for incoming connections...");
		c = sizeof(struct sockaddr_in);
		 
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if (client_sock < 0){
			perror("accept failed");
			return 1;
		}
		puts("Connection accepted");
		 

		while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 ){
			client_message[read_size] = '\0';
			
			puts("Reply received\n");
			puts(server_reply);
			
			puts("Data Send\n");
     
			printf("Character Received : %d\n",read_size);
			printf("%s\n",client_message);			
		}
		
		// ######### Send to Database ######### 
		sprintf(php_message,"GET /mikon.php?uid=%s HTTP/1.1\r\nHost: 127.0.0.1\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n",client_message);
		if( write(socket_to_php , php_message , strlen(php_message)) < 0){
				puts("Send failed");
				return 1;
		}
		else{
			puts("Send PHP success");
			printf("%d\n",(int)strlen(php_message));
		}
		close(socket_to_php);
		// ######### Send to Database ######### 
		
		if(read_size == 0){
			puts("Client disconnected");
			fflush(stdout);
		}
		else if(read_size == -1){
			perror("recv failed");
		}
	}
	close(socket_desc);
     
    return 0;
}
