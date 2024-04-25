#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_
#include "../entities/Character.h"
#include "../levels/Levels.h"
#include "../levels/Camera.h"
#include "../core/StateMachine.h"

class PlayState : public GameState {
public:
	static PlayState* get();
	bool enter(SDL_Renderer* ren);
	bool exit();
	void handleEvent(SDL_Event& e);
	void update(const float& dT);
	void render(SDL_Renderer* ren);
	void deleteSave();
	void loadResources(SDL_Renderer* ren);
private:
	static PlayState s_play_state_;
	PlayState();
	Character player_;
	Camera cam_;
	Level level_;
};

#endif // !PLAYSTATE_H_
