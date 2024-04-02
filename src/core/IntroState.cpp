#include "IntroState.h"
IntroState IntroState::s_intro_state_;
IntroState::IntroState() {}
IntroState* IntroState::get() {
	return &s_intro_state_;
}
bool IntroState::enter(SDL_Renderer* ren) {

	bool success = true;
	return success;
}
bool IntroState::exit() {
	bool success = true;
	return success;
}
void IntroState::handleEvent(SDL_Event& e) {
	if (e.key.keysym.sym == SDLK_r) {
		StateMachine::get()->setNextState(PlayState::get());
	}
	//do stuff
}
void IntroState::update(const float& dT) {
	//do stuff
}
void IntroState::render(SDL_Renderer* ren) {
	//do stuff
}