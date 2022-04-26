#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <stdlib.h>
#include <stddef.h>

enum HTTPv {
    HTTP11
};

enum ReqType {
    GET
};

typedef struct {
    enum ReqType type;
    char* requested;
    enum HTTPv httpv;  
} Request;

Request* parse_request(char* buffer, size_t nbytes);
void print_request(Request* req);


#endif