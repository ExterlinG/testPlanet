#pragma once
#include "DxLib.h"
#include "planet.h"
#include "types.h"
#include <vector>
#include <unordered_map>
//#include "globalGameData.h"

// „R„„„‚„…„{„„„…„‚„p „{„€„‚„p„q„|„‘ („x„p„r„y„ƒ„y„„ „„„€„|„„{„€ „€„„ „q„p„x„€„r„„‡ „„„y„„€„r)
struct Ship 
{
    int fromPlanetIdx;  // „I„~„t„u„{„ƒ „„|„p„~„u„„„-„€„„„„‚„p„r„y„„„u„|„‘ „r „r„u„{„„„€„‚„u planets
    int toPlanetIdx;    // „I„~„t„u„{„ƒ „„|„p„~„u„„„-„ˆ„u„|„y „r „r„u„{„„„€„‚„u planets
    int count;          // „K„€„|„y„‰„u„ƒ„„„r„€ „{„€„‚„p„q„|„u„z „r „s„‚„…„„„u
    float progress;     // „P„‚„€„s„‚„u„ƒ„ƒ „„u„‚„u„}„u„‹„u„~„y„‘ (0.0 - 1.0)
};
//struct Planet 
//{
//    int positionIndex;  
//    PlanetType type;
//    int shipsCount = 0;
//    int lastSpawnTime = 0;
//};
void ShipInit();
void ShipUpdate();
void ShipDraw();
void SendShips(int fromPlanetIdx, int toPlanetIdx);
void ClearAllShips();
void ShipRelease();
void ShipReset();

//// „R„„„‚„…„{„„„…„‚„p „{„€„‚„p„q„|„‘ („x„p„r„y„ƒ„y„„ „„„€„|„„{„€ „€„„ „q„p„x„€„r„„‡ „„„y„„€„r)
//struct Ship 
//{
//    int fromPlanetIdx;  // „I„~„t„u„{„ƒ „„|„p„~„u„„„-„€„„„„‚„p„r„y„„„u„|„‘ „r „r„u„{„„„€„‚„u planets
//    int toPlanetIdx;    // „I„~„t„u„{„ƒ „„|„p„~„u„„„-„ˆ„u„|„y „r „r„u„{„„„€„‚„u planets
//    int count;          // „K„€„|„y„‰„u„ƒ„„„r„€ „{„€„‚„p„q„|„u„z „r „s„‚„…„„„u
//    float progress;     // „P„‚„€„s„‚„u„ƒ„ƒ „„u„‚„u„}„u„‹„u„~„y„‘ (0.0 - 1.0)
//};
//
//
//    //std::vector<Ship> activeShips;
//    //const float SHIP_SPEED = 5.0f; // 5 „ƒ„u„{„…„~„t „~„p „„u„‚„u„}„u„‹„u„~„y„u
//    //int shipGraphic = -1;
//
//
//    void ShipInit();
//    void ShipUpdate();
//    void ShipDraw();
//    void SendShips(int fromPlanetIdx, int toPlanetIdx);
//    void ClearAllShips();
//    void ShipRelease();
//    void ShipReset();
//
//
//    // „D„|„‘ „r„y„x„…„p„|„y„x„p„ˆ„y„y „r„„q„€„‚„p
//    //static void DrawSelectionCircle(const VectorI2& position);
