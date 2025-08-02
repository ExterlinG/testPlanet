#pragma once

void AppInit();

void AppUpdate();

void AppDraw();

void AppRelease();

bool IsAllKeyPush();

enum class Scene {
	TITLE,
	PLAY,
	GAMEOVER,
};

void ChangeScene(Scene next);