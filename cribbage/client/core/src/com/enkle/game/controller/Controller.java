package com.enkle.game.controller;

public class Controller {

    Communicator comm;

    public Controller(){
        comm = new Communicator();
    }

    public int joinGame(){
        String req = "GET /cribbage/joinGame HTTP/1.1\r\n";
        Response resp = comm.sendRequest(req);

        int player_id = Integer.parseInt(resp.getContent());

        System.out.println("Content : " + resp.getContent());
        return player_id;
    }
}
