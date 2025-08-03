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


// „I„ƒ„„‚„p„r„|„u„~„y„u: „…„q„y„‚„p„u„} const „… „„p„‚„p„}„u„„„‚„p planets, „‰„„„€„q„ „}„€„w„~„€ „q„„|„€ „q„‚„p„„„ „p„t„‚„u„ƒ„p „„|„u„}„u„~„„„€„r
Planet* FindNearestTargetPlanet(Planet* source, std::vector<Planet>& planets) {
    Planet* nearest = nullptr;
    float minDist = std::numeric_limits<float>::max();

    for (auto& planet : planets) {
        // „P„‚„€„„…„ƒ„{„p„u„} „y„ƒ„‡„€„t„~„…„ „„|„p„~„u„„„… „y „„|„p„~„u„„„ „„„€„z „w„u „†„‚„p„{„ˆ„y„y
        if (&planet == source || planet.type == source->type)
            continue;

        float dx = planet.position.x - source->position.x;
        float dy = planet.position.y - source->position.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist < minDist) {
            minDist = dist;
            nearest = &planet;
        }
    }
    return nearest;
}

void UpdateEnemyShips(std::vector<Planet>& planets, std::vector<Ship>& ships) {
    for (auto& planet : planets) {
        // „Q„p„q„€„„„p„u„} „„„€„|„„{„€ „ƒ „r„‚„p„w„u„ƒ„{„y„}„y „„|„p„~„u„„„p„}„y
        if (planet.type != ENEMY1 && planet.type != ENEMY2)
            continue;

        // „R„‰„y„„„p„u„} „{„€„‚„p„q„|„y „~„p „„|„p„~„u„„„u
        int shipCount = 0;
        for (auto& ship : ships) {
            if (ship.currentPlanet == &planet) {
                shipCount++;
            }
        }

        // „E„ƒ„|„y „q„€„|„„Š„u 10 - „€„„„„‚„p„r„|„‘„u„} „r„ƒ„u
        if (shipCount > 10) {
            Planet* target = FindNearestTargetPlanet(&planet, planets);
            if (target) {
                for (auto& ship : ships) {
                    if (ship.currentPlanet == &planet) {
                        ship.targetPlanet = target;
                        ship.currentPlanet = nullptr;
                    }
                }
            }
        }
    }
}