#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>
#include <stdio.h>

#include "request_parser.h"

#define MAX_RCV_SIZE (4096 * 1024)
#define MAX_FILE_SIZE 182000
#define MAX_MSG 183000
#define MAX_FILE_PATH 100
#define CONTENT_TYPE_LEN 50

size_t send_response(enum HTTPv httpv, char* content_type, size_t file_size, char* body, int dest);
int send_file(char* file_path, int dest, enum HTTPv httpv, int feedback);
size_t send_OK(enum HTTPv httpv, int dest);
void send_404(int client, enum HTTPv httpv);
size_t read_client(int client, char rcv[]);

int get_mime_type(char* file_path, char content_type[]);


#endif