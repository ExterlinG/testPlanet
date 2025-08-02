#pragma once

void PlayerInit();
void PlayerUpdate();
void PlayerDraw();
void PlayerRelease();

void PlayerReset();

bool PlayerIsDead();
void PlayerMove();
void MoveControllerTo(float x, float y);
void DrawArrow(int x, int y, float angle, int color, float size);
void DrawAvailableTransitions();