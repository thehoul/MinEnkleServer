#include "errors.h"

#include <stdio.h>

const char* error_to_string(int err){
    switch(err){
        case NO_ERROR:
            return "No Error";
        case ILLEGAL_PHASE:
            return "Illegal Phase";
        case INVALID_ARGUMENT:
            return "Invalid Argument";
        case PLAYER_NOT_IN_GAME:
            return "Player not part of the given game";
        case PARSING_ERROR:
            return "Parsing Error";
        default:
            return "Unknown or Unimplemented error";
    }
}

void print_err(int err, const char* specific){
    fprintf(stderr, "%i %s : %s\n", err, error_to_string(err), specific);
}

size_t write_error(int err, const char* specific, char* buffer){
    size_t len = sprintf(buffer, "%i %s : %s", err, error_to_string(err), specific);
    return len;
}