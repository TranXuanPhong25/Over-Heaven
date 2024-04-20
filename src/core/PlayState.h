#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_
#include "GameState.h"
#include "../entities/Character.h"
#include "../levels/Levels.h"
#include "../levels/Camera.h"
class PlayState : public GameState {
public:
	static PlayState* get();
	bool enter(SDL_Renderer* ren);
	bool exit();
	void handleEvent(SDL_Event& e);
	void update(const float& dT);
	void render(SDL_Renderer* ren);
	void deleteSave();



private:
	static PlayState s_play_state_;
	PlayState();
	Character player_;
	Camera cam_;
	Level level_;
};

#endif // !PLAYSTATE_H_
