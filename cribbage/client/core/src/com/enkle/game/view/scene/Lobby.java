package com.enkle.game.view.scene;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.scenes.scene2d.ui.TextButton;
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener;
import com.badlogic.gdx.utils.viewport.ScreenViewport;
import com.enkle.game.controller.Controller;
import com.enkle.game.view.model.Game;
import com.enkle.game.view.util.MyToast;

public class Lobby extends Scene {

    private Stage stage;
    private Skin skin;
    private Controller controller;

    private Label players_txt;

    private final int player_id;
    private final int game_id;
    private Game game;

    public Lobby(int player_id, int game_id){
        this.player_id = player_id;
        this.game_id = game_id;
        controller = new Controller();
    }

    @Override
    public void prepareScene() {
        prepareVariables();
        prepareUI();
    }

    private void prepareUI(){
        float width = Gdx.graphics.getWidth();
        float height = Gdx.graphics.getHeight();
        float ui_height = 10;

        /* PLAYER  AND GAME ID LABEL */
        Label text_id = new Label("Player ID : " + player_id + " || Game ID : " + game_id , skin);
        text_id.setHeight(ui_height);
        text_id.setPosition(width/2f - text_id.getWidth()/2f,
                height - text_id.getHeight() - 30);
        stage.addActor(text_id);

        /* NB PLAYER LABEL */
        players_txt = new Label("Players In Lobby : " + game.getNb_players(), skin);
        players_txt.setHeight(ui_height);
        players_txt.setPosition(width/2f - players_txt.getWidth()/2f,
                height - players_txt.getHeight() - 100);
        stage.addActor(players_txt);

        /* START GAME BUTTON */
        TextButton btn = new TextButton("Start Game", skin);
        btn.setPosition(width/2f - btn.getWidth()/2f, height/2f - btn.getHeight()/2f);
        btn.addListener(new ClickListener() {
            @Override
            public void clicked(InputEvent event, float x, float y) {

                if(controller.startGame()){
                    sm.Push(new GameView(player_id, game_id));
                } else {
                    MyToast.makeToast("Can't start game yet", 2000, stage);
                }
            }
        });

        stage.addActor(btn);
        Gdx.input.setInputProcessor(stage);
    }

    private void prepareVariables(){
        stage = new Stage(new ScreenViewport());
        skin =  new Skin(Gdx.files.internal("ui/uiskin.json"));
        skin.getFont("default-font").getData().setScale(3f);
        game = controller.getGame();
    }

    @Override
    public void render(SpriteBatch batch) {
        game = controller.getGame();
        players_txt.setText("Players In Lobby : " + game.getNb_players());
        batch.begin();
        stage.draw();
        batch.end();
    }
}
