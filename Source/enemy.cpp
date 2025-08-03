#include <iostream>
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
        // „P„‚„€„„…„ƒ„{„p„u„}: „„„u„{„…„‹„…„ „„|„p„~„u„„„…, „ƒ„r„€„y „„|„p„~„u„„„ „y „~„u„z„„„‚„p„|„„~„„u („u„ƒ„|„y „~„…„w„~„€)
        if (&planet == fromPlanet ||
            static_cast<int>(planet.faction) == faction ||
            planet.faction == NEUTRAL) continue;

        float dx = planet.position.x - fromPlanet->position.x;
        float dy = planet.position.y - fromPlanet->position.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < minDistance) {
            minDistance = distance;
            nearestPlanet = &planet;
        }
    }

    // „D„€„q„p„r„y„} „€„„„|„p„t„€„‰„~„„z „r„„r„€„t
    if (!nearestPlanet) {
        std::cout << "No target found for faction " << faction << std::endl;
    }

    return nearestPlanet;
}

void UpdateEnemyLogic(int faction, std::vector<Planet>& planets, std::vector<Ship>& ships) {
    for (auto& planet : planets) {
        if (static_cast<int>(planet.faction) == faction) {
            int shipCount = 0;
            std::vector<size_t> shipsOnPlanet;

            // „R„‰„y„„„p„u„} „{„€„‚„p„q„|„y
            for (size_t i = 0; i < ships.size(); ++i) {
                if (ships[i].faction == faction &&
                    ships[i].currentPlanet == &planet) {
                    shipCount++;
                    shipsOnPlanet.push_back(i);
                }
            }

            // „E„ƒ„|„y >10 - „€„„„„‚„p„r„|„‘„u„} „B„R„E
            if (shipCount > 10) {
                Planet* target = FindNearestEnemyPlanet(&planet, faction, planets);
                if (target) {
                    for (auto shipIndex : shipsOnPlanet) {
                        ships[shipIndex].targetPlanet = target;
                        ships[shipIndex].currentPlanet = nullptr;
                        // „D„€„q„p„r„y„} „„‚„y„x„~„p„{ „t„r„y„w„u„~„y„‘
                        ships[shipIndex].isMoving = true;
                    }
                    std::cout << "Sent " << shipsOnPlanet.size()
                        << " ships from planet " << planet.id
                        << " to planet " << target->id << std::endl;
                }
            }
        }
    }
}