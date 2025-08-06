#include <DxLib.h>
//#include "ship.h"
#include "types.h"
#include <assert.h>
#include "config.h"
#include "UI.h"
//#include "struct.h"
#include "player.h"
#include <vector>
#include <unordered_map>
#include "planet.h"
#include "globalGameData.h"


namespace
{
    // „C„|„€„q„p„|„„~„„u „„u„‚„u„}„u„~„~„„u
    static const float PLANET_CENTER = 48.0;
    //VectorI2 line[] = { {689,128},{848, 96},{1008, 128},
    //                {1136, 224},{1192, 368},{1096, 509},
    //                {1456, 428},{1408, 592},{1280, 720},
    //                {1104, 768},{944, 704},{848, 560},
    //                {848.5, 911},{704, 800},{624, 640},
    //                {655, 464},{785, 352},{960, 336},{960,476} };
    //const int line_size = sizeof(line) / sizeof(line[0]);

    //std::vector<Planet> planets;
    const int MAX_SHIPS = 50;
    const int SPAWN_INTERVAL = 1000; // 1 „ƒ„u„{„…„~„t„p „r „}„y„|„|„y„ƒ„u„{„…„~„t„p„‡

}

void PlanetInit()
{
    planets.clear();

    // „I„~„y„ˆ„y„p„|„y„x„p„ˆ„y„‘ „„|„p„~„u„„ („„‚„y„}„u„‚)
    planets.push_back({ 0, PLAYER, 10 });   // „R„„„p„‚„„„€„r„p„‘ „„|„p„~„u„„„p „y„s„‚„€„{„p
    planets.push_back({ 6, ENEMY1, 10 });   // „P„|„p„~„u„„„p „„‚„€„„„y„r„~„y„{„p 1
    planets.push_back({ 12, ENEMY2, 10});   // „P„|„p„~„u„„„p „„‚„€„„„y„r„~„y„{„p 2
    // „O„ƒ„„„p„|„„~„„u „„|„p„~„u„„„ NEUTRAL
    for (int i = 0; i < 19; i++) 
    {
        if (i != 0 && i != 6 && i != 12) 
        {
            planets.push_back({ i, NEUTRAL, 10,10 });
        }
    }
}
void PlanetUpdate()
{
    int currentTime = GetNowCount();

    for (auto& planet : planets) 
    {
        // „C„u„~„u„‚„p„ˆ„y„‘ „{„€„‚„p„q„|„u„z „t„|„‘ „~„u-NEUTRAL „„|„p„~„u„„
        if (planet.type != NEUTRAL && planet.shipsCount < MAX_SHIPS) 
        {
            if (currentTime - planet.lastSpawnTime > SPAWN_INTERVAL) 
            {
                planet.shipsCount++;
                OnShipCreated(planet.type, 1);
                planet.lastSpawnTime = currentTime;
            }
        }

        // „K„€„‚„‚„u„{„„„y„‚„€„r„{„p „{„€„|„y„‰„u„ƒ„„„r„p „{„€„‚„p„q„|„u„z („~„u „q„€„|„u„u MAX_SHIPS)
        if (planet.shipsCount > MAX_SHIPS) 
        {
            if (currentTime % 1000 == 0) 
            { // „K„p„w„t„…„ „ƒ„u„{„…„~„t„…
                planet.shipsCount--;
            }
        }
    }
}
void PlanetDraw()
{
    for (const auto& planet : planets) {
        VectorI2 pos = line[planet.positionIndex];

        // „W„r„u„„ „r „x„p„r„y„ƒ„y„}„€„ƒ„„„y „€„„ „„„y„„p
        int color;
        switch (planet.type) {
        case PLAYER: color = GetColor(0, 255, 0); break;   // „H„u„|„u„~„„z
        case ENEMY1: color = GetColor(255, 0, 0); break;   // „K„‚„p„ƒ„~„„z
        case ENEMY2: color = GetColor(255, 165, 0); break; // „O„‚„p„~„w„u„r„„z
        default: color = GetColor(200, 200, 200);         // „R„u„‚„„z
        }

        // „Q„y„ƒ„…„u„} „{„‚„…„s „„|„p„~„u„„„
        DrawCircle(pos.x+ PLANET_CENTER, pos.y + PLANET_CENTER, 35, color, false,5.0f);

        // „B„„r„€„t„y„} „{„€„|„y„‰„u„ƒ„„„r„€ „{„€„‚„p„q„|„u„z
        char shipsText[10];
        sprintf_s(shipsText, "%d", planet.shipsCount);
        DrawString((pos.x + PLANET_CENTER)-5, (pos.y) - 15, shipsText, GetColor(255, 255, 255));
    }
}
void PlanetRelease()
{// „O„ƒ„r„€„q„€„w„t„u„~„y„u „‚„u„ƒ„…„‚„ƒ„€„r „„|„p„~„u„„
	planets.clear();
}

void PlanetReset()
{
    PlayerRelease();
    planets.clear();
    PlanetInit();
    // „R„q„‚„€„ƒ „ƒ„„„p„„„y„ƒ„„„y„{„y „†„‚„p„{„ˆ„y„z

}



void UpdatePlanetControl() {
    UpdateFactionStats(PLAYER);
    UpdateFactionStats(ENEMY1);
    UpdateFactionStats(ENEMY2);
}