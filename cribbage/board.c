#include "board.h"

Board* create_board(uint32_t nb_players){
    Board* board = calloc(1, sizeof(Board));
    
    board->deck = create_full_deck();
    board->deck_size = FULL_DECK_SIZE;
    board->middle = NULL;
    board->players_cards = NULL;
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

    free(board->deck);
    free(board);
}

void shuffle_deck(Board* board){
    for (int i = 0; i < FULL_DECK_SIZE; ++i) {
        int j = rand() % (FULL_DECK_SIZE - i);
        Card temp = board->deck[i];
        board->deck[i] = board->deck[j];
        board->deck[j] = temp;
    }
}

Card* pop_deck(Board* board){
    Card* popped = board->deck + board->deck_size-1;
    board->deck--;
    board->deck_size--;
    return popped;
}

void deal_cards(Board* board, uint32_t nb_players){
    board->players_cards = calloc(nb_players, sizeof(Card*));
    int nb_cards = nb_players == 2 ? 6 : 5;
    for(int i = 0; i < nb_players; i++){
        board->players_cards[i] = calloc(nb_cards, sizeof(Card));
        for(int j = 0; j < nb_cards; j++){
            board->players_cards[i][j] = *pop_deck(board);
        }
    }
}