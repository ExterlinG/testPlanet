#include <DxLib.h>
#include <assert.h>
#include "config.h"
#include "struct.h"
#include "player.h"
#include <vector>
#include <unordered_map>


namespace
{
	static const float PLANET_CENTER = 48.0;
	int humanShipImage = -1;
	Vector2 pos;		//planetワギャンの座標
	VectorI2 cell;		//planetの画像のアニメーション座標

	bool xFlip;			//playerの向き
	bool dead;			//player 死んでいるか否か

	enum class PlayerState {
		NO_STATE = 0,
		STAY,
		RIGHT,
		LEFT,
		DEAD,
	};
	PlayerState state;
	int key;	//ジョイパットの入力を確認する変数
	//lines 
	VectorI2 line[] = { {689,128},{848, 96},{1008, 128},
						{1136, 224},{1192, 368},{1096, 509},
						{1456, 428},{1408, 592},{1280, 720},
						{1104, 768},{944, 704},{848, 560},
						{848.5, 911},{704, 800},{624, 640},
						{655, 464},{785, 352},{960, 336},{960,476} };
	const int line_size = sizeof(line) / sizeof(line[0]);

	
	const std::pair<int, int> extraConnections[] = {
		{3, 17}, {4, 17}, {5, 18}, {9, 5},
		{10, 5}, {5, 11}, {11, 17}, {16, 11},
		{18, 11}, {17, 5},{15, 11}
	};

	// Матрица допустимых переходов: [текущая_позиция] = {доступные_позиции}
	const std::unordered_map<int, std::vector<std::pair<int, int>>> transitionMap =
	{
	{0, {RIGHT,1}},            // {689,128} → {848,96} или {960,476}
	{1, {{LEFT,0}, {RIGHT,2}},             // {848,96} ↔ {1008,128}
	{2, {{LEFT,1}, {RIGHT,3}},             // {1008,128} → {1136,224}
	{3, {{LEFT,2}, 4, 17}},         // {1136,224} → {1192,368} или {785,352}
	{4, {3, 5, 17}},         // {1192,368} → {1096,509} или {785,352}
	{5, {4, 11, 17}},     // {1096,509} → {1456,428}, {848,560} или {960,476}
	{6, {7}},             // {1456,428} → {1408,592}
	{7, {6, 8}},             // {1408,592} → {1280,720}
	{8, {7, 9}},             // {1280,720} → {1104,768}
	{9, {8, 10, 5}},         // {1104,768} → {944,704} или обратно в {1096,509}
	{10, {9, 11, 5}},        // {944,704} → {848,560} или {1096,509}
	{11, {10, 5, 17}},   // {848,560} → {848.5,911}, {1096,509} или {785,352}
	{12, {13}},          // {848.5,911} → {704,800}
	{13, {12, 14}},          // {704,800} → {624,640}
	{14, {13, 15}},          // {624,640} → {655,464}
	{15, {14, 16, 11}},      // {655,464} → {785,352} или {848,560}
	{16, {15, 17, 11}},      // {785,352} → {960,336}, {848,560} или {655,464}
	{17, {3, 4, 11, 16,18,5}}, // {960,336} ↔ {1136,224}, {1192,368}, {1096,509}, {848,560}, {785,352}
	{18, {17,5, 11}}         // {960,476} → {689,128}, {1096,509} или {848,560}
	};
	
	//----------------------------------------------
	float startPosX;
	float startPosY;

	int currentPosition;
	bool pressRight = false;
	bool pressLeft = false;
}
void Collision();
void Move();
void DeadFall();
void PlayerInit()
{
	currentPosition = 0; // Текущая позиция в массиве line
	startPosX = line[0].x;
	startPosY = line[0].y;
	
	if (humanShipImage < 0) {
		humanShipImage = LoadGraph("data\\texture\\humanShip\\battlecruiser.png");
		assert(humanShipImage >= 0);
	}
	PlayerReset();
}

void PlayerReset()
{
	//pos.x = 300.0f;
	//
	//cell.x = 0;
	//cell.y = 0;


	//dead = false;

	state = PlayerState::STAY;
	//walkCounter = 0;
	//deadCounter = 0;

	xFlip = false;
}

void PlayerUpdate() 
{
	key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	PlayerMove();
}

void PlayerDraw()
{
	
	DrawRectGraph((int)pos.x, (int)pos.y, cell.x * 80, cell.y * 80, 96, 112, humanShipImage, true, xFlip);
	DrawCircle(startPosX + PLANET_CENTER, startPosY + PLANET_CENTER, 35, 0XFFFFFF, false, 5.0f);
}
void PlayerRelease()
{
	if (humanShipImage > 0) {
		DeleteGraph(humanShipImage);
		humanShipImage = -1;
	}
}

void PlayerMove()
{
	bool RightPressed = (key & PAD_INPUT_RIGHT) != 0;
	bool LeftPressed = (key & PAD_INPUT_LEFT) != 0;
	
	if (RightPressed && !pressRight)
	{
		auto it = transitionMap.find(currentPosition);
		if (it != transitionMap.end() && !it->second.empty()) 
		{
			// Находим следующую точку в допустимых переходах
			int nextPos = -1;
			for (int i = 0; i < it->second.size(); i++) 
			{
				if (it->second[i] > currentPosition) 
				{
					nextPos = it->second[i];
					break;
				}
			}
			if (nextPos == -1) nextPos = it->second.back();

			currentPosition = nextPos;
			MoveControllerTo(line[currentPosition].x, line[currentPosition].y);
		}	
	}
	else if (LeftPressed && !pressLeft)
	{
		auto it = transitionMap.find(currentPosition);
		if (it != transitionMap.end() && !it->second.empty()) {
			// Находим предыдущую точку в допустимых переходах
			int prevPos = -1;
			for (int i = it->second.size() - 1; i >= 0; i--) {
				if (it->second[i] < currentPosition) {
					prevPos = it->second[i];
					break;
				}
			}
			if (prevPos == -1) prevPos = it->second.front();

			currentPosition = prevPos;
			MoveControllerTo(line[currentPosition].x, line[currentPosition].y);
		}
	}
	else if ((key & PAD_INPUT_UP) != 0)
	{

	}
	else if ((key & PAD_INPUT_DOWN) != 0)
	{

	}
	else if ((key & PAD_INPUT_A) != 0)
	{
		
	}
	pressRight = RightPressed;
	pressLeft = LeftPressed;
	VectorI2 newPosition = line[currentPosition];
	MoveControllerTo(newPosition.x, newPosition.y);
}
void MoveControllerTo(float x, float y)
{
	startPosX = x;
	startPosY = y;
}
