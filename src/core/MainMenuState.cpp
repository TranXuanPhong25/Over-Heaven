#include "MainMenuState.h"

MainMenuState MainMenuState::s_main_menu_state_;
MainMenuState::MainMenuState() {}

MainMenuState* MainMenuState::get() {
	return &s_main_menu_state_;
}
bool MainMenuState::enter(SDL_Renderer* ren) {
	return true;
}
bool MainMenuState::exit() {
	return true;
}
void MainMenuState::handleEvent(SDL_Event& e) {}
void MainMenuState::update(const float& dT) {}
void MainMenuState::render(SDL_Renderer* ren) {}
