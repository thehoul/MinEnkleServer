#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../../server/util/request_parser.h"

#include <stdlib.h>


void handle_request(Request* req, int client);

#endif