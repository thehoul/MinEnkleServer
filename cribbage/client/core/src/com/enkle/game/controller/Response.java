package com.enkle.game.controller;

public class Response {
    private final int status;
    private final HTTPv httpv;
    private final String content;
    private final Error error;
    private final int conent_len;

    public Response(int status, HTTPv httpv, String content, Error error, int content_len){
        this.status = status;
        this.httpv = httpv;
        this.content = content;
        this.error = error;
        this.conent_len = content_len;
    }

    public HTTPv getHttpv() {
        return httpv;
    }

    public int getStatus() {
        return status;
    }

    public String getContent() {
        return content;
    }

    public Error getError() {
        return error;
    }

    public int getConent_len() {
        return conent_len;
    }

    public enum HTTPv{
        HTTP11, UNKNWN
    }
}
