#include "server_handler.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILE_SIZE 9000
#define MAX_MSG 10000
#define MAX_FILE_PATH 100
#define BASE_HTML_DIR "./server/html"

int send_file(char* file_path, int dest, enum HTTPv httpv){
    FILE* file = fopen(file_path, "r");
    if(file == NULL){
        perror("Couldn't open requested file");
        return 0;
    }

    char body[MAX_FILE_SIZE];
    size_t size = fread(body, sizeof(char), MAX_FILE_SIZE, file);
    if(size == MAX_FILE_SIZE){
        fprintf(stderr, "Requested file is too big. Max is %i\n", MAX_FILE_SIZE);
        return 0;
    }

    char msg[MAX_MSG];
    switch(httpv){
        case HTTP11:
            snprintf(msg, MAX_MSG, 
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %ld\n\n%s\n", size, body);
            break;
        default:    
            fprintf(stderr, "HTTP version provided is not supported\n");
            return 0;
    }

    write(dest, msg, strlen(msg));
    fclose(file);
    return size;
}

void send_404(int client, enum HTTPv httpv){
    send_file("./server/html/404.html", client, httpv);
}

void default_handler(Server* server){

    char rcv[MAX_RCV_SIZE];
    socklen_t addrlen = sizeof(server->address);
    while(1){
        printf("Waiting for connection on port %i\n", server->port);

        fflush(stdout);

        int client = accept(server->socket, (struct sockaddr *) &server->address, (socklen_t*)&addrlen);

        memset(rcv, 0, MAX_RCV_SIZE);
        size_t nbytes = read(client, rcv, MAX_RCV_SIZE);
        if(nbytes < 0 ){
            perror("Error reading client");
            close(client);
            continue;
        }

        printf("Received : %s\n", rcv);
        close(client);
    }
}

void http_get_handler(Server* server){
    char rcv[MAX_RCV_SIZE];
    socklen_t addrlen = sizeof(server->address);

    while(1){
        printf("Waiting for connection on port %i\n", server->port);
        fflush(stdout);

        int client = accept(server->socket, (struct sockaddr *) &server->address, (socklen_t*)&addrlen);

        memset(rcv, 0, MAX_RCV_SIZE);
        size_t nbytes = read(client, rcv, MAX_RCV_SIZE);
        if(nbytes < 0){
            perror("Error reading client");
            close(client);
            continue;
        }

        printf("Received %li bytes : %s\n", nbytes, rcv);

        Request* req =  parse_request(rcv, nbytes);
        if(req == NULL){
            fprintf(stderr, "Couldn't parse request\n");
            close(client);
            continue;
        }

        if(strcmp(req->requested, "/") == 0){
            int sent = send_file("./server/html/index.html", client, req->httpv);
            if(sent == 0){
                fprintf(stderr, "Could not send requested file\n");
                send_404(client, req->httpv);
            }
        } else {

            char complete_file_path[MAX_FILE_PATH];
            memcpy(complete_file_path, BASE_HTML_DIR, strlen(BASE_HTML_DIR));
            memcpy(complete_file_path+strlen(BASE_HTML_DIR), req->requested, strlen(req->requested));
            int sent = send_file(complete_file_path, client, req->httpv);
            if(sent == 0){
                fprintf(stderr, "Could not send requested file. Requested : %s\n", complete_file_path);
                send_404(client, req->httpv);
            }
        }
        close(client);
    }
}