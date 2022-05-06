package com.enkle.game.view.scene;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.utils.viewport.ScreenViewport;

public class GameView extends Scene {

    private final int player_id;
    private SceneManager sm;
    private Skin skin;
    private Stage stage;


    public GameView(int player_id){
        this.player_id = player_id;
    }

    @Override
    public void prepareScene() {
        prepareVariables();
        prepareUI();
    }

    private void prepareVariables(){
        stage = new Stage(new ScreenViewport());
        skin  = new Skin(Gdx.files.internal("ui/uiskin.json"));
        skin.getFont("default-font").getData().setScale(3f);
    }

    private void prepareUI(){
        float width = Gdx.graphics.getWidth();
        float height = Gdx.graphics.getHeight();
        Label text = new Label("Player ID : " + player_id, skin);
        text.setPosition(10, height - text.getHeight() - 10);

        stage.addActor(text);
    }

    @Override
    public void render(SpriteBatch batch) {
        batch.begin();
        stage.draw();
        batch.end();
    }
}
