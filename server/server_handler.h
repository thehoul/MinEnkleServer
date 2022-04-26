#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#define MAX_RCV_SIZE (4096 * 1024)

#include "server.h"
#include "util/request_parser.h"

void default_handler(Server* server);
void http_get_handler(Server* server);


#endif