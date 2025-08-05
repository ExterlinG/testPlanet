#include "UI.h"
#include "types.h"
#include "globalGameData.h"
#include "planet.h"
#include "ship.h"
#include <vector>
#include <DxLib.h>

// „C„|„€„q„p„|„Ž„~„„u „„u„‚„u„}„u„~„~„„u
FactionStats g_playerStats = { 0 };
FactionStats g_enemy1Stats = { 0 };
FactionStats g_enemy2Stats = { 0 };
int g_uiFont = -1;

void InitUI() {
    g_uiFont = CreateFontToHandle(NULL, 20, 3, DX_FONTTYPE_ANTIALIASING);

    // „H„p„s„‚„…„x„{„p „„€„‚„„„‚„u„„„€„r
    g_playerStats.portraitGraph = LoadGraph("data\\texture\\ui\\human.png");
    g_enemy1Stats.portraitGraph = LoadGraph("data\\texture\\ui\\orc.png");
    g_enemy2Stats.portraitGraph = LoadGraph("data\\texture\\ui\\robot.png");
}

void UpdateFactionStats(PlanetType faction) {
    FactionStats* stats = nullptr;

    switch (faction) {
    case PLAYER: stats = &g_playerStats; break;
    case ENEMY1: stats = &g_enemy1Stats; break;
    case ENEMY2: stats = &g_enemy2Stats; break;
    default: return;
    }

    // „O„q„~„€„r„|„‘„u„} „{„€„|„y„‰„u„ƒ„„„r„€ „„|„p„~„u„„
    stats->planetsControlled = 0;
    for (const auto& planet : planets) {
        if (planet.type == faction) {
            stats->planetsControlled++;
        }
    }
}

void DrawFactionUI(int x, int y, const FactionStats& stats, int color) {
    if (stats.portraitGraph != -1) {
        DrawRectGraph(x, y, 0, 0,128, 128, stats.portraitGraph, true, false);
        //DrawGraph(x, y, stats.portraitGraph, TRUE);
    }

    DrawFormatStringToHandle(x + 70, y, color, g_uiFont, "„R„€„x„t„p„~„€: %d", stats.shipsProduced);
    DrawFormatStringToHandle(x + 70, y + 25, color, g_uiFont, "„P„€„„„u„‚„‘„~„€: %d", stats.shipsLost);
    DrawFormatStringToHandle(x + 70, y + 50, color, g_uiFont, "„T„~„y„‰„„„€„w„u„~„€: %d", stats.shipsDestroyed);
    DrawFormatStringToHandle(x + 70, y + 75, color, g_uiFont, "„P„|„p„~„u„„: %d", stats.planetsControlled);
}

void DrawPlayerUI() {
    DrawFactionUI(50, 50, g_playerStats, GetColor(100, 255, 100));
}

void DrawEnemy1UI() {
    DrawFactionUI(GetWindowWidth() - 250, 50, g_enemy1Stats, GetColor(255, 100, 100));
}

void DrawEnemy2UI() {
    DrawFactionUI(GetWindowWidth() - 250, 150, g_enemy2Stats, GetColor(255, 200, 100));
}