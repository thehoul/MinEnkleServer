#ifndef CRIBBAGE_H
#define CRIBBAGE_H

#include "board.h"

#define MAX_PLAYERS 4

enum PHASE {
    CHOOSING, ROUND, COUNT
};

typedef struct {
    enum PHASE phase;
    int nb_players;
    int* players;
    Board* board;
} Game;

Game* new_game(uint32_t nb_players);
void del_game(Game* game);

void print_game(Game* game);
char* to_string(Game* game);

#endif