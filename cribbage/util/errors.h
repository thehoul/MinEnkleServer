#ifndef ERRORS_H
#define ERRORS_H

#include <stdint.h>
#include <stdlib.h>

enum Errors {
    NO_ERROR,
    ILLEGAL_PHASE,
    INVALID_ARGUMENT,
    PLAYER_NOT_IN_GAME,
    PARSING_ERROR,
};

const char* error_to_string(int err);
void print_err(int err, const char* specific);
size_t write_error(int err, const char* specific, char* buffer);

#endif