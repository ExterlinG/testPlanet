#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "planet.h"
#include "ship.h"
#include <vector>
#include <memory>

// „O„q„~„€„r„|„v„~„~„„u „†„…„~„{„ˆ„y„y, „‚„p„q„€„„„p„„‹„y„u „ƒ vector<Planet> „r„}„u„ƒ„„„€ shared_ptr
void UpdateEnemyLogic(int faction, std::vector<Planet>& planets, std::vector<std::shared_ptr<Ship>>& ships);
Planet* FindNearestEnemyPlanet(Planet* fromPlanet, int faction, std::vector<Planet>& planets);

#endif // ENEMY_H