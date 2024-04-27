#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_
#include "../entities/Character.h"
#include "../levels/Levels.h"
#include "../levels/Camera.h"
#include "../core/StateMachine.h"

class PlayState : public GameState {
public:
	static PlayState* get();
	void getOut();
	void getIn();
	bool enter(SDL_Renderer* ren);
	bool exit();
	void handleEvent(SDL_Event& e);
	void update(const float& dT);
	void render(SDL_Renderer* ren);
	void deleteSave();
	float loadResources(SDL_Renderer* ren, std::atomic<float>* progress);
private:
	static PlayState s_play_state_;
	PlayState();
	bool is_get_in_;
	SDL_Surface* get_in_fx_;
	Character player_;
	Camera cam_;
	Level level_;
	std::atomic<bool> loaded_player_spritesheet_;
};

#endif // !PLAYSTATE_H_
