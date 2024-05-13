#ifndef MAINMENUSTATE_H_
#define MAINMENUSTATE_H_

#include "LoadingState.hpp"
#include "PlayState.hpp"
#include "../thirdParty/ffmpeg/VideoStreamer.hpp"

class MenuButton {
public:
	enum ButtonType {
		NEWGAME,
		CONTINUE,
		//OPTIONS,
		QUIT
	};
	~MenuButton();
	void render(SDL_Renderer* ren);
	void loadTexture(SDL_Renderer* ren, const std::string& path);
	void setRectY(const int& y);
	void setType(ButtonType type);
	void reduceAlpha();
	void enhanceAlpha();
	ButtonType getType() const;
private:
	ButtonType type_;
	SDL_Texture* texture_;
	SDL_Rect rect_;
	bool is_focused_;
	Uint8 alpha_;
};
//single-level menu
class MainMenuState : public GameState, public Transition
{
public:
	enum State {
		MAINMENU,
		OPTIONS
	};
	static MainMenuState* get();
	bool enter(SDL_Renderer* ren);
	bool exit();
	void handleFocusUp();
	void handleFocusDown();
	void handleEnter();
	void handleEvent(SDL_Event& e);
	void update(const float& dT);
	void render(SDL_Renderer* ren);
	void finishGetOut() override;
private:
	static MainMenuState s_main_menu_state_;
	MainMenuState();
	~MainMenuState();

	VideoStreamer* p_video_streamer_;

	MenuButton buttons_[NUMS_OF_BUTTONS];
	MenuButton::ButtonType current_button_;

	SDL_Texture* bg_;
};

#endif // !MAINMENUSTATE_H_
