#ifndef EXITSTATE_H_
#define EXITSTATE_H_

#include "GameState.h"
class ExitState : public GameState {
public:
	static ExitState* get();
	bool enter();
	bool exit();
	void handleEvent(SDL_Event& e);
	void update();
	void render();
private:
	static ExitState s_exit_state_;
	ExitState();
};
#endif // !EXITSTATE_H_

