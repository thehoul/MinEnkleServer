#include "board.h"

#include <stdio.h>
#include <string.h>

Board* create_board(uint32_t nb_players){
    Board* board = calloc(1, sizeof(Board));
    
    board->deck = create_full_deck();
    board->deck_size = FULL_DECK_SIZE;
    board->middle = NULL;
    board->players_cards = NULL;
    board->players_nb_cards = NULL;
    board->players_used_cards = NULL;
    board->players_nb_used = NULL;
    board->crib = NULL;

    return board;
}

void delete_board(Board* board){
    if(board->crib != NULL){
        free(board->crib);
    }
    if(board->middle != NULL){
        free(board->middle);
    }
    if(board->players_cards != NULL){
        free(board->players_cards);
    }

    if(board->players_nb_cards != NULL){
        free(board->players_nb_cards);
    }

    if(board->players_nb_used != NULL) {
        free(board->players_nb_used);
    }

    if(board->players_used_cards != NULL){
        free(board->players_used_cards);
    }

    free(board->deck);
    free(board);
}

void shuffle_deck(Board* board){
    printf("Shuffling deck\n"); 
    for (int i = 0; i < board->deck_size; ++i) {
        int j = rand() % (board->deck_size);
        if(j != i){
            Card temp = board->deck[i];
            board->deck[i] = board->deck[j];
            board->deck[j] = temp;
        }
    }
}

Card* pop_deck(Board* board){
    Card* popped = board->deck + board->deck_size-1;
    board->deck_size--;
    return popped;
}

void add_card_deck(Card** deck, size_t* deck_size, int suit, int val){
    *deck = realloc(*deck, (*deck_size)+1);
    (*deck)[*deck_size].suit = suit;
    (*deck)[*deck_size].value = val;
    (*deck_size)++;
}

void deal_cards(Board* board, uint32_t nb_players){
    board->players_cards = calloc(nb_players, sizeof(Card*));
    board->players_nb_cards = calloc(nb_players, sizeof(int));

    board->players_used_cards = calloc(nb_players, sizeof(Card*));
    board->players_nb_used = calloc(nb_players, sizeof(int));

    int nb_cards = nb_players == 2 ? 6 : 5;
    for(int i = 0; i < nb_players; i++){
        board->players_nb_cards[i] = nb_cards;
        board->players_nb_used[i] = 0;
        board->players_cards[i] = calloc(nb_cards, sizeof(Card));
        for(int j = 0; j < nb_cards; j++){
            Card* popped = pop_deck(board);
            board->players_cards[i][j].suit = popped->suit;
            board->players_cards[i][j].value = popped->value;
        }
    }

    if(nb_players == 3){
        Card* extra_crib = pop_deck(board);
        add_card_deck(&board->crib, &board->crib_size, extra_crib->suit, extra_crib->value);
    }
}


int get_card_index(Card* deck, int size, int player, int suit, int val){
    for(int i = 0; i < size; i++){
        if(deck[i].suit == suit &&
            deck[i].value == val){
            return i;
        }
    }
    printf("card not in deck\n");
    return -1;
}

int discard_player_card(Board* board, int player, int suit, int val){
    int index = get_card_index(board->players_cards[player], board->players_nb_cards[player],
         player, suit, val);
    if(index < 0){
        return index;
    }
    for(int j = index+1; j < board->players_nb_cards[player]; j++){
        board->players_cards[player][j-1].suit = board->players_cards[player][j].suit;
        board->players_cards[player][j-1].value = board->players_cards[player][j].value;
    }
    board->players_nb_cards[player]--;
    add_card_deck(&board->crib, &board->crib_size, suit, val);
    return index;
}

int use_card_player(Board* board, int player, int suit, int val){
    // Check that the card is contained in the player's hand
    if(get_card_index(board->players_cards[player], board->players_nb_cards[player],
        player, suit, val) < 0){
        printf("Card (%i,%i) not in the player's hand\n", suit, val);
        return -1;
    }
    // Check that the card is not contained in the used cards
    if(get_card_index(board->players_used_cards[player], board->players_nb_used[player],
        player, suit, val) >= 0){
        printf("Card has already been used\n");
        return -1;
    }
    add_card_deck(&board->players_used_cards[player], &board->players_nb_used[player], suit, val);
    add_card_deck(&board->middle, &board->nb_middle, suit, val);
    return 0;
}

int board_to_string(Board* board, int nb_players, int* players, char* str){
    char* tail = str;
    for(int i = 0; i < nb_players; i++){
        tail += sprintf(tail, "%i ", players[i]);
        tail += deck_to_string(board->players_cards[i], board->players_nb_cards[i], tail);
        tail += sprintf(tail, "\n");
        tail += deck_to_string(board->players_used_cards[i], board->players_nb_used[i], tail);
        tail += sprintf(tail, "\n");    
    }
    tail += deck_to_string(board->crib, board->crib_size, tail);
    tail += sprintf(tail, "\n");
    tail += deck_to_string(board->middle, board->middle_count, tail);
    tail += sprintf(tail, "\n");
    tail += deck_to_string(board->deck, board->deck_size, tail);

    return strlen(tail) - strlen(str);
}