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
    int positionIndex;  // „I„~„t„u„{„ƒ „r „}„p„ƒ„ƒ„y„r„u line[]
    PlanetType type;
    int faction = 0; // „D„€„q„p„r„|„u„~„€ „„€„|„u faction „t„|„‘ „ƒ„€„r„}„u„ƒ„„„y„}„€„ƒ„„„y „ƒ enemy.cpp
    int shipsCount = 0;
    int lastSpawnTime = 0;
    Vector2 position;
};

void PlanetInit();
void PlanetUpdate();
void PlanetDraw();
void PlanetRelease();

void PlanetReset();