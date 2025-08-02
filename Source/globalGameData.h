#pragma once
#include <vector>
#include "planet.h"
#include "ship.h"
//#include "struct.h"

extern std::vector<Planet> planets;
extern std::vector<Ship> activeShips;
extern const VectorI2 line[];
extern const std::unordered_map<int, std::vector<std::pair<int, int>>> transitionMap;
extern const float SHIP_SPEED;
extern int shipGraphic;
extern const int RIGHT;
extern const int LEFT;
extern const int UP;
extern const int DOWN;
//extern const int line_size = sizeof(line) / sizeof(line[0]);

struct VectorI2 {
    int x, y;
};

enum PlanetType {
    NEUTRAL,
    PLAYER,
    ENEMY1,
    ENEMY2
};

struct Vector2 {
    float x, y;
};


