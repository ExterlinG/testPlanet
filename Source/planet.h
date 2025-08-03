#pragma once
#include "types.h"
#include <vector>
//#include "globalGameData.h"
//enum PlanetType 
//{
//    NEUTRAL,
//    PLAYER,
//    ENEMY1,
//    ENEMY2
//};
//extern std::vector<std::shared_ptr<Planet>> planets;/
struct Planet 
{
    int positionIndex;  // �I�~�t�u�{�� �r �}�p�����y�r�u line[]
    PlanetType type;
    int faction = 0; // �D���q�p�r�|�u�~�� �����|�u faction �t�|�� �����r�}�u�����y�}�������y �� enemy.cpp
    int shipsCount = 0;
    int lastSpawnTime = 0;
    Vector2 position;
};

void PlanetInit();
void PlanetUpdate();
void PlanetDraw();
void PlanetRelease();

void PlanetReset();