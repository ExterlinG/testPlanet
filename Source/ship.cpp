#include "ship.h"
#include "planet.h" // „D„|„‘ „t„€„ƒ„„„…„„p „{ planets
#include <algorithm>
#include "struct.h"
#include "player.h"
#include "math.h"

// „C„|„€„q„p„|„„~„„u „„u„‚„u„}„u„~„~„„u „t„|„‘ „{„€„‚„p„q„|„u„z
std::vector<Ship> activeShips;
const float SHIP_SPEED = 5.0f;
int shipGraphic = -1;

void ShipInit() 
{
    shipGraphic = LoadGraph("Assets/ship.png");
    activeShips.clear();
}
void ShipUpdate() {
    int currentTime = GetNowCount();

    for (auto it = activeShips.begin(); it != activeShips.end(); ) {
        it->progress = (currentTime - it->startTime) / (SHIP_SPEED * 1000.0f);

        if (it->progress >= 1.0f) {
            // „O„q„‚„p„q„€„„„{„p „„‚„y„q„„„„y„‘ „{„€„‚„p„q„|„u„z
            Planet& fromPlanet = planets[it->fromPlanetIndex];
            Planet& toPlanet = planets[it->toPlanetIndex];

            if (it->count > toPlanet.shipsCount) {
                toPlanet.type = fromPlanet.type;
                toPlanet.shipsCount = it->count - toPlanet.shipsCount;
            }
            else {
                toPlanet.shipsCount -= it->count;
            }

            it = activeShips.erase(it);
        }
        else {
            ++it;
        }
    }
}

void SendShips(int fromPlanet, int toPlanet, int count) {
    if (fromPlanet < 0 || fromPlanet >= planets.size() ||
        toPlanet < 0 || toPlanet >= planets.size() ||
        count <= 0) return;

    Ship newShip;
    newShip.fromPlanetIndex = fromPlanet;
    newShip.toPlanetIndex = toPlanet;
    newShip.count = std::min(count, planets[fromPlanet].shipsCount);
    newShip.progress = 0.0f;
    newShip.startTime = GetNowCount();
    newShip.graphicHandle = shipGraphic;

    activeShips.push_back(newShip);
    planets[fromPlanet].shipsCount -= newShip.count;
}

void ShipDraw() {
    for (const auto& ship : activeShips) {
        const VectorI2& fromPos = line[planets[ship.fromPlanetIndex].positionIndex];
        const VectorI2& toPos = line[planets[ship.toPlanetIndex].positionIndex];

        float x = fromPos.x + (toPos.x - fromPos.x) * ship.progress;
        float y = fromPos.y + (toPos.y - fromPos.y) * ship.progress;
        float angle = atan2(toPos.y - fromPos.y, toPos.x - fromPos.x);

        DrawRotaGraphF(x, y, 1.0f, angle, ship.graphicHandle, TRUE);
        DrawFormatStringF(x + 15, y - 10, GetColor(255, 255, 255), "%d", ship.count);
    }
}