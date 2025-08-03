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

void UpdateEnemyLogic(int faction, std::vector<Planet>& planets, std::vector<Ship>& ships) {
    for (auto& planet : planets) {
        if (planet.faction == faction) {
            // ÑRÑÄÑqÑyÑÇÑpÑuÑ} ÑyÑ~ÑtÑuÑ{ÑÉÑç Ñ{ÑÄÑÇÑpÑqÑ|ÑuÑz Ñ~Ñp ÑèÑÑÑÄÑz ÑÅÑ|ÑpÑ~ÑuÑÑÑu
            std::vector<size_t> planetShipIndices;
            for (size_t i = 0; i < ships.size(); ++i) {
                if (ships[i].faction == faction && ships[i].currentPlanet == &planet) {
                    planetShipIndices.push_back(i);
                }
            }

            // ÑEÑÉÑ|Ñy ÑqÑÄÑ|ÑéÑäÑu 10 Ñ{ÑÄÑÇÑpÑqÑ|ÑuÑz - ÑÄÑÑÑÅÑÇÑpÑrÑ|ÑëÑuÑ} ÑBÑRÑE
            if (planetShipIndices.size() > 10) {
                Planet* targetPlanet = FindNearestEnemyPlanet(&planet, faction, planets);
                if (targetPlanet) {
                    for (auto shipIndex : planetShipIndices) {
                        ships[shipIndex].targetPlanet = targetPlanet;
                        ships[shipIndex].currentPlanet = nullptr;
                    }
                }
            }
        }
    }
}