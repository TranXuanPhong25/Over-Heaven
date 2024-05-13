#ifndef GAMESTATE_H_
#define GAMESTATE_H_
#include "../core/Constants.hpp"

class GameState {
public:
	virtual bool enter(SDL_Renderer* ren) = 0;
	virtual bool exit() = 0;

	virtual void handleEvent(SDL_Event& e) = 0;
	virtual void update(const float& dT) = 0;
	virtual void render(SDL_Renderer* ren) = 0;
	virtual ~GameState() {};
};
#endif // !GAMESTATE_H_