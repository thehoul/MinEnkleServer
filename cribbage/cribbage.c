#include "cribbage.h"

#include <stdio.h>
#include <stdlib.h>

Game* new_game(uint32_t nb_players){
    if(nb_players > MAX_PLAYERS){
        fprintf(stderr, "Illegal number of players. Must be bewteen 1 and %i, got %i\n", MAX_PLAYERS, nb_players);  
        return NULL;
    }

    Game* game = calloc(1, sizeof(Game));
    game->nb_players = nb_players;
    game->players = calloc(nb_players, sizeof(int));
    game->phase = CHOOSING;

    game->board = create_board(nb_players);
    shuffle_deck(game->board);
    deal_cards(game->board, game->nb_players);

    return game;
}
