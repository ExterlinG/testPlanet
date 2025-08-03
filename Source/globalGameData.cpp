#include "types.h"
//#include "ship.h"
#include "globalGameData.h"
#include "DxLib.h"
#include <vector>
#include <unordered_map>

// „O„„‚„u„t„u„|„‘„u„} „s„|„€„q„p„|„Ž„~„„u „„u„‚„u„}„u„~„~„„u
std::vector<Planet> planets;
std::vector<Ship> activeShips;
extern const float SHIP_SPEED = 5.0f;
//extern int shipGraphicHandle;
int shipGraphic = -1;
//size_t LINE_SIZE = 19;
VectorI2 line[] =  { { 689, 128 }, { 848, 96 }, { 1008, 128 },
					{1136, 224},{1192, 368},{1096, 509},
					{1456, 428},{1408, 592},{1280, 720},
					{1104, 768},{944, 704},{848, 560},
					{848.5, 911},{704, 800},{624, 640},
					{655, 464},{785, 352},{960, 336},{960,476} };
//const int line_size = sizeof(line) / sizeof(line[0]);

// „M„p„„„‚„y„ˆ„p „t„€„„…„ƒ„„„y„}„„‡ „„u„‚„u„‡„€„t„€„r: [„„„u„{„…„‹„p„‘_„„€„x„y„ˆ„y„‘] = {„t„€„ƒ„„„…„„~„„u_„„€„x„y„ˆ„y„y}
const int RIGHT = 1;
const int LEFT = 2;
const int UP = 4;
const int DOWN = 8;
const std::unordered_map<int, std::vector<std::pair<int, int>>> transitionMap =
{
    // „S„€„‰„{„p 0 (689,128)
    {0, {
        {RIGHT, 1}  // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 1 (848,96)
    }},

    // „S„€„‰„{„p 1 (848,96)
    {1, {
        {LEFT, 0},   // „B„|„u„r„€ ¨ „„„€„‰„{„p 0
        {RIGHT, 2}   // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 2 (1008,128)
    }},

    // „S„€„‰„{„p 2 (1008,128)
    {2, {
        {LEFT, 1},   // „B„|„u„r„€ ¨ „„„€„‰„{„p 1
        {RIGHT, 3}   // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 3 (1136,224)
    }},

    // „S„€„‰„{„p 3 (1136,224)
    {3, {
        {UP, 2},   // „B„|„u„r„€ ¨ „„„€„‰„{„p 2
        {RIGHT, 4},   // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 4 (1192,368)
        {LEFT, 17}      // „B„r„u„‚„‡ ¨ „„„€„‰„{„p 17 (960,336)
    }},

    // „S„€„‰„{„p 4 (1192,368)
    {4, {
        {UP, 3},    // „B„|„u„r„€ ¨ „„„€„‰„{„p 3
        {DOWN, 5},   // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 5 (1096,509)
        {LEFT, 17}      // „B„r„u„‚„‡ ¨ „„„€„‰„{„p 17
    }},

    // „S„€„‰„{„p 5 (1096,509)
    {5, {
        {UP | RIGHT, 4},           // „B„|„u„r„€ ¨ „„„€„‰„{„p 4
        {LEFT, 11},         // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 11 (848,560)
        {UP, 17},     // „B„r„u„‚„‡+„B„|„u„r„€ ¨ „„„€„‰„{„p 17
        {DOWN | LEFT, 10},    // „B„~„y„x+„B„„‚„p„r„€ ¨ „„„€„‰„{„p 6 (1456,428)
        { DOWN, 9 },
        { UP | LEFT, 18 },
    }},

    // „S„€„‰„{„p 6 (1456,428)
    {6, {
        {DOWN, 7}     // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 7 (1408,592)
    }},

    // „S„€„‰„{„p 7 (1408,592)
    {7, {
        {UP, 6},     // „B„|„u„r„€ ¨ „„„€„‰„{„p 6
        {DOWN, 8}     // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 8 (1280,720)
    }},

    // „S„€„‰„{„p 8 (1280,720)
    {8, {
        {RIGHT, 7},     // „B„|„u„r„€ ¨ „„„€„‰„{„p 7
        {LEFT, 9}     // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 9 (1104,768)
    }},

    // „S„€„‰„{„p 9 (1104,768)
    {9, {
        {RIGHT, 8},     // „B„|„u„r„€ ¨ „„„€„‰„{„p 8
        {LEFT, 10},   // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 10 (944,704)
        {UP, 5}      // „B„~„y„x ¨ „„„€„‰„{„p 5
    }},

    // „S„€„‰„{„p 10 (944,704)
    {10, {
        {RIGHT, 9},     // „B„|„u„r„€ ¨ „„„€„‰„{„p 9
        {LEFT, 11},   // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 11
        {UP, 5}      // „B„~„y„x ¨ „„„€„‰„{„p 5
    }},

    // „S„€„‰„{„p 11 (848,560)
    {11, {
        {DOWN, 10},    // „B„|„u„r„€ ¨ „„„€„‰„{„p 10
        {RIGHT, 5},    // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 5
        {UP, 17},      // „B„r„u„‚„‡ ¨ „„„€„‰„{„p 17
        {UP | RIGHT, 18},     // „B„~„y„x ¨ „„„€„‰„{„p 18 (960,476)
        {UP | LEFT, 16},
        {LEFT, 15},
    }},

    // „S„€„‰„{„p 12 (848.5,911)
    {12, {

        {LEFT, 13}    // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 13 (704,800)
    }},

    // „S„€„‰„{„p 13 (704,800)
    {13, {
        {RIGHT, 12},    // „B„|„u„r„€ ¨ „„„€„‰„{„p 12
        {LEFT, 14}    // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 14 (624,640)
    }},

    // „S„€„‰„{„p 14 (624,640)
    {14, {
        {DOWN, 13},    // „B„|„u„r„€ ¨ „„„€„‰„{„p 13
        {UP, 15}    // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 15 (655,464)
    }},

    // „S„€„‰„{„p 15 (655,464)
    {15, {
        {DOWN, 14},    // „B„|„u„r„€ ¨ „„„€„‰„{„p 14
        {UP, 16},   // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 16 (785,352)
        {RIGHT, 11}       // „B„r„u„‚„‡ ¨ „„„€„‰„{„p 11
    }},

    // „S„€„‰„{„p 16 (785,352)
    {16, {
        {LEFT, 15},    // „B„|„u„r„€ ¨ „„„€„‰„{„p 15
        {RIGHT, 17},   // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 17
        {DOWN, 11}       // „B„r„u„‚„‡ ¨ „„„€„‰„{„p 11
    }},

    // „S„€„‰„{„p 17 (960,336)
    {17, {
        {UP | RIGHT, 3},     // „B„|„u„r„€ ¨ „„„€„‰„{„p 3
        {RIGHT, 4},    // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 4
        {DOWN | LEFT, 11},      // „B„r„u„‚„‡ ¨ „„„€„‰„{„p 11
        {LEFT, 16},    // „B„~„y„x ¨ „„„€„‰„{„p 16
        {DOWN, 18},  // „B„|„u„r„€+„B„~„y„x ¨ „„„€„‰„{„p 18
        {RIGHT | DOWN, 5}     // „B„„‚„p„r„€+„B„r„u„‚„‡ ¨ „„„€„‰„{„p 5
    }},

    // „S„€„‰„{„p 18 (960,476)
    {18, {
        {UP, 17},    // „B„|„u„r„€ ¨ „„„€„‰„{„p 17
        {RIGHT, 5},    // „B„„‚„p„r„€ ¨ „„„€„‰„{„p 5
        {LEFT, 11}       // „B„r„u„‚„‡ ¨ „„„€„‰„{„p 11
    }}
};       // {960,476} ¨ {689,128}, {1096,509} „y„|„y {848,560}