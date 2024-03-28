#ifndef GAME_H_
#define GAME_H_
#include "header/Character.h"
#include "header/Timer.h"
#include "header/StateMachine.h"
class Game {
public:
	Game();
	~Game();
	void run();
private:
	bool initWindow();

	SDL_Window* window_;
	SDL_Renderer* ren_;
	StateMachine* p_game_state_;
	Character player_;
};
#endif