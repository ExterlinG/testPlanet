#include "DxLib.h"
#include <vector>
#include <unordered_map>
#include "planet.h"
#include "types.h"
//#include "struct.h"
#include "globalGameData.h"


struct Ship {
    int fromPlanetIndex;
    int toPlanetIndex;
    int count;
    float progress;
    int startTime;
};


    //std::vector<Ship> activeShips;
    //const float SHIP_SPEED = 5.0f; // 5 „ƒ„u„{„…„~„t „~„p „„u„‚„u„}„u„‹„u„~„y„u
    //int shipGraphic = -1;


    void ShipInit();
    void ShipUpdate();
    void ShipDraw();
    void SendShips(int fromPlanet, int toPlanet, int count);
    void ClearAllShips();
    void ShipRelease();
    void ShipReset();

    // „D„|„‘ „r„y„x„…„p„|„y„x„p„ˆ„y„y „r„„q„€„‚„p
    //static void DrawSelectionCircle(const VectorI2& position);
