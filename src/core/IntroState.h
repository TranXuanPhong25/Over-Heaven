#ifndef INTROSTATE_H_
#define INTROSTATE_H_
#include "PlayState.h"
#include "StateMachine.h"

class IntroState :public GameState {
public:
	static IntroState* get();
	bool enter(SDL_Renderer* ren);
	bool exit();
	void handleEvent(SDL_Event& e);
	void update(const float& dT);
	void render(SDL_Renderer* ren);

private:
	static IntroState s_intro_state_;
	IntroState();
	//another stuff
};
#endif // !INTROSTATE_H_