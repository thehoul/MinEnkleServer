#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include "server.h"
#include "util/request_parser.h"
#include "util/helpers.h"

void echo_handler(Server* server);
void http_get_handler(Server* server);


#endif