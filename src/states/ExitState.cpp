#include "ExitState.h"

ExitState ExitState::s_exit_state_;
ExitState::ExitState() {}

ExitState* ExitState::get() {
	return &s_exit_state_;
}
bool ExitState::enter(SDL_Renderer* ren) {
	return true;
}
bool ExitState::exit() {
	return true;
}
void ExitState::handleEvent(SDL_Event& e) {}
void ExitState::update(const float& dT) {}
void ExitState::render(SDL_Renderer* ren) {}
