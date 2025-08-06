#pragma once
#ifndef UI_H
#define UI_H

#include "DxLib.h"
#include "types.h" // �D�|�� PlanetType

// �R�������{�������p �����p���y�����y�{�y
struct FactionStats {
    int shipsProduced;
    int shipsLost;
    int shipsDestroyed;
    int planetsControlled;
    int portraitGraph;
};

// �C�|���q�p�|���~���u ���u���u�}�u�~�~���u �����p���y�����y�{�y
extern FactionStats g_playerStats;
extern FactionStats g_enemy1Stats;
extern FactionStats g_enemy2Stats;
extern int g_uiFont;

// �I�~�y���y�p�|�y�x�p���y�� UI
void InitUI();

// �O�q�~���r�|�u�~�y�u �����p���y�����y�{�y
void UpdateFactionStats(PlanetType faction);

// �O�����y�����r�{�p �y�~���u�����u�z���p
void DrawPlayerUI();
void DrawEnemy1UI();
void DrawEnemy2UI();

#endif