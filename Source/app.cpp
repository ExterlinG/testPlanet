#include "App.h"
#include <DxLib.h>

#include "titleScene.h"
#include "playScene.h"
#include "gameOverScene.h"
#include "config.h"

namespace 
{
	Scene scene;	//óÒãìå^ÉVÅ[ÉìÇÃíËã`
};

void AppInit() {
	TitleSceneInit();
	PlaySceneInit();
	GameOverSceneInit();

	scene = Scene::TITLE;
	TitleSceneReset();
}

void AppUpdate() 
{
	switch (scene) 
	{
	case Scene::TITLE:
		TitleSceneUpdate();
		break;
	case Scene::PLAY:
		PlaySceneUpdate();
		break;
	case Scene::GAMEOVER:
		GameOverSceneUpdate();
		break;
	}
}

void AppDraw() 
{
	switch (scene) 
	{
	case Scene::TITLE:
		TitleSceneDraw();
		break;
	case Scene::PLAY:
		PlaySceneDraw();
		break;
	case Scene::GAMEOVER:
		GameOverSceneDraw();
		break;
	}
}

void AppRelease() 
{
	TitleSceneRelease();
	PlaySceneRelease();
	GameOverSceneRelease();
}

bool IsAllKeyPush() 
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if ((key & PAD_INPUT_DOWN) != 0)
		return true;
	if ((key & PAD_INPUT_LEFT) != 0)
		return true;
	if ((key & PAD_INPUT_RIGHT) != 0)
		return true;
	if ((key & PAD_INPUT_UP) != 0)
		return true;
	if ((key & PAD_INPUT_1) != 0)
		return true;
	if ((key & PAD_INPUT_2) != 0)
		return true;
	if ((key & PAD_INPUT_3) != 0)
		return true;
	if ((key & PAD_INPUT_4) != 0)
		return true;
	if ((key & PAD_INPUT_5) != 0)
		return true;
	if ((key & PAD_INPUT_6) != 0)
		return true;
	if ((key & PAD_INPUT_7) != 0)
		return true;
	if ((key & PAD_INPUT_8) != 0)
		return true;
	if ((key & PAD_INPUT_9) != 0)
		return true;
	if ((key & PAD_INPUT_10) != 0)
		return true;
	return false;
}

void ChangeScene(Scene next) 
{
	if (scene != next) 
	{
		scene = next;
		switch (scene) 
		{
		case Scene::TITLE: TitleSceneReset(); break;
		case Scene::PLAY: PlaySceneReset(); break;
		case Scene::GAMEOVER: GameOverSceneReset(); break;
		}
	}
}
