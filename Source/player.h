#pragma once

void PlayerInit();
void PlayerUpdate();
void PlayerDraw();
void PlayerRelease();

void PlayerReset();

bool PlayerIsDead();
void PlayerMove();
void MoveControllerTo(float x, float y);