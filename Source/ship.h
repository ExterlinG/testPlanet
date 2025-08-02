#include "DxLib.h"
#include <vector>
#include <unordered_map>
#include "planet.h"
#include "struct.h"


struct Ship 
{
    int fromPlanetIndex;
    int toPlanetIndex;
    int count;
    float progress; // 0.0 - 1.0
    int startTime;
    int graphicHandle; // �D�|�� �p�~�y�}�p���y�y �{�����p�q�|��
};


    std::vector<Ship> activeShips;
    const float SHIP_SPEED = 5.0f; // 5 ���u�{���~�t �~�p ���u���u�}�u���u�~�y�u
    int shipGraphic = -1;


    void ShipInit();
    void ShipUpdate();
    void ShipDraw();
    void SendShips(int fromPlanet, int toPlanet, int count);
    void ClearAllShips();
    void ShipRelease();
    void ShipReset();

    // �D�|�� �r�y�x���p�|�y�x�p���y�y �r���q�����p
    static void DrawSelectionCircle(const VectorI2& position);
