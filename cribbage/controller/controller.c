#include "controller.h"
#include "../cribbage.h"
#include "../../server/util/helpers.h"

#include <string.h>
#include <stdio.h>

Game* game = NULL;
int nb_players = 0;
int* players;

void create_game(){
    if(game == NULL){
        game = new_game(nb_players);
        
    }
}

uint32_t joinGame(){
    players = realloc(players, sizeof(int) * (nb_players+1));
    players[nb_players] = nb_players;
    return nb_players++;
}

void handle_request(Request* req, int client){

    if(strstr(req->requested, "joinGame") != NULL){
        uint32_t id = joinGame();
        char body[100];
        snprintf(body, 100, "Player ID : %u", id);
        send_response(req->httpv, "text/plain", strlen(body), body, client);
    } else if(strstr(req->requested, "createGame") != NULL){
        create_game();
        send_OK(req->httpv, client);
    } else if(strstr(req->requested, "getGame") != NULL){
        if(game != NULL){
            // TODO : send game
        } else {
            send_OK(req->httpv, client);
        }
    }
}