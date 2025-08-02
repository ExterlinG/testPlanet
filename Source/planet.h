#pragma once
#include "types.h"
//#include "globalGameData.h"
//enum PlanetType 
//{
//    NEUTRAL,
//    PLAYER,
//    ENEMY1,
//    ENEMY2
//};

struct Planet 
{
    int positionIndex;  // „I„~„t„u„{„ƒ „r „}„p„ƒ„ƒ„y„r„u line[]
    PlanetType type;
    int shipsCount = 0;
    int lastSpawnTime = 0;
};

void PlanetInit();
void PlanetUpdate();
void PlanetDraw();
void PlanetRelease();

void PlanetReset();