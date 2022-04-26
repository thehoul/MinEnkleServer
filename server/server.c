#include "server.h"

#include <stdio.h>
#include <string.h>


Server* init_server(int port){
    Server* server = calloc(1, sizeof(Server));

    // Default values for now
    server->domain = AF_INET6;
    server->protocol = IPPROTO_TCP;
    server->service = SOCK_STREAM;

    server->port = port;

    // Create and test the socket
    server->socket = socket(server->domain, server->service, server->protocol);
    if(server->socket == -1){
        perror("Failed to create socket");
        free(server);
        return NULL;
    }

    // Change option to allow for both IPv4 & IPv6
    int val = 0;
    if(setsockopt(server->socket, IPPROTO_IPV6, IPV6_V6ONLY, (void *)&val, sizeof(val)) == -1){
        perror("Failed to change socket options");
    }

    // Change option to enable reusing addresses
    int flag = 1;
    if(setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) == -1){
        perror("Failed to set socket reuse address");
        return NULL;
    }

    // Setup the server's address
    memset(&server->address, 0, sizeof(server->address));
    server->address.sin6_family = server->domain;
    server->address.sin6_addr = in6addr_any;
    server->address.sin6_port = htons(port);

    // Bind the socket to the network
    if(bind(server->socket, (const struct sockaddr *)&server->address, sizeof(server->address)) == -1){
        perror("Failed to bind socket to network");
        free(server);
        return NULL;
    }

    // Set the socket to listening
    if(listen(server->socket, DEFAULT_BACKLOG) < 0){
        perror("Failed to set the socket to listen");
        free(server);
        return NULL;
    }

    return server;
}

void run_server(Server* server, Handler handler){
    handler(server);
}

void destroy_server(Server* server){
    close(server->socket);
    free(server);
    server = NULL;
}