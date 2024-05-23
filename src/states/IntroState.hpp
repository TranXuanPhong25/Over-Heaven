#ifndef INTROSTATE_H_
#define INTROSTATE_H_
#include "MainMenuState.hpp"
#include "../core/StateMachine.hpp"

class IntroState :public GameState,public Transition {
public:
	static IntroState* get();
	bool enter(SDL_Renderer* ren);
	bool exit();
	void handleEvent(SDL_Event& e);
	void update(const float& dT);
	void render(SDL_Renderer* ren);
	void finishGetOut() override;
	void finishGetIn() override;
private:
	static IntroState s_intro_state_;
	IntroState();
	Uint32 start_time_;
	SDL_Texture * intro_;
	//another stuff
};
#endif // !INTROSTATE_H_