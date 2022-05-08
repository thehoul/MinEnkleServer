#include "controller.h"
#include "../cribbage.h"
#include "../../server/util/server_helpers.h"
#include "../util/crib_helpers.h"
#include "../util/cribbage_rules.h"
#include "../util/errors.h"

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
uint32_t start_game(Request* req, char* body);
uint32_t join_game(Request* req, char* body);
uint32_t get_game(Request* req, char* body);
uint32_t discard_card(Request* req, char* body);
uint32_t use_card(Request* req, char* body);
uint32_t delete_game(Request* req, char* body);

struct Func funcs[] = {
    {"startGame", GET, start_game},
    {"joinGame", GET, join_game},
    {"getGame", GET, get_game},
    {"discardCard", POST, discard_card},
    {"useCard", POST, use_card},
    {"deleteGame", POST, delete_game}
};

size_t nb_func = 6;

Game* game = NULL;

uint32_t start_game(Request* req, char* body){
    if(check_nb_players(game->nb_players)){
        print_err(INVALID_ARGUMENT, "Invalid number of players");
        return write_error(INVALID_ARGUMENT, "Invalid number of players", body);
    } else {
        if(game == NULL){
            print_err(ILLEGAL_PHASE, "Game has not been created yet");
            return write_error(ILLEGAL_PHASE, "Game has not been created yet", body);
        }
        int err = deal_game(game);
        sprintf(body, "%i", NO_ERROR);
        return strlen(body);
    }
}

uint32_t delete_game(Request* req, char* body){
    if(game != NULL) {
        del_game(game);
        free(game);
        game = NULL;
    }

    sprintf(body, "%i", NO_ERROR);
    return strlen(body);
}

uint32_t get_game(Request* req, char* body){
    // Takes care of state transition before sending the game 
    update_game(game);

    if(game != NULL){
        char* game_str = to_string(game);
        snprintf(body, MAX_RESPONSE, "%i\n%s", NO_ERROR, game_str);
        return strlen(body);
    } else {
        sprintf(body, "%i Game not yet created, call createGame first", INVALID_ARGUMENT);
        return strlen(body);
    }
}

uint32_t join_game(Request* req, char* body){
    if(game == NULL){
        game = calloc(1, sizeof(Game));
        init_game(game);
    }
    uint32_t player_id = game->nb_players+1;
    add_player(game, player_id);
    sprintf(body, "%i %i", NO_ERROR, player_id);
    return strlen(body);
}

int parse_post_req(Request* req, Crib_post_req* post){

    int player = 0;
    while(player == 0){
        char* tok = strsep(&req->content, " \r\n");
        if(tok == NULL){
            return PARSING_ERROR;
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
            return PARSING_ERROR;
        }
    }

    return NO_ERROR;
}

void free_post_req(Crib_post_req* req){
    free(req->cards);
    req->cards = NULL;
}

uint32_t discard_card(Request* req, char* body){
    if(game->phase != CHOOSING){
        print_err(ILLEGAL_PHASE, "Can't discard cards if not in CHOOSING state");
        return write_error(ILLEGAL_PHASE, "Can't discard cards if not in CHOOSING state", body);
    }



    Crib_post_req post;
    int err = parse_post_req(req, &post);
    if(err){
        print_err(err, "Error parsing crib post request");
        return write_error(err, "Error parsing crib post request", body);
    }

    for(int i = 0; i < post.nb_cards; i++){
        err = player_discard(game, post.player_id, &post.cards[i]);
        printf("WOWOWOOW %s \n", error_to_string(err));
        if(err){
            print_err(err, "Couldn't discard player's card");
            return write_error(err, "Couldn't discard player's card", body);
        }
    }

    sprintf(body, "%i Card successfully discarded", NO_ERROR);
    free_post_req(&post);
    return strlen(body);
}

uint32_t use_card(Request* req, char* body){
    Crib_post_req post;
    int err = parse_post_req(req, &post);
    if(err){
        print_err(err, "Couldn't parse post request");
        return write_error(err, "Couldn't parse pot request", body);
        return strlen(body);
    }

    err = player_use(game, post.player_id, &post.cards[0]);
    if(err){
        print_err(err, "Using card didn't work");
        return write_error(err, "Using card didn't work", body);
    }

    sprintf(body, "%i", NO_ERROR);
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