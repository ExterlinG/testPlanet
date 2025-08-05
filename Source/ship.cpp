#include "types.h"
#include "ship.h"
#include "planet.h" // „D„|„‘ „t„€„ƒ„„„…„„p „{ planets
#include "globalGameData.h"
#include <vector>
//#include "struct.h"
#include "player.h"
#include "math.h"
#include "playScene.h"
#include <algorithm>
#include <unordered_map>


// „C„|„€„q„p„|„„~„„u „„u„‚„u„}„u„~„~„„u („€„„‚„u„t„u„|„u„~„ „r globalData.cpp)
static const float PLANET_CENTER = 48.0;
extern std::vector<Planet> planets;
extern std::vector<Ship> activeShips;
extern VectorI2 line[];  // „M„p„ƒ„ƒ„y„r „{„€„€„‚„t„y„~„p„„ „„„€„‰„u„{
extern int shipGraphic;        // „C„‚„p„†„y„{„p „{„€„‚„p„q„|„‘
extern int shipGraphicEngine;        // „C„‚„p„†„y„{„p „{„€„‚„p„q„|„‘
//int shipGraphic = -1;
//extern VectorI2 line[] = { {689,128},{848, 96},{1008, 128},
//                    {1136, 224},{1192, 368},{1096, 509},
//                    {1456, 428},{1408, 592},{1280, 720},
//                    {1104, 768},{944, 704},{848, 560},
//                    {848.5, 911},{704, 800},{624, 640},
//                    {655, 464},{785, 352},{960, 336},{960,476} };
//const int line_size = sizeof(line) / sizeof(line[0]);
//std::vector<Planet> planets;
int patternShip;
int walkCounter; // „R„‰„u„„„‰„y„{ „t„|„‘ „p„~„y„}„p„ˆ„y„y „{„€„‚„p„q„|„u„z
void ShipInit() 
{
    //shipGraphicEngine = LoadGraph("data\\texture\\humanShip\\engine.png");
    shipGraphic = LoadGraph("data\\texture\\humanShip\\engine2.png");
    activeShips.clear(); // „O„‰„y„‹„p„u„} „}„p„ƒ„ƒ„y„r „{„€„‚„p„q„|„u„z
    walkCounter = 0;
}
void ShipUpdate() {
    patternShip = (walkCounter / 6) % 12;

    walkCounter++;
    for (size_t i = 0; i < activeShips.size(); ) {
        // „T„r„u„|„y„‰„y„r„p„u„} „„‚„€„s„‚„u„ƒ„ƒ „t„r„y„w„u„~„y„‘ (5 „ƒ„u„{„…„~„t „~„p „r„u„ƒ„ „„…„„„)
        activeShips[i].progress += 1.0f / (5.0f * 60.0f); // 60 FPS

        // „E„ƒ„|„y „{„€„‚„p„q„|„y „t„€„|„u„„„u„|„y
        if (activeShips[i].progress >= 1.0f) {
            Planet& fromPlanet = planets[activeShips[i].fromPlanetIdx];
            Planet& toPlanet = planets[activeShips[i].toPlanetIdx];

            // „L„€„s„y„{„p „q„€„‘:
            if (fromPlanet.type == PLAYER && toPlanet.type == PLAYER) 
            {
                toPlanet.shipsCount = min(toPlanet.shipsCount + activeShips[i].count, 100);
			}
            else if (activeShips[i].count > toPlanet.shipsCount) {
                // „H„p„‡„r„p„„ „„|„p„~„u„„„
                toPlanet.type = fromPlanet.type; // „M„u„~„‘„u„} „r„|„p„t„u„|„„ˆ„p
                toPlanet.shipsCount = activeShips[i].count - toPlanet.shipsCount;
            }
            else {
                // „O„q„€„‚„€„~„p „…„ƒ„„u„Š„~„p
                toPlanet.shipsCount -= activeShips[i].count;
            }

            activeShips.erase(activeShips.begin() + i); // „T„t„p„|„‘„u„} „„‚„y„q„„r„Š„y„u „{„€„‚„p„q„|„y
        }
        else {
            i++;
        }
    }
}

void SendShips(int fromPlanetIdx, int toPlanetIdx) {
    if (fromPlanetIdx == toPlanetIdx) return;

    Planet& fromPlanet = planets[fromPlanetIdx];
    int availableShips = fromPlanet.shipsCount;
    if (availableShips <= 0) return;

    // „R„€„x„t„p„u„} „s„‚„…„„„… „{„€„‚„p„q„|„u„z
    Ship newShip;
    newShip.fromPlanetIdx = fromPlanetIdx;
    newShip.toPlanetIdx = toPlanetIdx;
    newShip.count = availableShips; // „O„„„„‚„p„r„|„‘„u„} „r„ƒ„u „{„€„‚„p„q„|„y
    newShip.progress = 0.0f;

    activeShips.push_back(newShip);
    fromPlanet.shipsCount = 0; // „B„ƒ„u „{„€„‚„p„q„|„y „…„|„u„„„u„|„y
}

void ShipDraw() {
    for (const auto& ship : activeShips) {
        const VectorI2& fromPos = line[planets[ship.fromPlanetIdx].positionIndex];
        const VectorI2& toPos = line[planets[ship.toPlanetIdx].positionIndex];

        // „P„€„x„y„ˆ„y„‘ „ƒ „y„~„„„u„‚„„€„|„‘„ˆ„y„u„z
        float x = fromPos.x + (toPos.x  - fromPos.x )  * ship.progress;
        float y = fromPos.y+ (toPos.y  - fromPos.y)  * ship.progress;

        // „P„‚„p„r„y„|„„~„„z „‚„p„ƒ„‰„u„„ „…„s„|„p („~„€„ƒ „{ „ˆ„u„|„y)
        float angle = atan2(toPos.y - y, toPos.x - x) + DX_PI / 2;; // „T„s„€„| „€„„ „„„u„{„…„‹„u„z „„€„x„y„ˆ„y„y „{ „ˆ„u„|„y

        // 1. „Q„y„ƒ„…„u„} „€„ƒ„~„€„r„~„€„u „y„x„€„q„‚„p„w„u„~„y„u „{„€„‚„p„q„|„‘ („„€„r„u„‚„~„…„„„€„u „~„p angle)
        DrawRectRotaGraph2(x+ PLANET_CENTER, y+ PLANET_CENTER, patternShip * 128, 0, 128, 1536, 64, 64, 1.0f, angle, shipGraphic, true, false);

        //// 2. „Q„y„ƒ„…„u„} „t„r„y„s„p„„„u„|„y „ƒ „…„‰„u„„„€„} „„€„r„€„‚„€„„„p
        //float engineOffsetX = -25.0f * cosf(angle); // „R„}„u„‹„u„~„y„u „~„p„x„p„t „„€ „€„ƒ„y „{„€„‚„p„q„|„‘
        //float engineOffsetY = -25.0f * sinf(angle);

        
          

        // 3. „O„„„€„q„‚„p„w„p„u„} „{„€„|„y„‰„u„ƒ„„„r„€ „{„€„‚„p„q„|„u„z
        DrawFormatStringF(x + 25 * cosf(angle),
            y + 25 * sinf(angle),
            GetColor(255, 255, 255), "%d", ship.count);
    }
}