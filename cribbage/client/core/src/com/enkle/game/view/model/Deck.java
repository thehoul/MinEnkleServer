package com.enkle.game.view.model;

import java.util.ArrayList;
import java.util.List;

public class Deck {

    private List<Card> deck;

    public Deck(){
        deck = new ArrayList<>();
    }

    public void addCard(Card c){
        deck.add(c);
    }

    public int getSize(){
        return deck.size();
    }

    public Card getAt(int i){
        return deck.get(i);
    }

    public Card popAt(int i){
        return deck.remove(i);
    }

    public Card pop(){
        return deck.remove(deck.size()-1);
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        for(int i = 0; i < getSize(); i++){
            Card c = getAt(i);
            str.append("(" + c.getSuit() + "," + c.getValue() + ") ");
        }

        return str.toString();
    }
}
