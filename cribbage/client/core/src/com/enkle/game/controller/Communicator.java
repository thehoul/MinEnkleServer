package com.enkle.game.controller;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class Communicator {

    private Socket socket;

    private static final String Host = "localhost";
    private static final int Port = 8000;

    public Communicator(){

    }

    private void connect(){

        try {
            socket = new Socket(Host, Port);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public Response sendRequest(String req){
        connect();
        try {
            OutputStream out = socket.getOutputStream();
            InputStream in = socket.getInputStream();
            out.write(req.getBytes(StandardCharsets.UTF_8));
            byte[] data = new byte[100];
            in.read(data);
            Response response = Parser.parseResponse(data);
            if(!socket.isClosed()){
                socket.close();
            }
            return response;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }


}
