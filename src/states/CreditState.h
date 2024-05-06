#ifndef CREDITSTATE_H_
#define CREDITSTATE_H_
#include "../core/StateMachine.h"
class IntroState;
class CreditState : public GameState{
public:
	static CreditState* get();
	bool enter(SDL_Renderer* ren);
	bool exit();
	void handleEvent(SDL_Event& e);
	void update(const float& dT);
	void render(SDL_Renderer* ren);
private:
	static CreditState s_exit_state_;
	CreditState();
};

#endif // !CREDITSTATE_H_