#ifndef CONSTANT_H_
#define CONSTANT_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <atomic>
#include <filesystem>

using std::max;
using std::min;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const SDL_Rect ENTIRE_SCREEN = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

const float TARGET_TIMESTEP = 1000 / 60;

const int MAX_TILES = 155;
const int TILE_SIZE = 60;


const std::string PLAYER_DATA_PATH = "assets/player/player_data.json";
const std::string IDLE_ANIMATION_KEY = "idle";
const std::string JUMP_ANIMATION_KEY = "jump";
const std::string RUN_ANIMATION_KEY = "run";
const std::string FRAME_SIZE_KEY = "frameSize";
const std::string X_KEY = "x";
const std::string Y_KEY = "y";
const std::string WIDTH_KEY = "w";
const std::string HEIGHT_KEY = "h";
const std::string SIZE_KEY = "size";
const std::string IMAGES_PATH_KEY = "images";
const std::string PLAYER_SPRITESHEET_DATA_PATH_KEY = "spriteSheetData";

const int JUMP_HEIGHT = 1200;
const int MAX_FALL_SPEED = 2000;
const int MAX_JUMP_BUFFER = 3;
const int MAX_COYOTE_TIME = 6;

const int GRAVITY = 600;
const int DEFAULT_SPEED = 400;
const int FLOATY_FALL_VEL = 80;
const float FALL_SCALAR = 10;
const float FLOATY_SCALAR = 4;
const float MIN_SCALAR = 6;
const float REDUCE_SCALAR = 1;
const float FRICTION_SCALAR = 5;
const float DEFAULT_SCALAR = 15;
const int MAX_RUN_SPEED = 810;
const int RUN_SPEED = 30;
const int LEFT = -1;
const int RIGHT = 1;
const int UP = -1;
const int DOWN = 1;

const float TOTAL_LOADING_STEP = 10.0f;
const float PLAYER_DEFAULT_POS[4][2] = {
	{0,0},
	{ 180, 300 },
	{120, 5500 },
	{ 60, 60 }
};
const char SAVE_PATH[] = "save/save_game.xml";

const std::string LEVEL_PATH[4] = {
	"",
	"assets/level/level1/",
	"assets/level/level2/",
	"assets/level/level3/"
};
const std::string MAP_NAME[4] = {
	"",
	"map1.csv",
	"map2.csv",
	"map3.csv"
};
const std::string BACKGROUND_PATH = "background.png";
const std::string FARGROUND_PATH = "farground.png";
const std::string FOREGROUND_PATH = "foreground.png";
const std::string FACEGROUND_PATH = "faceground.png";
const std::string NEARGROUND_PATH = "nearground.png";

const Uint8 FOCUSING = 255;
const Uint8 MISFOCUSING = 90;
const int NUMS_OF_BUTTONS = 3;
const std::string MENU_BUTTON_TEXTURE_PATHS[3] = {
	"assets/menu/newGame.png",
	"assets/menu/continue.png",
	"assets/menu/quitGame.png",
};
const std::string MENU_BACKGROUND_TEXTURE_PATH = "assets/menu/bg_.png";

#endif // !CONSTANT_H_