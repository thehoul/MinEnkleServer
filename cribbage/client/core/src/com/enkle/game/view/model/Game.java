package com.enkle.game.view.model;

import java.util.ArrayList;
import java.util.List;

public class Game {

    private final int nb_players;
    private final List<Integer> players;
    private final int dealer;
    private List<Deck> players_card;
    private List<Deck> players_used;
    private Deck crib;
    private Deck middle;
    private Deck deck;

    public Game(List<Integer> players, int dealer){
        this.nb_players = players.size();
        this.players = players;
        this.dealer = dealer;
        players_card = new ArrayList<>(nb_players);
        players_used = new ArrayList<>(nb_players);
        for(int i = 0; i < nb_players; i++){
            players_card.add(new Deck());
            players_used.add(new Deck());
        }
        crib = new Deck();
        middle = new Deck();
        deck = new Deck();
    }

    public int getNb_players() {
        return nb_players;
    }

    public int getPlayerID(int i ){
        return players.get(i);
    }

    public List<Integer> getPlayers(){
        return players;
    }

    public void setPlayers_card(int player, Deck deck){
        if(!players.contains(player)){
            return;
        }
        players_card.set(players.indexOf(player), deck);
    }

    public void setPlayers_used(int player, Deck deck){
        if(!players.contains(players.indexOf(player))){
            return;
        }
        players_used.set(players.indexOf(player), deck);
    }

    public void addDeckCard(Card c){
        deck.addCard(c);
    }
    public void addCribCard(Card c){
        crib.addCard(c);
    }
    public void addMiddleCard(Card c){
        middle.addCard(c);
    }

    private static Card parseCard(String card_str){
        int suit; int value;

        String stripped = card_str.replace("(", "");
        stripped = stripped.replace(")", "");
        String[] splitted = stripped.split(",");
        if(splitted.length != 2){
            throw new IllegalArgumentException("Can't parse card : " + card_str);
        }
        suit = Integer.parseInt(splitted[0]);
        value = Integer.parseInt(splitted[1]);

        return new Card(suit, value);
    }

    public Deck getPlayerCards(int player){
        return players_card.get(players.indexOf(player));
    }

    public static Game fromString(String game_str){
        String[] lines = game_str.split("\n");
        String[] info_str = lines[0].split(" ");
        int nb_players = Integer.parseInt(info_str[0]);
        List<Integer> players = new ArrayList<>(nb_players);
        for(int i = 0; i < nb_players; i++){
            players.add(Integer.parseInt(info_str[i + 1]));
        }
        int dealer = Integer.parseInt(info_str[1 + nb_players]);
        Game game = new Game(players, dealer);

        // Getting each player's hands and used cards

        for(int i = 0; i < nb_players; i++){
            String[] player_str = lines[2*i + 1].split(" ");
            int player_id = Integer.parseInt(player_str[0]);

            // Parsing player's cards
            int nb_cards = Integer.parseInt(player_str[1]);
            Deck deck = new Deck();
            for(int j = 0; j < nb_cards; j++){
                deck.addCard(parseCard(player_str[j+2]));
            }
            game.setPlayers_card(player_id, deck);

            // Parsing player's used cards
            Deck used = new Deck();
            String[] used_str = lines[2*i + 2].split(" ");
            int nb_used = Integer.parseInt(used_str[0]);
            for(int j = 0; j < nb_used; j++){
                used.addCard(parseCard(used_str[j+1]));
            }
            game.setPlayers_used(player_id, used);
        }

        System.out.println("NB PLAYERS : " + nb_players);
        // Parsing the crib cards
        String[] crib_str = lines[1 + nb_players * 2].split(" ");
        int crib_size = Integer.parseInt(crib_str[0]);
        for(int i = 0; i < crib_size; i++){
            game.addCribCard(parseCard(crib_str[i+1]));
        }

        // Parsing middle cards
        String[] middle_str = lines[2 + nb_players * 2].split(" ");
        int nb_middle = Integer.parseInt(middle_str[0]);
        for(int i = 0; i < nb_middle; i++){
            game.addMiddleCard(parseCard(middle_str[i+1]));
        }

        // Parsing deck
        String[] deck_str = lines[3 + nb_players * 2].split(" ");
        int deck_size = Integer.parseInt(deck_str[0]);
        for(int i = 0; i < deck_size; i++){
            game.addDeckCard(parseCard(deck_str[i+1]));
        }

        return game;
    }
}
