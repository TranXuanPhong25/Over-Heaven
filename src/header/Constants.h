#ifndef CONSTANT_H_
#define CONSTANT_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <string>
#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cmath>
#include <WinUser.h>

const int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN) / 2;
const int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN) / 2;
//const int SCREEN_HEIGHT = 64 * 10;
//const int SCREEN_WIDTH = 64 * 20;
const SDL_Color WHITE = { 255,255,255 };
const SDL_Color BLACK = { 0,0,0 };

const char AIR_TILETYPE = '0';
const char DIRT_TILETYPE = '2';
const char DIRTGRASS_TILETYPE = '3';
const char COIN_TILETYPE = '4';
const char FLAG_TILETYPE = '5';

const std::string NUNU_TEXTURE_PATH_64X91 = "assets/char/nunu.png";
const int GRAVITY = 6400;
const int MAX_RUN_SPEED = 810;
const int RUN_SPEED = 20;
const int LEFT = -1;
const int RIGHT = 1;
const std::string MAP_PATH = "map/";
const int TILE_SIZE = 32;
const int INIT_POS_X = TILE_SIZE * 3;
const int INIT_POS_Y = SCREEN_HEIGHT - TILE_SIZE * 6;
const int MAX_X_MAP = 801;
const int MAX_Y_MAP = 10;



#endif // !CONSTANT_H_
