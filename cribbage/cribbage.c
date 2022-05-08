#include "cribbage.h"
#include "util/crib_helpers.h"
#include "util/cribbage_rules.h"
#include "util/errors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int init_game(Game* game){
    game->phase = BUILDING;
    game->nb_players = 0;

    init_deck(&game->crib);
    init_deck(&game->middle);
    init_deck(&game->deck);

    return NO_ERROR;
}

int get_player_index(Game* game, uint32_t player){
    for(int i = 0; i < game->nb_players; i++){
        if(game->players[i] == player){
            return i;
        }
    }
    return -1;
}

void add_player(Game* game, uint32_t player_id){
    if(get_player_index(game, player_id) >= 0){
        return; // Player is already in the game
    }
    // Add the player to the list
    game->players = realloc(game->players, sizeof(uint32_t) * (game->nb_players+1));
    game->players[game->nb_players] = player_id;

    // Initialise the player's cards
    game->hands = realloc(game->hands, sizeof(Deck) * (game->nb_players+1));
    init_deck(&game->hands[game->nb_players]);
    game->used_cards = realloc(game->used_cards, sizeof(Deck) * (game->nb_players +1));
    init_deck(&game->used_cards[game->nb_players]);
    game->nb_players++;
}

void del_game(Game* game){
    free(game->players);
    game->players = NULL;
    for(int i = 0; i < game->nb_players; i++){
        del_deck(&game->hands[i]);
        del_deck(&game->used_cards[i]);
    }
    free(game->hands);
    game->hands = NULL;
    free(game->used_cards);
    game->used_cards = NULL;
    del_deck(&game->crib);
    del_deck(&game->middle);
    del_deck(&game->deck);
}

void get_full_deck(Deck* deck){
    while(deck->nb_cards > 0){
        pop_deck(deck);
    }
    for(int s = 0; s < 4; s++){
        for(int v = 0; v < 13; v++){
            Card c = {.suit = s, .value = v};
            push_deck(deck, &c);
        }
    }
}

void shuffle_deck(Deck* deck){
    for(int i = 0; i < deck->nb_cards; i++){
        int newI = rand() % deck->nb_cards;
        if(newI != i){
            Card tmp = deck->cards[i];
            deck->cards[i] = deck->cards[newI];
            deck->cards[newI] = tmp;
        }
    }
}

int deal_game(Game* game){
    if(game->phase != BUILDING){
        return NO_ERROR; // Game has already been dealt
    }
    if(check_nb_players(game->nb_players)){
        print_err(INVALID_ARGUMENT, "Invalid number of player, must be between 2 and 4");
        fprintf(stderr, "Invalid number of players, must be between %i and %i. Got %i\n",
            MIN_PLAYERS, MAX_PLAYERS, game->nb_players);
        return INVALID_ARGUMENT;
    }
    int card_per_player = game->nb_players == 2 ? 6 : 5;

    get_full_deck(&game->deck);
    shuffle_deck(&game->deck);

    /*
    */
    for(int p = 0; p < game->nb_players; p++){
        for(int i = 0; i < card_per_player; i++){
            push_deck(&(game->hands[p]), pop_deck(&game->deck));
        }
    }

    // When there are 3 players, the crib needs a fourth card from the deck
    if(game->nb_players == 3){
        push_deck(&game->crib, pop_deck(&game->deck));
    }

    // Randomly select a player to be the first dealer
    game->dealer = game->players[rand() % game->nb_players];
    game->phase = CHOOSING;
    return NO_ERROR;
}

void update_game(Game* game){
    switch(game->phase){
        case BUILDING:
            break;
        case CHOOSING:
            if(game->crib.nb_cards != 4){
                return;
            }
            for(int i = 0; i < game->nb_players; i++){
                if(game->hands[i].nb_cards != 4){
                    return;
                }
            }
            // If we reach this code, then all condition to start the rounds have been met
            game->phase = ROUND;
            break;
        case ROUND:
            break;
        case COUNT:
            break;
        default:
            break;
    }
}



int player_discard(Game* game, uint32_t player, Card* c){
    int index = get_player_index(game, player);
    if(index  < 0){
        return PLAYER_NOT_IN_GAME;
    }
    int err = rmv_deck(&game->hands[index], c);
    if(err)
        return err;

    push_deck(&game->crib, c);
    return NO_ERROR;
}

int player_use(Game* game, uint32_t player, Card* c){
    int index = get_player_index(game, player);
    if(index < 0){
        return PLAYER_NOT_IN_GAME;
    }

    // Check that the player has the card and that it has not already been used
    if(!deck_contains(&game->hands[index], c) ||
        deck_contains(&game->used_cards[index], c)){
        return INVALID_ARGUMENT;
    }

    push_deck(&game->used_cards[index], c);
    push_deck(&game->middle, c);
    return NO_ERROR;
}

char* to_string(Game* game){
    char* str = calloc(2000, sizeof(char));
    char* tail = str;
    tail += sprintf(tail, "%i", game->nb_players);
    for(int i = 0; i < game->nb_players; i++){
        tail += sprintf(tail, " %i", game->players[i]);
    }
    tail += sprintf(tail, " %i\n%i\n", game->dealer, game->phase);

    for(int i = 0; i < game->nb_players; i++){
        tail += sprintf(tail, "%i ", game->players[i]);
        tail += deck_to_string(&game->hands[i], tail);
        tail += sprintf(tail, "\n");
        tail += deck_to_string(&game->used_cards[i], tail);
        tail += sprintf(tail, "\n");
    }

    tail += deck_to_string(&game->crib, tail);
    tail += sprintf(tail, "\n");
    tail += deck_to_string(&game->middle, tail);
    tail += sprintf(tail, "\n");
    tail += deck_to_string(&game->deck, tail);

    return str;
}