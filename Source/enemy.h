#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "planet.h"
#include "ship.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include "types.h"


void UpdateEnemyAI(std::vector<Planet>& planets, std::vector<Ship>& ships);

#endif // ENEMY_H