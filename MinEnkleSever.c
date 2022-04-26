#include "server/server.h"
#include "server/server_handler.h"

void main(int argc, char* argv[]){
    Server* serv = init_server(8000);
    if(serv == NULL){
        exit(1);
    }

    run_server(serv, http_get_handler);
}