#include "cribbage_rules.h"
#include "errors.h"

int check_nb_players(uint32_t nb_players){
    if(nb_players < MIN_PLAYERS & nb_players > MAX_PLAYERS){
        return INVALID_ARGUMENT;
    } else {
        return NO_ERROR;
    }
}