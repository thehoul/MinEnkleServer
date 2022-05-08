#ifndef CRIBBAGE_H
#define CRIBBAGE_H

#include "deck.h"

enum PHASE {
    BUILDING, CHOOSING, ROUND, COUNT
};

typedef struct {
    enum PHASE phase;
    uint32_t nb_players;
    uint32_t* players;
    uint32_t dealer;
    Deck* hands;
    Deck* used_cards;
    Deck crib;
    Deck middle;
    Deck deck;
} Game;

int init_game(Game* game);
void del_game(Game* game);

void add_player(Game* game, uint32_t player_id);
int deal_game(Game* game);
void update_game(Game* game);

int player_discard(Game* game, uint32_t player, Card* c);
int player_use(Game* game, uint32_t player, Card* c);

void print_game(Game* game);
char* to_string(Game* game);

#endif