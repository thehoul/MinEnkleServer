package com.enkle.game.view.scene;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.scenes.scene2d.ui.TextButton;
import com.badlogic.gdx.scenes.scene2d.ui.TextField;
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener;
import com.badlogic.gdx.utils.viewport.ScreenViewport;
import com.enkle.game.controller.Controller;

public class MainView extends Scene{

    private Stage stage;
    private Skin skin;
    private Controller controller;


    public MainView(){
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

        final TextField game_id_txt = new TextField("", skin);
        game_id_txt.setPosition(width/2f - game_id_txt.getWidth()/2f,
                    height/2f - game_id_txt.getHeight()/2f + 40);
        stage.addActor(game_id_txt);

        TextButton btn = new TextButton("Join Game", skin);
        btn.setPosition(width/2f-btn.getWidth()/2f, height/2f - btn.getHeight()/2f - 40);
        btn.addListener(new ClickListener(){
            @Override
            public void clicked(InputEvent event, float x, float y) {
                int player_id = controller.joinGame();
                int game_id  = Integer.parseInt(game_id_txt.getText());
                sm.Push(new Lobby(player_id, game_id));
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
