package com.enkle.game.view.model;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.scenes.scene2d.ui.Image;

import java.util.Objects;

public class Card {

    private final int suit;
    private final int value;
    private Image img;

    public Card(int suit, int value){
        this.suit = suit;
        this.value = value;

        Texture texture = new Texture(Gdx.files.internal(getTexturePath()));
        img = new Image(texture);
    }

    private String getTexturePath(){
        StringBuilder str = new StringBuilder("cards/white/");
        switch(suit){
            case 0 :
                str.append("Hearts_");
                break;
            case 1 :
                str.append("Pikes_");
                break;
            case 2 :
                str.append("Clovers_");
                break;
            case 3 :
                str.append("Tiles_");
                break;
            default:
                throw new IllegalArgumentException("Card suit doesnt exist, Got : " + suit);
        }
        if(value == 0){
            str.append("A_");
        } else if(value < 10){
            str.append(value+1);
            str.append("_");
        } else {
            switch (value){
                case 10 :
                    str.append("Jack_");
                    break;
                case 11 :
                    str.append("Queen_");
                    break;
                case 12 :
                    str.append("King_");
                    break;
                default :
                    throw new IllegalArgumentException("Card values is not valid. Got : " + value);
            }
        }

        str.append("white.png");
        return str.toString();
    }

    public Image getImg() {
        return img;
    }

    public int getSuit() {
        return suit;
    }

    public int getValue() {
        return value;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Card card = (Card) o;
        return suit == card.suit && value == card.value;
    }

    @Override
    public int hashCode() {
        return Objects.hash(suit, value);
    }
}
