#include "gameOverScene.h"
#include <DxLib.h>
#include "app.h"
#include "playScene.h"
#include <assert.h>
#include "UI.h"
#include "globalGameData.h"
namespace {
    int winImage = -1;
    int loseImage = -1;
    int timeOverImage = -1;
    int endImage = -1;
    bool pushed; // ƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚½
    int pushedCounter; // ƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚½Œã‚ÌŠÔ‚ğ”‚¦‚é
    
};
void GameOverSceneInit()
{
    if (endImage < 0) {
        endImage = LoadGraph("data\\texture\\ui\\BG.png");
        assert(endImage >= 0);
    }
    if (winImage < 0) {
        winImage = LoadGraph("data\\texture\\ui\\win.png");
        assert(winImage >= 0);
    }
    if (loseImage < 0) {
        loseImage = LoadGraph("data\\texture\\ui\\lose.png");
        assert(loseImage >= 0);
    }
    if (timeOverImage < 0) {
        timeOverImage = LoadGraph("data\\texture\\ui\\score.png");
        assert(timeOverImage >= 0);
    }
}
void GameOverSceneUpdate()
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
            ChangeScene(Scene::TITLE);
    }
}
void GameOverSceneDraw()
{
    DrawGraph(0, 0, endImage, true);
    int x = (1920 - 600) / 2;
    int y = (1080 - 120) / 2;
    DrawGameOverStats();


    if (GameResult.isVictory) {
        if (winImage != -1) {
            DrawRectGraph(x, y, 0, 0, 600, 120, winImage, TRUE, FALSE);
            printf("Drawing victory image\n");
        }
        else {
            DrawString(x, y, "VICTORY", GetColor(255, 255, 255));
        }
    }
    else if (GameResult.isLose) {
        if (loseImage != -1) {
            DrawRectGraph(x, y, 0, 0, 600, 120, loseImage, TRUE, FALSE);
            printf("Drawing lose image\n");
        }
        else {
            DrawString(x, y, "DEFEAT", GetColor(255, 255, 255));
        }
    }
    else if (GameResult.isTimeOver) {
        if (timeOverImage != -1) {
            DrawRectGraph(x, y, 0, 0, 600, 120, timeOverImage, TRUE, FALSE);
            printf("Drawing time over image\n");
        }
        else {
            DrawString(x, y, "TIME OVER", GetColor(255, 255, 255));
        }
    }
}
void GameOverSceneRelease()
{
    if (endImage > 0) {
        DeleteGraph(endImage);
        endImage = -1;
    }
    if (winImage > 0) {
        DeleteGraph(winImage);
        winImage = -1;
    }
    if (loseImage > 0) {
        DeleteGraph(loseImage);
        loseImage = -1;
	}
    if (timeOverImage > 0) {
        DeleteGraph(timeOverImage);
        timeOverImage = -1;
    }
    GameOverSceneReset();
	printf("Game Over Scene Released\n");

}

void GameOverSceneReset()
{
    pushed = false;
    pushedCounter = 0;
}
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