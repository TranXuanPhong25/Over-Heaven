#ifndef GAME_H_
#define GAME_H_
#include "../comp/Timer.h"
#include "StateMachine.h"
#include "IntroState.h"

class Game {
public:
	Game();
	~Game();
	void run();
private:
	bool initWindow();
	SDL_Renderer* ren_;
	SDL_Window* window_;
	StateMachine* state_machine_;
};
#endif