#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_BACKLOG 10

typedef struct {
    int port;
    int domain;
    int protocol;
    int service;

    struct sockaddr_in6 address;
    int socket;
} Server;

typedef void (*Handler)(Server*);

Server* init_server(int port);
void destroy_server(Server* server);

void run_server(Server* server, Handler handler);

#endif