#include "deck.h"
#include "util/errors.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void init_deck(Deck* deck){
    if(deck->cards != NULL){
        free(deck->cards);
    }
    deck->nb_cards = 0;
    deck->allocated = DEFAULT_SIZE;
    deck->cards = calloc(DEFAULT_SIZE, sizeof(Card));
}

void del_deck(Deck* deck){
    if(deck->cards != NULL){
        free(deck->cards);
    }
    deck->cards = NULL;
}

size_t push_deck(Deck* deck, Card* c){
    if(deck->nb_cards >= deck->allocated){
        deck->allocated += DEFAULT_SIZE;
        deck->cards = realloc(deck->cards, deck->allocated * sizeof(Card));
    }
    deck->cards[deck->nb_cards].suit = c->suit;
    deck->cards[deck->nb_cards].value = c->value;
    deck->nb_cards++;

    return deck->nb_cards;
}

Card* pop_deck(Deck* deck){
    if(deck->nb_cards == 0){
        return NULL;
    }
    Card* popped = &deck->cards[deck->nb_cards-1];
    deck->nb_cards--;
    return popped;
}

int rmv_deck_at(Deck* deck, int i){
    // Check index
    if(i < 0 || i >= deck->nb_cards){
        return INVALID_ARGUMENT;
    }

    for(int j = i+1; j < deck->nb_cards; j++){
        deck->cards[j-1].suit = deck->cards[j].suit;
        deck->cards[j-1].value = deck->cards[j].value;
    }
    deck->nb_cards--;
    return NO_ERROR;
}

int rmv_deck(Deck* deck, Card* c){
    for(int i = 0; i < deck->nb_cards; i++){
        if(equals(&deck->cards[i], c)){
            return rmv_deck_at(deck, i);
        }
    }
    return INVALID_ARGUMENT;
}

int deck_indexOf(Deck* deck, Card* c){
    for(int i = 0; i < deck->nb_cards; i++){
        if(equals(&deck->cards[i], c)){
            return i;
        }
    }

    return -1;
}

int deck_contains(Deck* deck, Card* c){
    return deck_indexOf(deck, c) >= 0;
}

size_t deck_to_string(Deck* deck, char* buffer){
    if(deck == NULL){
        return 0;
    }

    size_t len = 0;
    len += sprintf(buffer+len, "%li", deck->nb_cards);
    for(int i = 0; i < deck->nb_cards; i++){
        len += sprintf(buffer+len, " (%i,%i)", deck->cards[i].suit, deck->cards[i].value);
    }
    return len;
}