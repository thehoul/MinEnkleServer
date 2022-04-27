#include "card.h"

#include <stdio.h>
#include <stdlib.h>

Card* new_card(uint32_t val, uint32_t suit){
    if(val > 13 || suit > 4){
        fprintf(stderr, "Invalid value for suit or card value. Got : (%u, %u)\n", val, suit);
        return NULL;
    }
    Card* card = calloc(1, sizeof(Card));
    card->value = val;
    card->suit = suit;

    return card;
}

Card* create_full_deck(){
    Card* deck = calloc(4 * 13, sizeof(Card));

    Card* curr = deck;
    for(int s = 0; s < 3; s++){
        for(int v = 0; v < 13; v++){
            *curr = *new_card(v, s);
            curr++;
        }
    }

    return deck;
}

void del_card(Card* card){
    free(card);
}   

void print_card(Card* card){
    printf("Card | suit : %i\t val : %i\n", card->suit, card->value);
}

void compact_print_card(Card* card){
    printf("(%i, %i)", card->suit, card->value);
}

void print_deck(Card* deck, size_t size){
    printf("Deck of size %li : \n", size);
    for(int i = 0; i < size; i++){
        compact_print_card(deck+i);
        if(i % 13 == 0){
            printf("\n");
        } else {
            printf(" ");
        }
    }
    printf("\n");
}