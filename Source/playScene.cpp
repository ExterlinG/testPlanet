#include <DxLib.h>
#include <assert.h>
#include "types.h"
#include "globalGameData.h"

#include "playScene.h"
#include "planet.h"
#include "ship.h"

#include "player.h"
#include "app.h"
//#include "struct.h"
#include "math.h"
#include <vector>
#include <utility>
#include "enemy.h"

#include <memory>



//extern std::vector<std::shared_ptr<Planet>> planets;// „B playScene.cpp
////std::vector<std::shared_ptr<Planet>> planets;
//extern std::vector<Planet> planets;
namespace {
	enum class PlayStatus {
		BEFORE_PLAY,
		IN_PLAY,
		AFTER_PLAY,
	};
	
	PlayStatus status;

	int galaxy = -1;		//game‚Ì”wŒi‰æ‘œ‚Ìƒnƒ“ƒhƒ‹
	int groundImage = -1;	//’n–Ê‚Ì‰æ‘œƒnƒ“ƒhƒ‹
	int lines = -1;

	int startCounter;	//ƒQ[ƒ€‚Ìn‚Ü‚é‚Æ‚«‚ÌƒJƒEƒ“ƒ^[
	int deadCounter;		//€‚ñ‚¾‚ÌƒJƒEƒ“ƒ^[

	int distanceImage = -1;	//i‚ñ‚¾‹——£‚ğ•\‚·‰æ‘œ
	int playTime;	//i‚ñ‚¾‹——£‚ğ•\‚·ƒJƒEƒ“ƒ^[

	int playSound = -1;	//ƒXƒ^[ƒg‚Ì‰¹ƒnƒ“ƒhƒ‹
	int walkCounter;

	int lineWalkCounter;
	//----------------------------------------------
	

	VectorI2 planet[] = { {689,128},{848, 96},{1008, 128},
							{1136, 224},{1192, 368},{1096, 509},
							{1456, 428},{1408, 592},{1280, 720},
							{1104, 768},{944, 704},{848, 560},
							{848.5, 911},{704, 800},{624, 640},
							{655, 464},{785, 352},{960, 336},{960,476} };
	const int planet_size = sizeof(planet) / sizeof(planet[0]);
	//----------------------------------------------
	

	//VectorI2 line[] = { {689,128},{848, 96},{1008, 128},
	//					{1136, 224},{1192, 368},{1096, 509},
	//					{1456, 428},{1408, 592},{1280, 720},
	//					{1104, 768},{944, 704},{848, 560},
	//					{848.5, 911},{704, 800},{624, 640},
	//					{655, 464},{785, 352},{960, 336},{960,476} };
	//const int line_size = sizeof(line) / sizeof(line[0]);

	//----------------------------------------------
	const std::pair<int, int> extraConnections[] = {
		{3, 17}, {4, 17}, {5, 18}, {9, 5},
		{10, 5}, {5, 11}, {11, 17}, {16, 11},
		{18, 11}, {17, 5},{15, 11}
	};



	//----------------------------------------------
	VectorI2 lineToPlanet;

	int patternLine;
	int patternPlanet;
	//----------------------------------------------
	VectorI2 lineAngle[];
	double dx;
	double dy;

	static const float PLANET_CENTER = 48.0;

	double planetAngle[planet_size];
	double extraAngles[10];
	//double planetAngle = 1.57f;
	//double enemyScale = 0.5f;

	double enemyPosX = 848.0f;	//ƒGƒlƒ~[‚ÌÀ•W
	double enemyPosY = 96.0f;

	std::vector<std::shared_ptr<Ship>> ships;

	//debug
	int color;
	static const bool DEBUG_FONT = true;
};

void PlaySceneInit()
{
	if (galaxy < 0) {
		galaxy = LoadGraph("data\\texture\\galaxy\\galaxy1.png");
		assert(galaxy >= 0);
	}
	if (lines < 0) {
		lines = LoadGraph("data\\texture\\lines\\mylines2.png");
		assert(lines >= 0);
	}
	if (groundImage < 0) {
		groundImage = LoadGraph("data\\texture\\planet\\planet.png");
		assert(groundImage >= 0);
	}
	if (distanceImage < 0) {
		distanceImage = LoadGraph("data\\texture\\ui\\num02.png");
		assert(distanceImage >= 0);
	}
	if (playSound < 0) {
		playSound = LoadSoundMem("data\\sound\\playSound\\playSound.wav");
		assert(playSound >= 0);
	}
	//planets.clear();
	//for (int i = 0; i < planet_size; ++i) {
	//	auto p = std::make_shared<Planet>();
	//	p->positionIndex = i;
	//	p->type = NEUTRAL; // „y„|„y „t„‚„…„s„€„z „„„y„, „u„ƒ„|„y „~„…„w„~„€
	//	p->faction = 0;
	//	p->shipsCount = 0;
	//	p->lastSpawnTime = 0;
	//	p->position.x = planet[i].x;
	//	p->position.y = planet[i].y;
	//	planets.push_back(p);
	//}
	PlanetInit();
	PlayerInit();
	ShipInit();
	ships.clear();
	walkCounter= 0;
	patternLine = 0;
	patternPlanet = 0;
	


	//debug
	color = GetColor(255, 255, 255);

}
void PlaySceneUpdate()
{
	PlayerUpdate();
	ShipUpdate();
	PlanetUpdate();
	// „R„„„p„|„€ („u„ƒ„|„y ships - vector<shared_ptr<Ship>>):
	std::vector<Ship> rawShips;
	for (auto& shipPtr : ships) {
		rawShips.push_back(*shipPtr);
	}
	UpdateEnemyLogic(1, planets, rawShips);
	patternPlanet = (walkCounter / 6)% 77;

	walkCounter++;
	lineWalkCounter++;
	patternLine = (lineWalkCounter / 10) % 10;
	
	//if (lineWalkCounter > 60)
	//{
	//	lineToPlanet.x += 2;
	//	lineWalkCounter = 0;
	//	lineToPlanet.x - ;
	//}
		//–Ú•WÀ•WiƒvƒŒƒCƒ„[j‚©‚çƒGƒlƒ~[‚ÌÀ•W‚ğ‚ğˆø‚¢‚ÄƒxƒNƒgƒ‹d‚ğ‹‚ß‚é(dx,dy)

	//angle
	CalculatePlanetAngles(planetAngle);

	//extra angle
	CalculateExtraAngles(extraAngles);
	
	//for (int i = 0; i < planet_size; i++)
	//{
	//	double dx[i] = ((planet[i].x + PLANET_CENTER) - (planet[i + 1].x + PLANET_CENTER));
	//	double dy[i] = ((planet[i].y + PLANET_CENTER) - (planet[i + 1].y + PLANET_CENTER));
	//	planetAngle[i] = atan2(dy[i], dx[i]);
	//}
	
	//double dx =-(enemyPosX+48);
	//double dy =176.0-(enemyPosY+48);

	//planetAngle = atan2(dy, dx);

	//Angle‚Æ‘¬“x‚ğ‘«‚µ‚ÄÀ•W‚ğ•Ï‚¦‚é
	//enemyPosX = cos(planetAngle);
	//enemyPosY = sin(planetAngle);

}

void PlaySceneDraw()
{
	
	ClearDrawScreen();
	//DrawRotaGraph(500, 500,1.0,45,lines,false, false);
	DrawGraph(0, 0, galaxy, true);
	DistanceMeter(170, 30);


	//line

	DrawLines(planetAngle);
	//more center lines „t„€„„€„|„~„y„„„u„|„„~„„u „|„y„~„y„y.
		DrawExtraLines(extraAngles);
		//DrawRectRotaGraph2((line[11].x + PLANET_CENTER), line[11].y + PLANET_CENTER, patternLine * 16, 112, 80, LINE_SPRITE_WIDTH + PLANET_CENTER, LINE_SPRITE_HEIGHT + PLANET_CENTER, 0, 1, planetAngle[11], lines, true, false);
	
		//DrawRectRotaGraph2(848 + PLANET_CENTER, 96 + PLANET_CENTER, patternLine * 16, 112, 80, 16, -48, 0, 1, planetAngle, lines, true, false);//lines red-gray 1
		//DrawRectRotaGraph2(1008 + PLANET_CENTER, 128 + PLANET_CENTER, patternLine * 16, 112, 80, 16, -48, 0, 1, planetAngle, lines, true, false);//lines gray 1- gray 2

		//planet position
		
		for (int i = 0; i < planet_size; i++)

		{
			DrawRectGraph(planet[i].x, planet[i].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false);
		}

		PlanetDraw();
		ShipDraw();
		PlayerDraw();
		ScreenFlip();
		//DrawRectGraph(planet[18].x, planet[18].y, patternPlanet *96, 0, 96, 96, groundImage, true, false); //middle
		//DrawRectGraph(planet[17].x, planet[17].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 15
		//DrawRectGraph(planet[16].x, planet[16].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 14
		//DrawRectGraph(planet[15].x, planet[15].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 13
		//DrawRectGraph(planet[14].x, planet[14].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 12
		//DrawRectGraph(planet[13].x, planet[13].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 11
		//DrawRectGraph(planet[12].x, planet[12].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //blue

		//DrawRectGraph(planet[11].x, planet[11].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 10
		//DrawRectGraph(planet[10].x, planet[10].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 9
		//DrawRectGraph(planet[9].x, planet[9].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 8
		//DrawRectGraph(planet[8].x, planet[8].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 7
		//DrawRectGraph(planet[7].x, planet[7].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 6
		//DrawRectGraph(planet[6].x, planet[6].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //yelloy

		//DrawRectGraph(planet[5].x, planet[5].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 5
		//DrawRectGraph(planet[4].x, planet[4].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 4
		//DrawRectGraph(planet[3].x, planet[3].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 3
		//DrawRectGraph(planet[2].x, planet[2].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 2
		//DrawRectGraph(planet[1].x, planet[1].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 1
		//DrawRectGraph(planet[0].x, planet[0].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //red

			//1. planet[3] „y planet[17].
			//2. planet[4] „y planet[17].
			//3. planet[5] „y planet[18].
			//4. planet[9] „y planet[5].
			//5. planet[10] „y planet[5].
			//6. planet[5] „y planet[11].
			//7. planet[11] „y planet[17].
			//8. planet[16] „y planet[11].
			//9. planet[17] „y planet[11].
			//10. planet[17] „y planet[5].
			

			//1. planet[17] „y planet[18].
			//2. planet[11] „y planet[18].
			//3. planet[3] „y planet[11].
			//4. planet[4] „y planet[11].
			//5. planet[11] „y planet[5].
			//6. planet[17] „y planet[11].
			//7. planet[9] „y planet[17].
			//8. planet[10] „y planet[17].
			//9. planet[16] „y planet[5].
			//10. planet[15] „y planet[5].
			//11. planet[5] „y planet[17].
		//DrawRectGraph(689, 128, linePos.x*16, 112, 80, 16, lines, true, false); //lines
		//DrawRotaGraph2(848, 128, linePos.x*16, 112, 1, planetAngle, lines, true, false);
		//DrawRectRotaGraph(enemyPosX, enemyPosY, linePos.x*16, 112,80,16, 1, planetAngle, lines, true, false);//lines rotated
		//DrawRectRotaGraph2(848+48, 96+48, linePos.x * 16, 112, 80, 16, 0, 0, 1, planetAngle, lines, true, false);//lines rotated



		if (DEBUG_FONT) {
			//DrawFormatString(20, 30, color, "EnemyStatus");
			//DrawFormatString(20, 50, color, "PosX %f, PosY %f ", enemyPosX, enemyPosY);

			//Angle‚ÍŠp“x‚Å‚Í‚È‚­Aƒ‰ƒWƒAƒ“i1.5790“xj‚Å•\Œ»‚³‚ê‚é
			//75s–Ú‚Ì’†g
			//DrawFormatString(20, 70, color, "Angle %f ", planetAngle);

			//XÀ•W‚ÆYÀ•W‚Ö‚ÌˆÚ“®—Ê
			//78s–ÚA79s–Ú‚Ì’†g
			//DrawFormatString(20, 120, color, "XMove %f ", cos(planetAngle));
			//DrawFormatString(20, 140, color, "YMove %f ", sin(planetAngle));
		}
	}

void PlaySceneRelease()
{
	PlayerRelease();

	if (playSound > 0) {
		DeleteSoundMem(playSound);
		playSound = -1;
	}
	if (groundImage > 0) {
		DeleteGraph(groundImage);
		groundImage = -1;
	}
	if (galaxy > 0) {
		DeleteGraph(galaxy);
		galaxy = -1;
	}
	if (lines > 0) {
		DeleteGraph(lines);
		lines = -1;
	}
	if (distanceImage > 0) {
		DeleteGraph(distanceImage);
		distanceImage = -1;
	}
}

void PlaySceneReset()
{
	status = PlayStatus::BEFORE_PLAY;
	playTime = 0;
	startCounter = 0;
	deadCounter = 0;
	PlaySoundMem(playSound, DX_PLAYTYPE_BACK);
	PlayerReset();
}

void DistanceMeter(int x, int y) {
	int meter = playTime / 5;
	int copy = meter;
	int dig = 0;
	do {
		DrawRectGraph(x - (32 * dig), y, copy % 10 * 32, 0, 32, 64, distanceImage, true, false);
		copy = copy / 10;
		dig++;
	} while (copy > 0);
}

void CalculatePlanetAngles(double planetAngle[]) {  // first lines „|„y„~„y„y „ƒ„r„‘„x„„r„p„„‹„y„u „„|„p„~„u„„„ „„€„ƒ„|„u„t„€„r„p„„„u„|„„~„€
	for (int i = 0; i < planet_size; i++) {
		int next_idx = (i + 1) % planet_size;

		double dx = (planet[i].x + PLANET_CENTER) - (planet[next_idx].x + PLANET_CENTER);
		double dy = (planet[i].y + PLANET_CENTER) - (planet[next_idx].y + PLANET_CENTER);


		planetAngle[i] = atan2(dy, dx);  // atan2 „r„€„x„r„‚„p„‹„p„u„„ double
	}
}
// more lines „t„€„„€„|„~„y„„„u„|„„~„„u „|„y„~„y„y
void CalculateExtraAngles(double extraAngles[]) {
	// „P„p„‚„ „„|„p„~„u„„ „t„|„‘ „t„€„„€„|„~„y„„„u„|„„~„„‡ „ƒ„€„u„t„y„~„u„~„y„z

	for (int i = 0; i < 11; i++) {
		int idx1 = extraConnections[i].first;
		int idx2 = extraConnections[i].second;

		double dx = (planet[idx2].x + PLANET_CENTER) - (planet[idx1].x + PLANET_CENTER);
		double dy = (planet[idx2].y + PLANET_CENTER) - (planet[idx1].y + PLANET_CENTER);
		extraAngles[i] = atan2(dy, dx);
	}
}

void DrawExtraLines(double extraAngles[]) {
	const int LINE_SPRITE_WIDTH = 16;
	const int LINE_SPRITE_HEIGHT = 70;

	// „P„p„‚„ „„|„p„~„u„„ „t„|„‘ „t„€„„€„|„~„y„„„u„|„„~„„‡ „ƒ„€„u„t„y„~„u„~„y„z („„„p„{„y„u „w„u „{„p„{ „r CalculateExtraAngles)
			//1. planet[3] „y planet[17].
			//2. planet[4] „y planet[17].
			//3. planet[5] „y planet[18].
			//4. planet[9] „y planet[5].
			//5. planet[10] „y planet[5].
			//6. planet[5] „y planet[11].
			//7. planet[11] „y planet[17].
			//8. planet[16] „y planet[11].
			//9. planet[11] „y planet[18].
			//10. planet[17] „y planet[5].

	//const std::pair<int, int> extraConnections[] = {
	//	{3, 17}, {4, 17}, {5, 18}, {9, 5},
	//	{10, 5}, {5, 11}, {11, 17}, {16, 11},
	//	{18, 11}, {17, 5}
	//};

	for (int i = 0; i < 11; i++) {
		int idx1 = extraConnections[i].first;
		int idx2 = extraConnections[i].second;

		// „B„„‰„y„ƒ„|„‘„u„} „ƒ„u„‚„u„t„y„~„… „}„u„w„t„… „„|„p„~„u„„„p„}„y
		int midX = (planet[idx1].x + planet[idx2].x) / 2;
		int midY = (planet[idx1].y + planet[idx2].y) / 2;

		// „O„„„‚„y„ƒ„€„r„„r„p„u„} „p„~„y„}„y„‚„€„r„p„~„~„…„ „|„y„~„y„
		DrawRectRotaGraph2(midX + PLANET_CENTER,midY + PLANET_CENTER,patternLine * 16,112,144,LINE_SPRITE_WIDTH,LINE_SPRITE_HEIGHT,0,1,extraAngles[i],lines,true,false);
		DrawLineAA(line[idx1].x + PLANET_CENTER, line[idx1].y + PLANET_CENTER, line[idx2].x + PLANET_CENTER, line[idx2].y + PLANET_CENTER, GetColor(2, 194, 240), 2.0f);
	}
}
void DrawLines(double planetAngle[])
{
	const int LINE_SPRITE_WIDTH = 16;
	const int LINE_SPRITE_HEIGHT = 100;
	for (int i = 0; i < LINE_SIZE; i++)
	{
		bool skipLine = (i == 5 || i == 11 || i == 18);


		if (!skipLine) {
			DrawRectRotaGraph2((line[i].x + PLANET_CENTER), line[i].y + PLANET_CENTER, patternLine * 16, 112, 144, LINE_SPRITE_WIDTH + PLANET_CENTER, LINE_SPRITE_HEIGHT + PLANET_CENTER, 0, 1, planetAngle[i], lines, true, false);
			DrawLineAA((line[i].x + PLANET_CENTER), line[i].y + PLANET_CENTER, (line[i + 1].x + PLANET_CENTER), (line[i + 1].y + PLANET_CENTER), GetColor(2, 194, 240), 2.0f);
		}
	}
}

