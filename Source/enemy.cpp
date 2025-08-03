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


void UpdateEnemyAI(std::vector<Planet>& planets, std::vector<Ship>& ships) {
    // „R„~„p„‰„p„|„p „€„q„~„€„r„|„‘„u„} „{„€„|„y„‰„u„ƒ„„„r„€ „{„€„‚„p„q„|„u„z „~„p „„|„p„~„u„„„p„‡
    //for (auto& planet : planets) {
    //    planet.shipsCount = 0;
    //}
    for (const auto& ship : ships) {
        if (ship.currentPlanet) {
            ship.currentPlanet->shipsCount++;
        }
    }

    for (size_t fromIdx = 0; fromIdx < planets.size(); fromIdx++) {
        auto& fromPlanet = planets[fromIdx];

        // „P„‚„€„r„u„‚„‘„u„} „„„€„|„Ž„{„€ „r„‚„p„w„u„ƒ„{„y„u „„|„p„~„u„„„ (2 - ENEMY1, 3 - ENEMY2)
        if (fromPlanet.type != 2 && fromPlanet.type != 3) continue;

        // „E„ƒ„|„y „{„€„‚„p„q„|„u„z „~„u„t„€„ƒ„„„p„„„€„‰„~„€ - „„‚„€„„…„ƒ„{„p„u„}
        if (fromPlanet.shipsCount <= 10) continue;

        std::cout << "Enemy planet " << fromPlanet.id
            << " has " << fromPlanet.shipsCount << " ships\n";

        // „I„‹„u„} „r„ƒ„u „t„€„ƒ„„„…„„~„„u „ˆ„u„|„y
        for (size_t toIdx = 0; toIdx < planets.size(); toIdx++) {
            if (fromIdx == toIdx) continue;

            auto& toPlanet = planets[toIdx];
            // „P„‚„€„r„u„‚„‘„u„}, „‰„„„€ „ˆ„u„|„Ž „t„‚„…„s„€„z „†„‚„p„{„ˆ„y„y
            if (toPlanet.type == fromPlanet.type) continue;

            // „P„‚„€„r„u„‚„‘„u„} „ƒ„…„‹„u„ƒ„„„r„€„r„p„~„y„u „„u„‚„u„‡„€„t„p
            bool validPath = false;
            auto transitions = transitionMap.find(fromPlanet.positionIndex);
            if (transitions != transitionMap.end()) {
                for (const auto& trans : transitions->second) {
                    if (trans.second == toPlanet.positionIndex) {
                        validPath = true;
                        break;
                    }
                }
            }

            if (validPath) {
                std::cout << "Valid path found: " << fromPlanet.id
                    << " -> " << toPlanet.id << "\n";

                // „O„„„„‚„p„r„|„‘„u„} „B„R„E „{„€„‚„p„q„|„y („}„€„w„~„€ „y„x„}„u„~„y„„„Ž „~„p fromPlanet.shipsCount - 10)
                SendShips(fromIdx, toIdx);

                // „B„„‡„€„t„y„} „„€„ƒ„|„u „„u„‚„r„€„z „~„p„z„t„u„~„~„€„z „ˆ„u„|„y
                break;
            }
        }
    }
}