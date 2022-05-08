package com.enkle.game.controller;

import java.nio.charset.StandardCharsets;

public class Parser {

    private Parser(){}

    private static Error getError(String content){
        return Error.fromString(content.split("\n")[0]);
    }


    public static Response parseResponse(byte[] data){
        Response.HTTPv httpv;
        int status;
        int content_len;
        Error error;
        StringBuilder content;

        String data_str = new String(data, StandardCharsets.US_ASCII);
        System.out.println("Parsing : " + data_str.length());

        String[] line = data_str.split("\n");
        String[] split = line[0].split(" ");
        if(split[0] == "HTTP/1.1"){
            httpv = Response.HTTPv.HTTP11;
        } else {
            httpv = Response.HTTPv.UNKNWN;
        }
        status = Integer.parseInt(split[1]);

        content_len = Integer.parseInt(line[2].split(" ")[1]);
        int content_nb_lines = line.length - 3 - 3;
        error = getError(line[4]);
        content = new StringBuilder();
        for(int i = 0; i < content_nb_lines; i++){
            if(i == content_nb_lines-1){
                content.append(line[5 + i]);
            } else{
                content.append(line[5 + i]  + "\n");
            }

        }

        return new Response(status, httpv, content.toString(), error, content_len);
    }




}


