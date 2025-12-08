#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    struct sockaddr_in socket_data;
    socklen_t socklen=sizeof(socket_data);

    socket_data.sin_family=AF_INET;
    socket_data.sin_port=htons(PORT);
    socket_data.sin_addr.s_addr=INADDR_ANY;

    int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd<0){
        printf("error has been occured while creating a socket");
        return 0;
    }
    printf("server initialized\n");

    int bind_socket_to_sockaddr=bind(socket_fd,(struct sockaddr*)&socket_data,sizeof(socket_data));
    if(bind_socket_to_sockaddr<0){
        printf("error occured while binding socket to sockaddres");
        return 0;
    }
    printf("sucessfully binded\n");

    int listen_to_server=listen(socket_fd,5);
    if(listen_to_server<0){
        printf("cant listen to a server");
        return 0;
    }
    printf("listening:\n");
    

    char buffer[BUFFER_SIZE];
    int client_fd=accept(socket_fd,(struct sockaddr*)&socket_data,&socklen);
    if(client_fd<0){
        printf("client creation error");
        return 0;
    }    
    while(1){
        int len=0;
        int bytes=recv(client_fd,buffer,sizeof(buffer)-1,0);
        if (bytes == 0) {
             printf("Client disconnected\n");
            close(client_fd);
            break;
         }
        buffer[bytes]='\0';
        printf("client: %s",buffer);
    }
    
    printf("disconnecting\n");
    close(client_fd);
    close(socket_fd);
    return 0;
}
