#ifndef MAINMENUSTATE_H_
#define MAINMENUSTATE_H_
#include "GameState.h"
class MainMenuState : public GameState {
public:
	static MainMenuState* get();
	bool enter(SDL_Renderer* ren);
	bool exit();
	void handleEvent(SDL_Event& e);
	void update(const float& dT);
	void render(SDL_Renderer* ren);
private:
	static MainMenuState s_main_menu_state_;
	MainMenuState();
};

#endif // !MAINMENUSTATE_H_
