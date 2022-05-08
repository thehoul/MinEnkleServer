#include "card.h"

#include <stdio.h>
#include <string.h>

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

    int ind = 0;
    for(uint32_t s = 0; s < 4; s++){
        for(uint32_t v = 0; v < 13; v++){
            deck[ind].suit = s;
            deck[ind].value = v;
            ind++;
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

int deck_to_string(Card* deck, int nb_cards, char* str){
    int len = sprintf(str, "%i", nb_cards);
    for(int i = 0; i < nb_cards; i++){
        len += sprintf(str+len, " (%i,%i)", deck[i].suit, deck[i].value);
    }
    return len;
}