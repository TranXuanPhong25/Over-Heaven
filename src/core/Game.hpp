#ifndef GAME_H_
#define GAME_H_
#include "StateMachine.hpp"
#include "../states/IntroState.hpp"

class Game {
public:
	Game();
	~Game();
	void run();
	void launchGameLoop(SDL_Event& e);
private:
	bool initWindow();
	SDL_Renderer* p_ren_;
	SDL_Window* p_window_;
	StateMachine* p_state_machine_;

	Uint64 preFrame;
	Uint64 curFrame;
	float time_step_;
	float time_step_seconds_;
};
#endif