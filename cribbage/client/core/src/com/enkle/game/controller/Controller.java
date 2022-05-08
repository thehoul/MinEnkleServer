package com.enkle.game.controller;

import com.enkle.game.view.model.Game;
import com.enkle.game.view.util.MyToast;

public class Controller {

    public static final String GETGAME = "GET /cribbage/getGame HTTP/1.1\r\n";
    public static final String STARTGAME = "GET /cribbage/startGame HTTP/1.1\r\n";
    public static final String JOINGAME = "GET /cribbage/joinGame HTTP/1.1\r\n";

    Communicator comm;

    public Controller(){
        comm = new Communicator();
    }

    public int joinGame(){
        Response resp = comm.sendRequest(JOINGAME);

        if(resp.getError().getErrCode() != 0){
            System.out.println(resp.getError().getErrString());
            return 0;
        } else {
            int player_id = Integer.parseInt(resp.getContent());
            return player_id;
        }
    }

    public boolean startGame(){
        Response resp = comm.sendRequest(STARTGAME);

        if(resp.getError().getErrCode() != 0){
            System.out.println(resp.getError().getErrString());
            return false;
        }

        return true;
    }

    public Game getGame(){
        Response resp = comm.sendRequest(GETGAME);

        Game game = Game.fromString(resp.getContent());

        return game;
    }
}
