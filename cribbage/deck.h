#ifndef DECK_H
#define DECK_H

#include "card.h"

#define DEFAULT_SIZE 6

typedef struct {
    Card* cards;
    size_t allocated;
    size_t nb_cards;
} Deck;

void init_deck(Deck* deck);
void del_deck(Deck* deck);

size_t push_deck(Deck* deck, Card* c);
Card* pop_deck(Deck* deck);
int rmv_deck_at(Deck* deck, int i);
int rmv_deck(Deck* deck, Card* c);

int deck_indexOf(Deck* deck, Card* c);
int deck_contains(Deck* deck, Card* c);

size_t deck_to_string(Deck* deck, char* buffer);



#endif