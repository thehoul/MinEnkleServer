#include "helpers.h"

#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <magic.h>


int send_file(char* file_path, int dest, enum HTTPv httpv, int feedback){

    struct stat file_stats;
    stat(file_path, &file_stats);

    if(file_stats.st_size > MAX_FILE_SIZE){
        fprintf(stderr, "Requested file is too big. Max is %i\n", MAX_FILE_SIZE);
        return 0;
    }

    char content_type[50];
    int succ = get_mime_type(file_path, content_type);
    if(!succ){
        fprintf(stderr, "Failed to find content type");
        memcpy(content_type, "text/plain", 10);
    }
    

    FILE* file = fopen(file_path, "r");
    if(file == NULL){
        perror("Couldn't open requested file");
        return 0;
    }
    

    
    unsigned char body[MAX_FILE_SIZE];
    memset(body, 0, MAX_FILE_SIZE);
    size_t file_size = fread(body, sizeof(char), MAX_FILE_SIZE, file);
    if(file_size != file_stats.st_size){
        return 0;
    }
    fclose(file);

    unsigned char msg[MAX_MSG];
    memset(msg, 0, MAX_MSG);
    switch(httpv){
        case HTTP11:
            snprintf(msg, MAX_MSG, 
                "HTTP/1.1 200 OK\n"
                "Content-Type: %s\n"
                "Content-Length: %li\n\n%s\n", content_type, file_size, body);
            break;
        default:    
            fprintf(stderr, "HTTP version provided is not supported\n");
            return 0;
    }

    write(dest, msg, strlen(msg));

    if(feedback == 1){
        printf("Sent file \"%s\" (%li bytes). Bytes sent : %li\n", file_path, file_size, strlen(msg));
    } else if(feedback == 2){
        printf("Sent %li bytes : %s\n", strlen(msg), msg);
    }

    
    return file_size;
}

void send_404(int client, enum HTTPv httpv){
    send_file("./server/html/404.html", client, httpv, 0);
}

size_t read_client(int client, char rcv[]){

    memset(rcv, 0, MAX_RCV_SIZE);
    size_t nbytes = read(client, rcv, MAX_RCV_SIZE);
    if(nbytes <= 0 ){
        perror("Error reading client");
        close(client);
        return 0;
    }

    return nbytes;
} 

int get_mime_type(char* file_path, char content_type[]){
    const char* mime;
    magic_t magic;


    magic = magic_open(MAGIC_MIME);
    if(magic == NULL){
        fprintf(stderr, "Failed to create magic cookie\n");
        return 0;
    }
    
    if(magic_load(magic, NULL) < 0){
        perror("Failed to load magic");
        return 0;
    }
    
    mime = magic_file(magic, file_path);
    if(mime == NULL){
        perror("Failde to read MIME type of requested file");
        return 0;
    }

    memcpy(content_type, mime, strlen(mime));

    magic_close(magic);

    return 1;
}