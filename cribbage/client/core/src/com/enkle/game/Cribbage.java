package com.enkle.game;

import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.utils.ScreenUtils;
import com.enkle.game.view.scene.MainView;
import com.enkle.game.view.scene.SceneManager;

public class Cribbage extends ApplicationAdapter {
	SpriteBatch batch;
	SceneManager sm;
	
	@Override
	public void create () {
		batch = new SpriteBatch();
		sm = SceneManager.getInstance();
		sm.Push(new MainView());
	}

	@Override
	public void render () {
		ScreenUtils.clear(1, 0, 0, 1);
		sm.Peek().render(batch);
	}
	
	@Override
	public void dispose () {
		batch.dispose();
		sm.Peek().dispose(batch);
	}
}
