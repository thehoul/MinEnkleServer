#ifndef CARD_H
#define CARD_H

#include <stdint.h>
#include <stdlib.h>

#define FULL_DECK_SIZE (13 * 4)

typedef struct {
    int value;
    int suit;
} Card;

Card* new_card(uint32_t val, uint32_t suit);
Card* create_full_deck();
void del_card(Card* card);

void print_card(Card* card);

char* deck_to_string(Card* deck, int nb_cards);

#endif