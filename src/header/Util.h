//#pragma once
#ifndef UTIL_H_
#define UTIL_H_

#include "Constants.h"

bool initWindow(SDL_Window** window, SDL_Renderer** ren);
void closeWindow(SDL_Window* window, SDL_Renderer* ren, TTF_Font* font);
#endif // !UTIL_H_