package com.enkle.game.view.util;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;

public class MyToast extends Label {

    private static final Skin skin = new Skin(Gdx.files.internal("ui/uiskin.json"));
    private static final float scale = 1.5f;
    private static final float bottom_padding = 15f;

    private final float duration;
    private Long start;

    public MyToast(float duration, String text){
        super(text, skin);
        skin.getFont("default-font").getData().setScale(scale);
        this.duration = duration;
        this.start = System.currentTimeMillis();
        System.out.println("Start " + start);
        setPosition(Gdx.graphics.getWidth()/2f - getWidth()/2f, bottom_padding);
    }

    @Override
    public void draw(Batch batch, float parentAlpha) {
        if(isAlive()){
            super.draw(batch, parentAlpha);
        } else {
            remove();
        }
    }

    public boolean isAlive(){
        return (System.currentTimeMillis() - start) < duration;
    }

    public static MyToast makeToast(String text, float duration, Stage stage){
        MyToast toast = new MyToast(duration, text);
        stage.addActor(toast);
        return toast;
    }

}
