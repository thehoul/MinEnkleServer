package com.enkle.game.controller;

import java.nio.charset.StandardCharsets;

public class Parser {

    private Parser(){}

    public static Response parseResponse(byte[] data){
        Response.HTTPv httpv;
        int status;
        int content_len;
        String content;

        String data_str = new String(data, StandardCharsets.US_ASCII);

        String[] line = data_str.split("\n");
        String[] split = line[0].split(" ");
        if(split[0] == "HTTP/1.1"){
            httpv = Response.HTTPv.HTTP11;
        } else {
            httpv = Response.HTTPv.UNKNWN;
        }
        status = Integer.parseInt(split[1]);

        content_len = Integer.parseInt(line[2].split(" ")[1]);
        content = line[4];

        return new Response(status, httpv, content, content_len);
    }




}


