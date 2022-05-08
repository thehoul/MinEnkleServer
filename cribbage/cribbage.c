#include "cribbage.h"
#include "util/crib_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Game* new_game(uint32_t* players, uint32_t nb_players){
    if(nb_players > MAX_PLAYERS){
        fprintf(stderr, "Illegal number of players. Must be bewteen 1 and %i, got %i\n", MAX_PLAYERS, nb_players);  
        return NULL;
    }

    Game* game = calloc(1, sizeof(Game));
    game->nb_players = nb_players;
    game->players = calloc(nb_players, sizeof(int));
    for(int i = 0; i < nb_players; i++){
        game->players[i] = players[i];
    }
    game->phase = CHOOSING;

    game->board = create_board(nb_players);
    shuffle_deck(game->board);
    deal_cards(game->board, game->nb_players);
    // For now the default first dealer is the first player in the list
    game->dealer = game->players[0];

    return game;
}

void del_game(Game* game){
    delete_board(game->board);
    free(game->players);
    free(game);
}

void print_game(Game* game){
    printf("Cribbage Game !\n\t Nb players : %i\n\t Phase : %i\n",
        game->nb_players, game->phase);
}

char* to_string(Game* game){
    char* str = calloc(2000, sizeof(char));
    int len = sprintf(str, "%i", game->nb_players);
    for(int i = 0; i < game->nb_players; i++){
        len += sprintf(str+len, " %i", game->players[i]);
    }
    len += sprintf(str+len, " %i\n", game->dealer);

    len += board_to_string(game->board, game->nb_players, game->players, str+len);

    

    return str;
}