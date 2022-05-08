package com.enkle.game.controller;

public class Error {

    private final Errors err;
    private final String specific;

    public Error(Errors err, String specific){
        this.err = err;
        this.specific = specific;
    }

    public static Error fromString(String err_str){
        String[] splitted = err_str.split(" ");
        Errors err = Errors.values()[Integer.parseInt(splitted[0])];
        if(splitted.length == 2){

            return new Error(err, splitted[1]);
        } else {
            return new Error(err, err.toString());
        }
    }

    public int getErrCode(){
        return err.ordinal();
    }

    public String getErrString(){
        return err.toString() + " " + specific;
    }

    public enum Errors {
        NO_ERROR("No Error"),
        ILLEGAL_PHASE("Illegal Phase"),
        INVALID_ARGUMENT("Invalid Argument"),
        PLAYER_NOT_IN_GAME("Player not part of the game"),
        PARSING_ERROR("Parsing Error");

        private final String str;

        Errors(String str){
            this.str = str;
        }

        @Override
        public String toString() {
            return str;
        }
    }
}
