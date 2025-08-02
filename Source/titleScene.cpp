#include "titleScene.h"
#include <DxLib.h>
#include "app.h"
#include "assert.h"
#include "config.h"

//„t„€„q„p„r„y„„„ 
// 1. „r„„q„€„‚ „ƒ„„„€„‚„€„~„
// 2. „„‚„p„r„y„|„p „y„s„‚„
namespace
{
	int logoImage = -1;	    //ƒ^ƒCƒgƒ‹‚Ì‰æ‘œƒnƒ“ƒhƒ‹
	int buttonImage = -1;	//ƒ^ƒCƒgƒ‹ƒ{ƒ^ƒ“‚Ì‰æ‘œƒnƒ“ƒhƒ‹
	bool pushed; // ƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚½
	int pushedCounter; // ƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚½Œã‚ÌŠÔ‚ğ”‚¦‚é
	int titleSound = -1;
}

void TitleSceneInit()
{
	if (logoImage < 0) {
		logoImage = LoadGraph("data\\texture\\ui\\BG.png");
		assert(logoImage >= 0);
	}
	if (buttonImage < 0) {
		buttonImage = LoadGraph("data\\texture\\ui\\Start_BTN.png");
		assert(buttonImage >= 0);
	}
	if (titleSound < 0) {
		titleSound = LoadSoundMem("data\\sound\\titleSound\\titleSound.wav");
		assert(titleSound >= 0);
	}
	PlaySoundMem(titleSound, DX_PLAYTYPE_BACK);
}

void TitleSceneUpdate()
{
	if (!pushed) {
		if (IsAllKeyPush()) {
			pushed = true;
			pushedCounter = 0;
		}
		
	}
	else {
		++pushedCounter;
		if (pushedCounter >= 30)
			ChangeScene(Scene::PLAY);
		StopSoundMem(titleSound);
	}
}

void TitleSceneDraw()
{
	DrawGraph(0, 0, logoImage, true);

	int patternX = pushedCounter / 7 % 2;
	int patternY = pushedCounter / 15 % 2;
	DrawRectGraph(755, 400, patternX * 410, patternY * 120, 410, 120, buttonImage, true, false);
}

void TitleSceneRelease()
{
	if (titleSound > 0) {
		DeleteSoundMem(titleSound);
		titleSound = -1;
	}
	if (logoImage > 0) {
		DeleteGraph(logoImage);
		logoImage = -1;
	}
	if (buttonImage > 0) {
		DeleteGraph(buttonImage);
		buttonImage = -1;
	}

}

void TitleSceneReset()
{
	pushed = false;
	pushedCounter = 0;
}