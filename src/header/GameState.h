#ifndef GAMESTATE_H_
#define GAMESTATE_H_
#include "Constants.h"

class GameState {
public:
	virtual bool enter() = 0;
	virtual bool exit() = 0;

	virtual void handleEvent(SDL_Event& e) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual ~GameState() {};
};
#endif // !GAMESTATE_H_
