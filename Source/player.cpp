#include <DxLib.h>
#include <assert.h>
#include "config.h"
#include "struct.h"
#include "player.h"


namespace
{
	static const int COLLISION_SIZE = 36;
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
	pos.x = 300.0f;
	
	cell.x = 0;
	cell.y = 0;


	dead = false;

	state = PlayerState::STAY;
	//walkCounter = 0;
	//deadCounter = 0;

	xFlip = false;
}

void PlayerUpdate();
void PlayerDraw()
{
	DrawRectGraph((int)pos.x, (int)pos.y, cell.x * 80, cell.y * 80, 96, 112, humanShipImage, true, xFlip);
}
void PlayerRelease()
{
	if (humanShipImage > 0) {
		DeleteGraph(humanShipImage);
		humanShipImage = -1;
	}
}