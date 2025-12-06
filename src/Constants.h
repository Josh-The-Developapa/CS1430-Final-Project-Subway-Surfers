#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <map>
#include <vector>

// Screen dimensions
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

// Game physics
const float GRAVITY = 0.6f;
const float JUMP_VELOCITY = -12.0f;
const float BASE_SCROLL_SPEED = 3.0f;

// Player constants
const int PLAYER_Y_GROUND = 450;
const int PLAYER_WIDTH = 40;
const int PLAYER_HEIGHT = 50;

// Lane positions
const int LANE_POSITIONS[] = {225, 475, 725};
const int NUM_LANES = 3;
const int LANE_SPACING = 250;

// Game states
const int STATE_START = 0;
const int STATE_PLAYING = 1;
const int STATE_PAUSED = 2;
const int STATE_GAME_OVER = 3;

// 5x7 Bitmap Font
extern std::map<char, std::vector<int>> FONT_5X7;

void initializeFont();

#endif