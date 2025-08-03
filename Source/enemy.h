#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "planet.h"
#include "ship.h"
#include <vector>

void UpdateEnemyShips(std::vector<Planet>& planets, std::vector<Ship>& ships);

#endif // ENEMY_H