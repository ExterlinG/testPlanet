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
    for (size_t i = 0; i < planets.size(); i++) {
        auto& planet = planets[i];

        // �S���|���{�� �t�|�� �r���p�w�u���{�y�� ���|�p�~�u�� (ENEMY1 �y�|�y ENEMY2)
        if (planet.type != ENEMY1 && planet.type != ENEMY2) continue;

        // �E���|�y �{�����p�q�|�u�z �q���|�����u 10
        if (planet.shipsCount > 10) {
            // �P���|�����p�u�} �t�����������~���u ���u���u�����t�� �t�|�� ���u�{�����u�z ���|�p�~�u����
            auto it = transitionMap.find(planet.id);
            if (it == transitionMap.end()) {
                std::cout << "No transitions for planet " << planet.id << std::endl;
                continue;
            }

            // �I���u�} ���u���r���� �t�����������~���� �����w���� ���|�p�~�u����
            int targetIdx = -1;
            for (auto& transition : it->second) {
                int targetPlanetId = transition.second; // �A�u���u�} �r���������z ���|�u�}�u�~�� ���p���� (ID ���u�|�u�r���z ���|�p�~�u����)

                // �N�p�����t�y�} �y�~�t�u�{�� ���|�p�~�u���� ���� ID
                for (size_t j = 0; j < planets.size(); j++) {
                    if (planets[j].id == targetPlanetId && planets[j].type != planet.type) {
                        targetIdx = j;
                        break;
                    }
                }

                if (targetIdx != -1) break;
            }

            // �E���|�y �~�p���|�y �t�����������y�}���� ���u�|��
            if (targetIdx != -1) {
                std::cout << "ENEMY AI: Sending ships from planet " << planet.id
                    << " to " << planets[targetIdx].id << std::endl;

                // �I�������|���x���u�} �������u�����r���������� �����~�{���y�� ���������p�r�{�y
                SendShips(i, targetIdx);
            }
            else {
                std::cout << "No valid targets for planet " << planet.id << std::endl;
            }
        }
    }
}