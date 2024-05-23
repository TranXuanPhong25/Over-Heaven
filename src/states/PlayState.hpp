#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_
#include "../entities/Character.hpp"
#include "../levels/Levels.hpp"
#include "../comp/Transition.hpp"
class PlayState : public GameState, public Transition {
public:

	static PlayState* get();
	bool enter(SDL_Renderer* ren);
	bool exit();
	void handleEvent(SDL_Event& e);
	void update(const float& dT);
	void render(SDL_Renderer* ren);
	void handleChangeLevel();
	void deleteSave();
	void finishGetOut() override;
	float loadResources(SDL_Renderer* ren, std::atomic<float>* progress);
private:

	static PlayState s_play_state_;
	PlayState();

	bool should_change_level_;
	bool loaded_player_data_;
	Character player_;
	Camera cam_;
	Level level_;
	Mix_Music* background_music_;
};

#endif // !PLAYSTATE_H_
