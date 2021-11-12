#include<stdio.h>
#include<string.h>	//strlen
#include<stdlib.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include<pthread.h>

void *connection_handler(void *);
int main(int argc, char *argv[])
{
    int socketdesc, new_socket, c, *new_sock;
    struct sockaddr_in server, client;
    char *message;

    socketdesc = socket(AF_INET, SOCK_STREAM, 0);
    if (socketdesc == -1)
    {
        printf("Could not create socket");
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    if(bind(socketdesc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    puts("bind done");

    listen(socketdesc, 3);
    puts("Waiting for incoming connections...");
    while((new_socket = accept(socketdesc, (struct sockaddr *)&client, (socklen_t*)&c)))
    {
        puts("Connection accepted");
        //Reply to client
        message = "Hello Client, I have received your connection.\n";
        write(new_socket, message, strlen(message));
        
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;
        
        if(pthread_create(&sniffer_thread, NULL, connection_handler, (void*) new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
        //pthread_join(sniffer_thread, NULL);
        puts("Handler assigned");
    }

    if(new_socket < 0)
    {
        perror("accept failed");
        return 1;
    }
    return 0;
}

void *connection_handler(void * socket_desc){
   //Get the socket descriptor
	int sock = *(int*)socket_desc;
	int read_size;
	char *message , client_message[2000];
	
	//Send some messages to the client
	message = "Greetings! I am your connection handler\n";
	write(sock , message , strlen(message));
	
	message = "Now type something and i shall repeat what you type \n";
	write(sock , message , strlen(message));
	
	//Receive a message from client
	while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
	{
		//Send the message back to client
		write(sock , client_message , strlen(client_message));
	}
	
	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}
		
	//Free the socket pointer
	free(socket_desc);
	
	return 0; 
    
}