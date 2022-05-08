package com.enkle.game.controller;

import com.enkle.game.view.model.Game;

public class Controller {

    public static final String GETGAME = "GET /cribbage/getGame HTTP/1.1\r\n";
    public static final String CREATEGAME = "GET /cribbage/createGame HTTP/1.1\r\n";
    public static final String JOINGAME = "GET /cribbage/joinGame HTTP/1.1\r\n";

    Communicator comm;

    public Controller(){
        comm = new Communicator();
    }

    public int joinGame(){
        Response resp = comm.sendRequest(JOINGAME);

        int player_id = Integer.parseInt(resp.getContent());

        return player_id;
    }

    public int createGame(){
        Response resp = comm.sendRequest(CREATEGAME);
        int game_id = Integer.parseInt(resp.getContent());

        return game_id;
    }

    public Game getGame(){
        Response resp = comm.sendRequest(GETGAME);

        Game game = Game.fromString(resp.getContent());

        return game;
    }
}
