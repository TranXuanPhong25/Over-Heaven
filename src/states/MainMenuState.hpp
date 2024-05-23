#ifndef MAINMENUSTATE_H_
#define MAINMENUSTATE_H_

#include "LoadingState.hpp"
#include "PlayState.hpp"
#include "../thirdParty/ffmpeg/VideoStreamer.hpp"
#include "../comp/Button.hpp"
class MainMenuState : public GameState, public Transition
{
public:
	enum State {
		MAINMENU=0,
		OPTIONS=4
	};
	static MainMenuState* get();
	bool enter(SDL_Renderer* ren);
	bool exit();
	void handleEnter();
	void handleEvent(SDL_Event& e);
	void update(const float& dT);
	void render(SDL_Renderer* ren);

	void handleFocusDown();
	void handleFocusUp();
	void handleAdjustVolume();
	void finishGetOut() override;
private:
	static MainMenuState s_main_menu_state_;
	MainMenuState();
	~MainMenuState();
	State state_;
	int current_num_buttons_;
	Button buttons_[Button::NUM_BUTTONS];
	Button::Type current_button_;
	bool continue_available_;

	Mix_Music* background_music_;
	VideoStreamer* p_video_streamer_;
	SDL_Texture* bg_;
};

#endif // !MAINMENUSTATE_H_
