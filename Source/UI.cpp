#include "UI.h"
#include "planet.h"
#include "ship.h"
#include "DxLib.h"
#include "types.h" // „D„|„‘ PlanetType
#include "globalGameData.h"
#include "assert.h"
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
    g_enemy2Stats.portraitGraph = LoadGraph("data\\texture\\ui\\robot1.png");
    assert(g_playerStats.portraitGraph >= 0);
    assert(g_enemy1Stats.portraitGraph >= 0);
    assert(g_enemy2Stats.portraitGraph >= 0);
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
		DrawRectGraph(x, y, 0, 0,128,128, stats.portraitGraph, true, false);
        //DrawGraph(x, y, stats.portraitGraph, TRUE);
    }

    DrawFormatStringToHandle(x + 80, y, color, g_uiFont, "Created: %d", stats.shipsProduced);
    DrawFormatStringToHandle(x + 80, y + 25, color, g_uiFont, "Lost: %d", stats.shipsLost);
    DrawFormatStringToHandle(x + 80, y + 50, color, g_uiFont, "Destroed: %d", stats.shipsDestroyed);
    DrawFormatStringToHandle(x + 80, y + 75, color, g_uiFont, "Planet: %d", stats.planetsControlled);
}

void DrawPlayerUI() {
    DrawFactionUI(20, 64, g_playerStats, GetColor(100, 255, 100));
    DrawCircle(50,100, 35, GetColor(0, 255, 0), false, 5.0f);
}

void DrawEnemy1UI() {
    DrawFactionUI(20, 164, g_enemy1Stats, GetColor(255, 100, 100));
    DrawCircle(50, 200, 35, GetColor(255, 0, 0), false, 5.0f);
}

void DrawEnemy2UI() {
    DrawFactionUI(20, 264, g_enemy2Stats, GetColor(255, 200, 100));
    DrawCircle(50, 300, 35, GetColor(255, 165, 0), false, 5.0f);
}
void UIRelease() {
    DeleteGraph(g_playerStats.portraitGraph);
    DeleteGraph(g_enemy1Stats.portraitGraph);
    DeleteGraph(g_enemy2Stats.portraitGraph);
    DeleteFontToHandle(g_uiFont);
}
void UIReset() {
    g_playerStats = { 0 };
    g_enemy1Stats = { 0 };
    g_enemy2Stats = { 0 };
    InitUI();
}