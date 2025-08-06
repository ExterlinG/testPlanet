#pragma once
struct Ship;
#include "ship.h"
#include <vector>
#include "planet.h"
#include <unordered_map>
//#include "struct.h"
constexpr size_t LINE_SIZE = 19;
extern std::vector<Planet> planets;
extern std::vector<Ship> activeShips;
//extern std::vector<std::shared_ptr<Planet>> planets;
extern VectorI2 line[];
extern const std::unordered_map<int, std::vector<std::pair<int, int>>> transitionMap;
extern const float SHIP_SPEED;
extern int shipGraphicEngine;
extern int shipGraphic;
extern const int RIGHT;
extern const int LEFT;
extern const int UP;
extern const int DOWN;
extern struct GameResultStruct {
    bool isVictory = false;
    bool isTimeOver = false;
    bool isLose = false;
};
extern GameResultStruct GameResult;
//extern struct GameResult GameResult;

//extern const int line_size = sizeof(line) / sizeof(line[0]);

//struct VectorI2 {
//    int x, y;
//};
//
//enum PlanetType {
//    NEUTRAL,
//    PLAYER,
//    ENEMY1,
//    ENEMY2
//};
//
//struct Vector2 {
//    float x, y;
//};


