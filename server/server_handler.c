#include "server_handler.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>


void default_handler(Server* server){

    char rcv[MAX_RCV_SIZE];
    socklen_t addrlen = sizeof(server->address);
    while(1){
        printf("Waiting for connection on port %i\n", server->port);

        fflush(stdout);

        int client = accept(server->socket, (struct sockaddr *) &server->address, (socklen_t*)&addrlen);

        memset(rcv, 0, MAX_RCV_SIZE);
        size_t nBytes = read(client, rcv, MAX_RCV_SIZE);
        if(nBytes < 0 ){
            perror("Error reading client");
            close(client);
        }

        printf("Received : %s\n", rcv);
        close(client);
    }
}