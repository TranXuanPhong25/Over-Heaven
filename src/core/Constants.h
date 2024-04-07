#ifndef CONSTANT_H_
#define CONSTANT_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <string>
#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>
//1080p resolution
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const float TARGET_TIMESTEP = 1000 / 60;
const int MAX_TILES = 200;
const int TILE_SIZE = 60;

const std::string NUNU_TEXTURE_PATH_64X91 = "assets/char/nunu.png";
const int JUMP_HEIGHT = 1800;
const int MAX_FALL_SPEED = 2400;
const int MAX_JUMP_BUFFER = 3;
const int MAX_COYOTE_TIME = 5;
const int MAX_DASH_FRAMES = 6;
const int DASH_FORCE = 5;
const float DASH_COOLDOWN = 0.5f;
const int GRAVITY = 1400;
const int DEFAULT_SPEED = 600;
const int FLOATY_FALL_VEL = 90;
const float FALL_SCALAR = 5;
const float FLOATY_SCALAR = 1.5;
const float MIN_SCALAR = 1.6;
const float REDUCE_SCALAR = 0.4;
const float FRICTION_SCALAR = 1.2;
const float DEFAULT_SCALAR = 7;
const int MAX_RUN_SPEED = 810;
const int RUN_SPEED = 30;
const int LEFT = -1;
const int RIGHT = 1;
const std::string MAP_PATH = "map/";

const SDL_Rect EMPTY_TILE_CLIP = { 0, 0, TILE_SIZE, TILE_SIZE };
const SDL_Rect GROUND_TILE_CLIP = { TILE_SIZE, 0, TILE_SIZE, TILE_SIZE };


#endif // !CONSTANT_H_
