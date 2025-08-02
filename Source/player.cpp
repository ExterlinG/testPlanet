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
	Vector2 pos;		//planetƒƒMƒƒƒ“‚ÌÀ•W
	VectorI2 cell;		//planet‚Ì‰æ‘œ‚ÌƒAƒjƒ[ƒVƒ‡ƒ“À•W

	bool xFlip;			//player‚ÌŒü‚«
	bool dead;			//player €‚ñ‚Å‚¢‚é‚©”Û‚©

	enum class PlayerState {
		NO_STATE = 0,
		STAY,
		RIGHT,
		LEFT,
		DEAD,
	};
	PlayerState state;
	int key;	//ƒWƒ‡ƒCƒpƒbƒg‚Ì“ü—Í‚ğŠm”F‚·‚é•Ï”
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
	float startPosX;
	float startPosY;

}
void Collision();
void Move();
void DeadFall();
void PlayerInit()
{
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
	int currentPosition = 0; // „S„u„{„…„‹„p„‘ „„€„x„y„ˆ„y„‘ „r „}„p„ƒ„ƒ„y„r„u line
	bool movingRight = true; // „N„p„„‚„p„r„|„u„~„y„u „t„r„y„w„u„~„y„‘
	if ((key & PAD_INPUT_RIGHT) != 0) 
	{
		movingRight = true;
		currentPosition = (currentPosition + 1) % (sizeof(line) / sizeof(line[0]));
	}
	else if ((key & PAD_INPUT_LEFT) != 0) 
	{
		movingRight = false;
		currentPosition = (currentPosition - 1 + sizeof(line) / sizeof(line[0])) % (sizeof(line) / sizeof(line[0]));
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
	VectorI2 newPosition = line[currentPosition];
	MoveControllerTo(newPosition.x, newPosition.y);
}
void MoveControllerTo(int x, int y)
{
	startPosX = x;
	startPosY = y;
}
