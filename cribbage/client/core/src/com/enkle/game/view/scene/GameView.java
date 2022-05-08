package com.enkle.game.view.scene;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.utils.viewport.ScreenViewport;
import com.enkle.game.controller.Controller;
import com.enkle.game.view.model.Card;
import com.enkle.game.view.model.Deck;
import com.enkle.game.view.model.Game;

import java.util.ArrayList;
import java.util.ConcurrentModificationException;

public class GameView extends Scene {

    private static final float ui_scale = 0.1f;
    private static final float text_scale = 1f;

    private final int player_id;
    private final int game_id;
    private SceneManager sm;
    private Skin skin;
    private Stage stage;
    private Game game;
    private Controller controller;


    public GameView(int player_id, int game_id){
        this.player_id = player_id;
        this.game_id = game_id;
        this.controller = new Controller();
    }

    @Override
    public void prepareScene() {
        prepareVariables();
        prepareUI();
    }

    private void prepareVariables(){
        stage = new Stage(new ScreenViewport());
        skin  = new Skin(Gdx.files.internal("ui/uiskin.json"));
        this.game = controller.getGame();
        skin.getFont("default-font").getData().setScale(text_scale);
    }

    private void prepareUI(){
        float width = Gdx.graphics.getWidth();
        float height = Gdx.graphics.getHeight();

        setUpPlayersHand();
        setUpMiddle();
    }

    private void setUpMiddle(){
        float width = Gdx.graphics.getWidth();
        float height = Gdx.graphics.getHeight();
        float left_offset = 60f;

        Texture back = new Texture(Gdx.files.internal("cards/back.png"));
        Image deck = new Image(back);
        deck.setScale(ui_scale);
        deck.setPosition(width/2f - left_offset - deck.getWidth()*ui_scale/2f, height/2f - deck.getHeight()*ui_scale/2f);
        stage.addActor(deck);

        Label deck_label = new Label("Deck", skin);
        deck_label.setPosition(width/2f - left_offset - deck_label.getWidth()/2f,
                height/2f - 25 - deck.getHeight()*ui_scale/2f);
        stage.addActor(deck_label);
    }

    private void setUpPlayersHand(){
        Deck player_cards = game.getPlayerCards(player_id);
        int nb_cards = player_cards.getSize();
        float margin = 10;
        float card_width = player_cards.getAt(0).getImg().getWidth() * ui_scale;
        float tot_width = nb_cards * card_width + (nb_cards-1) * margin;
        float left_most = Gdx.graphics.getWidth()/2f - tot_width/2f;

        for(int i = 0; i < player_cards.getSize(); i++){
            Image img = player_cards.getAt(i).getImg();
            img.setScale(ui_scale);
            img.setPosition(left_most + i * (card_width + margin), 20);
            stage.addActor(player_cards.getAt(i).getImg());
        }

        ArrayList<Integer> players_pos = new ArrayList<>();
        switch (game.getNb_players()) {
            case 2 :
                players_pos.add(0);
                break;
            case 3 :
                players_pos.add(-1);
                players_pos.add(1);
                break;
            case 4 :
                players_pos.add(-1);
                players_pos.add(0);
                players_pos.add(1);
                break;
        }

        Texture back = new Texture(Gdx.files.internal("cards/back.png"));
        int ind = 0;
        for(int id : game.getPlayers()){
            if(id == player_id){
                continue;
            }
            int cards_cnt = game.getPlayerCards(id).getSize();
            for(int i = 0; i < cards_cnt; i++){
                Image img = new Image(back);
                img.setScale(ui_scale);
                if(players_pos.get(ind) == 0){
                    img.setPosition(left_most + i * (card_width + margin),
                            Gdx.graphics.getHeight() - 20 - img.getHeight() * ui_scale);
                } else {
                    float top_most = Gdx.graphics.getHeight()/2f - tot_width/2f;
                    img.rotateBy(90);
                    img.setPosition( players_pos.get(ind) == -1 ? img.getHeight()*ui_scale + 20 :
                                        Gdx.graphics.getWidth() - 20,
                            top_most + i * (card_width + margin));
                }
                stage.addActor(img);

            }
            ind++;

        }

    }

    @Override
    public void render(SpriteBatch batch) {
        batch.begin();
        stage.draw();
        batch.end();
    }
}
