#ifndef BOARD_H
#define BOARD_H

#include "card.h"

#include <stdlib.h>

typedef struct {
    Card** players_cards;
    size_t* players_nb_cards;
    Card** players_used_cards;
    size_t* players_nb_used; 
    Card* deck;
    size_t deck_size;
    Card* crib;
    size_t crib_size;
    Card* middle;
    size_t nb_middle;
    unsigned int middle_count;
} Board;

Board* create_board(uint32_t nb_players);
void delete_board(Board* board);

void shuffle_deck(Board* board);
void deal_cards(Board* board, uint32_t nb_players);

int discard_player_card(Board* board, int player, int suit, int val);
int use_card_player(Board* board, int player, int suit, int val);

char* board_to_string(Board* board, int nb_players);

#endif