#include "request_parser.h"

#include <string.h>
#include <stdio.h>

#define MAX_FILE_PATH_SIZE 50

Request* parse_request(char* buffer, size_t nbytes){

    Request* req = calloc(1, sizeof(Request));

    char* type = strsep(&buffer, " \r\n");
    if(strcmp(type, "GET") == 0){
        req->type = GET;
    } else if(strcmp(type, "POST") == 0){
        req->type = POST;
    } else {
        fprintf(stderr, "Provided request type cannot be handled. Received \"%s\"\n", type);
        free(req);
        return NULL;
    }   

    char* requested = strsep(&buffer, " \r\n");
    req->requested = calloc(MAX_FILE_PATH_SIZE , sizeof(char));
    memcpy(req->requested, requested, MAX_FILE_PATH_SIZE);

    

    char* httpv = strsep(&buffer, " \r\n");
    if(strcmp(httpv, "HTTP/1.1") == 0){
        req->httpv = HTTP11;
    } else {
        fprintf(stderr, "HTTP version is not supported. Got \"%s\"\n", httpv);
        free(req->requested);
        free(req);
        return NULL;
    }

    // if we have a post, get the content 
    if(req->type == POST){
        while(strcmp(strsep(&buffer, " \r\n"), "Content-Length:") != 0);
        req->content_len = atoi(strsep(&buffer, " \r\n"));
        req->content = calloc(strlen(buffer), sizeof(char));
        strcpy(req->content, buffer);
    }

    return req;

}

void print_request(Request* req){
    printf("Request : \n\ttype: %s\n\thttpv: %s\n\trequested: %s\n",
        req->type == GET ? "GET" : "UNKWN", req->httpv == HTTP11 ? "HTTP 1.1" : "HTTP ??",
        req->requested);
}