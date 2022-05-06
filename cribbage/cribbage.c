#include "cribbage.h"
#include "util/crib_helpers.h"

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
    snprintf(str, 2000, "Cribbage Game !\n"
        "\t Nb players : %i\n"
        "\t Phase : %s\n"
        "%s",
        game->nb_players, int_to_phase(game->phase), board_to_string(game->board, game->nb_players));

    return str;
}