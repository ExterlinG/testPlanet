#include "ship.h"
#include "planet.h" // �D�|�� �t�����������p �{ planets
#include "globalGameData.h"
#include "struct.h"
#include "player.h"
#include "math.h"
#include "playScene.h"
#include <algorithm>
// �C�|���q�p�|���~���u ���u���u�}�u�~�~���u �t�|�� �{�����p�q�|�u�z
//std::vector<Ship> activeShips;
//const float SHIP_SPEED = 5.0f;
//int shipGraphic = -1;
//VectorI2 line[] = { {689,128},{848, 96},{1008, 128},
//                    {1136, 224},{1192, 368},{1096, 509},
//                    {1456, 428},{1408, 592},{1280, 720},
//                    {1104, 768},{944, 704},{848, 560},
//                    {848.5, 911},{704, 800},{624, 640},
//                    {655, 464},{785, 352},{960, 336},{960,476} };
//const int line_size = sizeof(line) / sizeof(line[0]);
//std::vector<Planet> planets;
void ShipInit() 
{
    shipGraphic = LoadGraph("data\\texture\\humanShip\\battlecruiser.png");
    activeShips.clear();
}
void ShipUpdate() {
    int currentTime = GetNowCount();

    for (auto it = activeShips.begin(); it != activeShips.end(); ) {
        it->progress = (currentTime - it->startTime) / (SHIP_SPEED * 1000.0f);

        if (it->progress >= 1.0f) {
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
    newShip.count = min(count, planets[fromPlanet].shipsCount);
    newShip.progress = 0.0f;
    newShip.startTime = GetNowCount();

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

        DrawRotaGraphF(x, y, 1.0f, angle, shipGraphic, TRUE);
        DrawFormatStringF(x + 15, y - 10, GetColor(255, 255, 255), "%d", ship.count);
    }
}