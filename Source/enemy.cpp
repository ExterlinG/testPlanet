#define NOMINMAX
#include <limits>
#include "DxLib.h"
#include "ship.h"
#include "types.h"
#include "globalGameData.h"
#include "enemy.h"
#include <algorithm>
#include <cmath>
#include "planet.h"
#include <memory>
#include "math.h"


Planet* FindNearestEnemyPlanet(Planet* fromPlanet, int faction, std::vector<Planet>& planets) {
    Planet* nearestPlanet = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (auto& planet : planets) {
        // „P„‚„€„„…„ƒ„{„p„u„} „„„u„{„…„‹„…„ „„|„p„~„u„„„… „y „„|„p„~„u„„„ „„„€„z „w„u „†„‚„p„{„ˆ„y„y
        if (&planet == fromPlanet || planet.faction == faction) continue;

        float dx = planet.position.x - fromPlanet->position.x;
        float dy = planet.position.y - fromPlanet->position.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < minDistance) {
            minDistance = distance;
            nearestPlanet = &planet;
        }
    }

    return nearestPlanet;
}

void UpdateEnemyLogic(int faction, std::vector<Planet>& planets, std::vector<std::shared_ptr<Ship>>& ships) {
    for (auto& planet : planets) {
        if (planet.faction == faction) {
            // „R„€„q„y„‚„p„u„} „r„ƒ„u „{„€„‚„p„q„|„y „„„„€„z „†„‚„p„{„ˆ„y„y „~„p „„|„p„~„u„„„u
            std::vector<std::shared_ptr<Ship>> planetShips;
            for (auto& ship : ships) {
                if (ship->faction == faction && ship->currentPlanet.get() == &planet) {
                    planetShips.push_back(ship);
                }
            }

            // „E„ƒ„|„y „q„€„|„„Š„u 10 „{„€„‚„p„q„|„u„z - „€„„„„‚„p„r„|„‘„u„} „B„R„E
            if (planetShips.size() > 10) {
                Planet* targetPlanet = FindNearestEnemyPlanet(&planet, faction, planets);
                if (targetPlanet) {
                    for (auto& ship : planetShips) {
                        ship->targetPlanet = targetPlanet;
                        ship->currentPlanet = nullptr;
                    }
                }
            }
        }
    }
}