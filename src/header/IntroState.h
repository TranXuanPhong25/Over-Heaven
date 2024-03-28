#ifndef INTROSTATE_H_
#define INTROSTATE_H_
#include "GameState.h"

class IntroState :public GameState {
public:
	static IntroState* get();
	bool enter();
	bool exit();
	void handleEvent(SDL_Event& e);
	void update();
	void render();

private:
	static IntroState s_intro_state_;
	IntroState();
	//another stuff
};
#endif // !INTROSTATE_H_