#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    struct sockaddr_in sock;
    sock.sin_family=AF_INET;
    sock.sin_port=htons(PORT);
    int addr=inet_pton(AF_INET,"127.0.0.1",&sock.sin_addr);

    if(addr<0){
        printf("error while creating socket struct");
        return 0;
    }

    int client_sock=socket(AF_INET,SOCK_STREAM,0);
    
    int connection = connect(client_sock,(struct sockaddr*)&sock, sizeof(sock));
    if(connection<0){
        printf("connection problem");
        return 0;
    }
    printf("connecting to a server:\n");

    char buffer[BUFFER_SIZE];
    while(1){
        printf("enter a text\n");
        fgets(buffer, BUFFER_SIZE, stdin);

        int x=send(client_sock,buffer,strlen(buffer),0);
        if(x<0){
            printf("error while sending");
            return 0;
        }
    }

    close(client_sock);
    return 0;
}
