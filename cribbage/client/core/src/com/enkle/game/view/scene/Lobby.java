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
import com.enkle.game.view.util.MyToast;

public class Lobby extends Scene {

    private Stage stage;
    private Skin skin;
    private Controller controller;

    private final int player_id;

    public Lobby(int player_id){
        this.player_id = player_id;
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

        Label text = new Label("Player ID : " + player_id, skin);
        text.setPosition(width/2f - text.getWidth()/2f, height - text.getHeight() - 10);
        text.setHeight(ui_height);

        stage.addActor(text);

        TextButton btn = new TextButton("Start Game", skin);
        btn.setPosition(width/2f - btn.getWidth()/2f, height/2f - btn.getHeight()/2f);
        btn.addListener(new ClickListener() {
            @Override
            public void clicked(InputEvent event, float x, float y) {
                int game_id = controller.createGame();
                if(game_id > 0){
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
    }

    @Override
    public void render(SpriteBatch batch) {
        batch.begin();
        stage.draw();
        batch.end();
    }
}
