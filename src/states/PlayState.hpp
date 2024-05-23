#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_
#include "../entities/Character.hpp"
#include "../levels/Levels.hpp"
#include "../comp/Transition.hpp"
#include "../comp/Button.hpp"
class PlayState : public GameState, public Transition {
public:
	enum Channel
	{
		NAVIGATE,
		SELECT,
		ADJUST
	};
	enum State {
		PAUSE=0,
		PLAY=1,
		OPTION=3
	};
	enum PauseMenuButton {
		CONTINUE,
		OPTIONS,
		EXIT,
		VOLUME_SLIDER,
		SLIDER,
		BACK
	};
	
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
	void handleNavigateUp();
	void handleNavigateDown();
	void handleEnter();
	void handleAdjustVolume(int direction);
	void handleEsc();
private:
	static PlayState s_play_state_;
	PlayState();

	bool should_change_level_;
	bool loaded_player_data_;
	Character player_;
	Camera cam_;
	Level level_;

	State state_;
	
	Button buttons_[NUM_OF_PAUSE_MENU_BUTTONS];
	PauseMenuButton current_button_;
	SDL_Texture* pause_menu_bg_;
	Mix_Music* background_music_;
	Mix_Chunk* navigate_sound_;
	Mix_Chunk* select_sound_;
	Mix_Chunk* adjust_sound_;
};

#endif // !PLAYSTATE_H_
