#include "gameOverScene.h"
<<<<<<< HEAD
#include "globalGameData.h"
#include "types.h"
#include <DxLib.h>
#include "app.h"
#include "playScene.h"
#include <assert.h>
#include "UI.h"


namespace {
	//extern GameResultStruct GameResult;
	int gameoverImage = -1;	//ƒ^ƒCƒgƒ‹ƒ{ƒ^ƒ“‚Ì‰æ‘œƒnƒ“ƒhƒ‹
	int winImage = -1;	//ƒ^ƒCƒgƒ‹ƒ{ƒ^ƒ“‚Ì‰æ‘œƒnƒ“ƒhƒ‹
	int loseImage = -1;	//ƒ^ƒCƒgƒ‹ƒ{ƒ^ƒ“‚Ì‰æ‘œƒnƒ“ƒhƒ‹
	int timeOverImage = -1;	//ƒ^ƒCƒgƒ‹ƒ{ƒ^ƒ“‚Ì‰æ‘œƒnƒ“ƒhƒ‹

	bool pushed; // ƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚½
	int pushedCounter; // ƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚½Œã‚ÌŽžŠÔ‚ð”‚¦‚é
	//GameResultStruct GameResult = {};
};
void DrawGameOverStats() {
	int y = 200;
	DrawFormatStringToHandle(100, y, GetColor(255, 255, 255), g_uiFont,
		"„I„s„‚„€„{: „T„~„y„‰„„„€„w„y„| %d „{„€„‚„p„q„|„u„z", g_playerStats.shipsDestroyed);
	y += 30;
	DrawFormatStringToHandle(100, y, GetColor(255, 100, 100), g_uiFont,
		"„B„‚„p„s 1: „T„~„y„‰„„„€„w„y„| %d „{„€„‚„p„q„|„u„z", g_enemy1Stats.shipsDestroyed);
	y += 30;
	DrawFormatStringToHandle(100, y, GetColor(255, 200, 100), g_uiFont,
		"„B„‚„p„s 2: „T„~„y„‰„„„€„w„y„| %d „{„€„‚„p„q„|„u„z", g_enemy2Stats.shipsDestroyed);
}
=======

>>>>>>> parent of 1fdb669 (debug key included)
void GameOverSceneInit()
{

}
void GameOverSceneUpdate()
{

}
void GameOverSceneDraw()
{

<<<<<<< HEAD
	int patternX = pushedCounter / 7 % 2;
	int patternY = pushedCounter / 15 % 2;
	// „B „†„…„~„{„ˆ„y„y „€„„„‚„y„ƒ„€„r„{„y:
	int x = (1920 - 600) / 2;  // „W„u„~„„„‚„y„‚„€„r„p„~„y„u „„€ „Š„y„‚„y„~„u
	int y = (1080 - 120) / 2; // „W„u„~„„„‚„y„‚„€„r„p„~„y„u „„€ „r„„ƒ„€„„„u

	printf("Debug: Victory=%d, Lose=%d, TimeOver=%d\n",
		GameResult.isVictory, GameResult.isLose, GameResult.isTimeOver);

	if (GameResult.isVictory) {
		if (winImage != -1) {
			DrawRectGraph(x, y, 0, 0, 600, 120, winImage, TRUE, FALSE);
			printf("Drawing victory image\n");
			DrawString(0, 0, "VICTORY", GetColor(255, 255, 255));
		}
		else {
			DrawString(0, 0, "VICTORY", GetColor(255, 255, 255));
		}
	}
	else if (GameResult.isLose) {
		if (loseImage != -1) {
			DrawRectGraph(x, y, 0, 0, 600, 120, loseImage, TRUE, FALSE);
			printf("Drawing lose image\n");
			DrawString(0, 0, "DEFEAT", GetColor(255, 255, 255));
		}
		else {
			DrawString(0, 0, "DEFEAT", GetColor(255, 255, 255));
		}
	}
	else if (GameResult.isTimeOver) {
		if (timeOverImage != -1) {
			DrawRectGraph(x, y, 0, 0, 600, 120, timeOverImage, TRUE, FALSE);
			printf("Drawing time over image\n");
			DrawString(0, 0, "TIME OVER", GetColor(255, 255, 255));
		}
		else {
			DrawString(0, 0, "TIME OVER", GetColor(255, 255, 255));
		}
	}
	DrawGameOverStats();
	
=======
>>>>>>> parent of 1fdb669 (debug key included)
}
void GameOverSceneRelease()
{

}

void GameOverSceneReset()
{
<<<<<<< HEAD
	pushed = false;
	pushedCounter = 0;
}

=======

}
>>>>>>> parent of 1fdb669 (debug key included)
