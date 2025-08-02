#include <DxLib.h>
#include <assert.h>
#include "config.h"
#include "struct.h"
#include "player.h"
#include <vector>


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
	//----------------------------------------------


}
void Collision();
void Move();
void DeadFall();
void PlayerInit()
{
	
	
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
}

void PlayerDraw()
{
	
	DrawRectGraph((int)pos.x, (int)pos.y, cell.x * 80, cell.y * 80, 96, 112, humanShipImage, true, xFlip);
	DrawCircle(line[0].x + PLANET_CENTER, line[0].y + PLANET_CENTER, 35, 0XFFFFFF, false, 5.0f);
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
	if ((key & PAD_INPUT_RIGHT) != 0) 
	{
		
	}
	else if ((key & PAD_INPUT_LEFT) != 0) 
	{

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
}
