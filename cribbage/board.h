#ifndef BOARD_H
#define BOARD_H

#include "card.h"

#include <stdlib.h>

typedef struct {
    Card** players_cards;
    Card* deck;
    int deck_size;
    Card* crib;
    Card* middle;
} Board;

Board* create_board(uint32_t nb_players);
void delete_board(Board* board);

void shuffle_deck(Board* board);
void deal_cards(Board* board, uint32_t nb_players);

#endif