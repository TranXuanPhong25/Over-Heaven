#ifndef EXITSTATE_H_
#define EXITSTATE_H_

#include "GameState.h"
class ExitState : public GameState {
public:
	static ExitState* get();
	bool enter(SDL_Renderer* ren);
	bool exit();
	void handleEvent(SDL_Event& e);
	void update(const float& dT);
	void render(SDL_Renderer* ren);
private:
	static ExitState s_exit_state_;
	ExitState();
};
#endif // !EXITSTATE_H_

