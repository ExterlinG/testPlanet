#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "planet.h"
#include "ship.h"
#include <vector>
#include <memory>
#include <limits>
void UpdateEnemyLogic(int faction, std::vector<std::shared_ptr<Planet>>& planets, std::vector<std::shared_ptr<Ship>>& ships);
std::shared_ptr<Planet> FindNearestEnemyPlanet(std::shared_ptr<Planet> fromPlanet, int faction, const std::vector<std::shared_ptr<Planet>>& planets);

#endif // ENEMY_H