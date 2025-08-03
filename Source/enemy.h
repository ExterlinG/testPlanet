#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "planet.h"
#include "ship.h"
#include <vector>

void UpdateEnemyLogic(int faction, std::vector<Planet>& planets, std::vector<Ship>& ships);
Planet* FindNearestEnemyPlanet(Planet* fromPlanet, int faction, std::vector<Planet>& planets);

#endif // ENEMY_H