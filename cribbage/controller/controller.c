#include "controller.h"
#include "../cribbage.h"
#include "../../server/util/server_helpers.h"
#include "../util/crib_helpers.h"

#include <string.h>
#include <stdio.h>

#define MAX_RESPONSE 700

typedef struct {
    int player_id;
    int nb_cards;
    Card* cards;
} Crib_post_req;

struct Func{
    const char* name;
    enum ReqType type;
    uint32_t (*func)(Request* req, char*);
};

// Declaring function to be able to use them in the funcs list below
uint32_t create_game(Request* req, char* body);
uint32_t join_game(Request* req, char* body);
uint32_t get_game(Request* req, char* body);
uint32_t discard_card(Request* req, char* body);
uint32_t use_card(Request* req, char* body);

struct Func funcs[] = {
    {"createGame", GET, create_game},
    {"joinGame", GET, join_game},
    {"getGame", GET, get_game},
    {"discardCard", POST, discard_card},
    {"useCard", POST, use_card},
};

size_t nb_func = 5;

Game* game = NULL;
uint32_t nb_players = 0;
uint32_t* players;

void check_state(){
    switch(game->phase){
        case CHOOSING:
            if(game->board->crib_size == 4){
                game->phase = ROUND;
            }
            break;
        case ROUND:
            break;
        case COUNT:
            break;
        default:
            break;
    }
}

uint32_t create_game(Request* req, char* body){
    if(nb_players < 2 || nb_players > 4){
        sprintf(body, "0");
        return strlen(body);
    }
    if(game != NULL){
        del_game(game);
    }
    game = new_game(players, nb_players);
    sprintf(body, "1");
    return strlen(body);
}

uint32_t get_game(Request* req, char* body){
    // Takes care of state transition before sending the game 
    check_state();

    if(game != NULL){
        char* game_str = to_string(game);
        snprintf(body, MAX_RESPONSE, "%s", game_str);
        return strlen(body);
    } else {
        sprintf(body, "Game not yet created, call createGame first");
        return strlen(body);
    }
}

uint32_t join_game(Request* req, char* body){
    players = realloc(players, sizeof(int) * (nb_players+1));
    players[nb_players] = nb_players+1;
    sprintf(body, "%i", ++nb_players);
    return strlen(body);
}

int parse_post_req(Request* req, Crib_post_req* post){

    int player = 0;
    while(player == 0){
        char* tok = strsep(&req->content, " \r\n");
        if(tok == NULL){
            return -1;
        }
        player = atoi(tok);
    }
    post->player_id = player;

    post->nb_cards = atoi(strsep(&req->content, " "));

    post->cards = calloc(post->nb_cards, sizeof(Card));
    for(int i = 0; i < post->nb_cards; i++){
        char* card_str = strsep(&req->content, " ");
        if(sscanf(card_str, "(%i,%i)", &post->cards[i].suit, &post->cards[i].value) != 2){
            free(post->cards);
            return -1;
        }
    }

    return 0;
}

uint32_t discard_card(Request* req, char* body){
    if(game->phase != CHOOSING){
        sprintf(body, "Can't discard cards in phase %s", int_to_phase(game->phase));
        return strlen(body);
    }

    Crib_post_req post;
    parse_post_req(req, &post);

    if(post.player_id < 0){
        sprintf(body, "Error reading discard POST");
        return strlen(body);
    } 

    if(post.nb_cards == 0){
        sprintf(body, "Can't discard 0 cards");
        return strlen(body);
    }

    for(int i = 0; i < post.nb_cards; i++){
        if(discard_player_card(game->board, post.player_id-1, post.cards[i].suit, post.cards[i].value) < 0){
            sprintf(body, "Couldn't discard : (%i,%i)\n", post.cards[i].suit, post.cards[i].value);
            return strlen(body);
        }
    }
    sprintf(body, "Card successfully discarded");
    free(post.cards);
    return strlen(body);
}

uint32_t use_card(Request* req, char* body){
    printf("USING CARD\n");
    Crib_post_req post;
    parse_post_req(req, &post);
    if(post.nb_cards > 1){
        sprintf(body, "Can't use more than one card at once");
        return strlen(body);
    }

    if(use_card_player(game->board, post.player_id-1, post.cards[0].suit, post.cards[0].value) < 0){
        sprintf(body, "Couldn't use the given card");
        return strlen(body);
    }

    sprintf(body, "Card successfully used");
    return strlen(body);
}

void handle_request(Request* req, int client){
    printf("Crib req  : %s\n", req->requested);

    for(int i = 0; i < nb_func; i++){
        if(strstr(req->requested, funcs[i].name) != NULL && req->type == funcs[i].type){
            char* body = calloc(MAX_RESPONSE, sizeof(char));
            int len = funcs[i].func(req, body);
            send_response(req->httpv, "text/plain", len, body, client);
            free(body);
        }
    }
}