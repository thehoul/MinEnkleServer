package com.enkle.game.view.scene;

import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.scenes.scene2d.Stage;

public abstract class Scene extends ApplicationAdapter {
    protected SceneManager sm;
    private Stage stage;

    protected Scene(){this.sm = SceneManager.getInstance();}

    public void render(SpriteBatch batch) {
        batch.begin();
        onRender(batch);
        batch.end();
    }

    protected void onRender(SpriteBatch batch){

    }

    public void dispose(SpriteBatch batch){
        batch.dispose();
    }

    public Stage getStage() {
        return stage;
    }

    public void prepareScene(){
        this.stage = new Stage();
    }

    public void disposeEarly() { }
}

