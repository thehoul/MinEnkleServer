#include "server_handler.h"
#include "util/helpers.h"
#include "../cribbage/controller/controller.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BASE_HTML_DIR "./server/html"


void echo_handler(Server* server){

    char rcv[MAX_RCV_SIZE];
    socklen_t addrlen = sizeof(server->address);
    
    while(1){
        printf("Waiting for connection on port %i\n", server->port);
        
        int client = accept(server->socket, (struct sockaddr *) &server->address, (socklen_t*)&addrlen);
        
        size_t nbytes = read_client(client, rcv);

        printf("Received(%li) : %s\n", nbytes, rcv);
        
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

        size_t nbytes = read_client(client, rcv);

        //printf("Received %li bytes : %s\n", nbytes, rcv);

        Request* req =  parse_request(rcv, nbytes);
        if(req == NULL){
            fprintf(stderr, "Couldn't parse request\n");
            close(client);
            continue;
        }

        if(strstr(req->requested, "cribbage") != NULL){
            handle_request(req, client);
        } else if(strcmp(req->requested, "/") == 0){
            int sent = send_file("./server/html/index.html", client, req->httpv, 1);
            if(sent == 0){
                fprintf(stderr, "Could not send requested file\n");
                send_404(client, req->httpv);
            }
        } else {

            char complete_file_path[MAX_FILE_PATH];
            memcpy(complete_file_path, BASE_HTML_DIR, strlen(BASE_HTML_DIR));
            memcpy(complete_file_path+strlen(BASE_HTML_DIR), req->requested, strlen(req->requested));
            int sent = send_file(complete_file_path, client, req->httpv, 2);
            if(sent == 0){
                fprintf(stderr, "Could not send requested file. Requested : %s\n", complete_file_path);
                send_404(client, req->httpv);
            }
        }
        close(client);
    }
}