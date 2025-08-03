#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "planet.h"
#include "ship.h"
#include <vector>
#include <memory>

// �O�q�~���r�|�v�~�~���u �����~�{���y�y, ���p�q�����p�����y�u �� vector<Planet> �r�}�u������ shared_ptr
void UpdateEnemyLogic(int faction, std::vector<Planet>& planets, std::vector<std::shared_ptr<Ship>>& ships);
Planet* FindNearestEnemyPlanet(Planet* fromPlanet, int faction, std::vector<Planet>& planets);

#endif // ENEMY_H