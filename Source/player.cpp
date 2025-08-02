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
    const int RIGHT = 1;
    const int LEFT = 2;
    const int UP = 4;
    const int DOWN = 8;
	const std::unordered_map<int, std::vector<std::pair<int, int>>> transitionMap =
	{
        // Точка 0 (689,128)
        {0, {
            {RIGHT, 1}  // Вправо → точка 1 (848,96)
        }},

        // Точка 1 (848,96)
        {1, {
            {LEFT, 0},   // Влево → точка 0
            {RIGHT, 2}   // Вправо → точка 2 (1008,128)
        }},

        // Точка 2 (1008,128)
        {2, {
            {LEFT, 1},   // Влево → точка 1
            {RIGHT, 3}   // Вправо → точка 3 (1136,224)
        }},

        // Точка 3 (1136,224)
        {3, {
            {UP, 2},   // Влево → точка 2
            {RIGHT, 4},   // Вправо → точка 4 (1192,368)
            {LEFT, 17}      // Вверх → точка 17 (960,336)
        }},

        // Точка 4 (1192,368)
        {4, {
            {UP, 3},    // Влево → точка 3
            {DOWN, 5},   // Вправо → точка 5 (1096,509)
            {LEFT, 17}      // Вверх → точка 17
        }},

        // Точка 5 (1096,509)
        {5, {
            {UP | RIGHT, 4},           // Влево → точка 4
            {LEFT, 11},         // Вправо → точка 11 (848,560)
            {UP, 17},     // Вверх+Влево → точка 17
            {DOWN | LEFT, 10},    // Вниз+Вправо → точка 6 (1456,428)
            { DOWN, 9 },
            { UP | LEFT, 18 },
        }},

        // Точка 6 (1456,428)
        {6, {
            {DOWN, 7}     // Вправо → точка 7 (1408,592)
        }},

        // Точка 7 (1408,592)
        {7, {
            {UP, 6},     // Влево → точка 6
            {DOWN, 8}     // Вправо → точка 8 (1280,720)
        }},

        // Точка 8 (1280,720)
        {8, {
            {RIGHT, 7},     // Влево → точка 7
            {LEFT, 9}     // Вправо → точка 9 (1104,768)
        }},

        // Точка 9 (1104,768)
        {9, {
            {RIGHT, 8},     // Влево → точка 8
            {LEFT, 10},   // Вправо → точка 10 (944,704)
            {UP, 5}      // Вниз → точка 5
        }},

        // Точка 10 (944,704)
        {10, {
            {RIGHT, 9},     // Влево → точка 9
            {LEFT, 11},   // Вправо → точка 11
            {UP, 5}      // Вниз → точка 5
        }},

        // Точка 11 (848,560)
        {11, {
            {DOWN, 10},    // Влево → точка 10
            {RIGHT, 5},    // Вправо → точка 5
            {UP, 17},      // Вверх → точка 17
            {UP | RIGHT, 18},     // Вниз → точка 18 (960,476)
            {UP | LEFT, 16},
            {LEFT, 15},
        }},

        // Точка 12 (848.5,911)
        {12, {
                
            {LEFT, 13}    // Вправо → точка 13 (704,800)
        }},

        // Точка 13 (704,800)
        {13, {
            {RIGHT, 12},    // Влево → точка 12
            {LEFT, 14}    // Вправо → точка 14 (624,640)
        }},

        // Точка 14 (624,640)
        {14, {
            {DOWN, 13},    // Влево → точка 13
            {UP, 15}    // Вправо → точка 15 (655,464)
        }},

        // Точка 15 (655,464)
        {15, {
            {DOWN, 14},    // Влево → точка 14
            {UP, 16},   // Вправо → точка 16 (785,352)
            {RIGHT, 11}       // Вверх → точка 11
        }},

        // Точка 16 (785,352)
        {16, {
            {LEFT, 15},    // Влево → точка 15
            {RIGHT, 17},   // Вправо → точка 17
            {DOWN, 11}       // Вверх → точка 11
        }},

        // Точка 17 (960,336)
        {17, {
            {UP | RIGHT, 3},     // Влево → точка 3
            {RIGHT, 4},    // Вправо → точка 4
            {DOWN | LEFT, 11},      // Вверх → точка 11
            {LEFT, 16},    // Вниз → точка 16
            {DOWN, 18},  // Влево+Вниз → точка 18
            {RIGHT | DOWN, 5}     // Вправо+Вверх → точка 5
        }},

        // Точка 18 (960,476)
        {18, {
            {UP, 17},    // Влево → точка 17
            {RIGHT, 5},    // Вправо → точка 5
            {LEFT, 11}       // Вверх → точка 11
        }}
    };       // {960,476} → {689,128}, {1096,509} или {848,560}
	
	
	//----------------------------------------------
	float startPosX;
	float startPosY;

	int currentPosition;
	bool pressRight = false;
	bool pressLeft = false;
    bool pressUp = false;
    bool pressDown = false;
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
	DrawCircle(startPosX + PLANET_CENTER, startPosY + PLANET_CENTER, 42, 0XFFFFFF, false, 5.0f);
    DrawAvailableTransitions();
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
    // 1. Собираем текущий ввод и определяем новые нажатия
    bool pressedRight = (key & PAD_INPUT_RIGHT) != 0;
    bool pressedLeft = (key & PAD_INPUT_LEFT) != 0;
    bool pressedUp = (key & PAD_INPUT_UP) != 0;
    bool pressedDown = (key & PAD_INPUT_DOWN) != 0;

    // 2. Формируем битовую маску только для новых нажатий
	int inputDir = 0;
    if (pressedRight && !pressRight) inputDir |= RIGHT;
    if (pressedLeft && !pressLeft) inputDir |= LEFT;
    if (pressedUp && !pressUp) inputDir |= UP;
    if (pressedDown && !pressDown) inputDir |= DOWN;
	
    // 2. Ищем переходы для текущей позиции
    auto it = transitionMap.find(currentPosition);
    if (it != transitionMap.end()) {
        // 3. Проверяем все возможные переходы
        for (const auto& transition : it->second) {  // <- Изменили здесь
            int dir = transition.first;    // Направление
            int target = transition.second; // Целевая позиция

            if (inputDir == dir) {
                currentPosition = target;
                MoveControllerTo(line[currentPosition].x, line[currentPosition].y);
                break;
            }
        }
    }
	pressRight = pressedRight;
	pressLeft = pressedLeft;
    pressUp = pressedUp;
    pressDown = pressedDown;
	VectorI2 newPosition = line[currentPosition];
	MoveControllerTo(newPosition.x, newPosition.y);
}
void MoveControllerTo(float x, float y)
{
	startPosX = x;
	startPosY = y;
}

void DrawAvailableTransitions() {
    // Настройки отрисовки
    const int LINE_COLOR = GetColor(0, 255, 0); // Зелёный цвет
    const float LINE_THICKNESS = 2.0f;
    const int CURRENT_POS_COLOR = GetColor(255, 0, 0); // Красный для текущей позиции
    const int CURRENT_POS_RADIUS = 10;

    // 1. Рисуем текущую позицию (красный круг)
    DrawCircle(
        line[currentPosition].x+ PLANET_CENTER,
        line[currentPosition].y+ PLANET_CENTER,
        CURRENT_POS_RADIUS,
        CURRENT_POS_COLOR,
        TRUE
    );

    // 2. Получаем доступные переходы для текущей позиции
    auto it = transitionMap.find(currentPosition);
    if (it != transitionMap.end()) {
        // 3. Рисуем линии ко всем доступным точкам
        for (const auto& transition : it->second) {
            int targetPos = transition.second;

            DrawLineAA(
                static_cast<float>(line[currentPosition].x+ PLANET_CENTER),
                static_cast<float>(line[currentPosition].y+ PLANET_CENTER),
                static_cast<float>(line[targetPos].x + PLANET_CENTER),
                static_cast<float>(line[targetPos].y + PLANET_CENTER),
                LINE_COLOR,
                LINE_THICKNESS
            );

            // (Опционально) Рисуем стрелки на концах линий
            float angle = atan2f(
                (line[targetPos].y + PLANET_CENTER) - (line[currentPosition].y + PLANET_CENTER),
                (line[targetPos].x + PLANET_CENTER) - (line[currentPosition].x + PLANET_CENTER)
            );
            DrawArrow(
                (line[targetPos].x + PLANET_CENTER), (line[targetPos].y + PLANET_CENTER),
                angle, LINE_COLOR, 15.0f
            );
        }
    }
}

// Вспомогательная функция для рисования стрелок
void DrawArrow(int x, int y, float angle, int color, float size) {
    float x1 = x - size * cosf(angle + 0.3f);
    float y1 = y - size * sinf(angle + 0.3f);
    float x2 = x - size * cosf(angle - 0.3f);
    float y2 = y - size * sinf(angle - 0.3f);

    DrawLineAA(static_cast<float>(x), static_cast<float>(y), x1, y1, color, 2.0f);
    DrawLineAA(static_cast<float>(x), static_cast<float>(y), x2, y2, color, 2.0f);
}
