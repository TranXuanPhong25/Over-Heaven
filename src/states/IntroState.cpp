#include "IntroState.hpp"
IntroState IntroState::s_intro_state_;
IntroState::IntroState() {
	start_time_ = 0;
}
IntroState* IntroState::get() {
	return &s_intro_state_;
}
bool IntroState::enter(SDL_Renderer* ren) {
	bool success = true;
	start_time_ = SDL_GetTicks();
	return success;
}
bool IntroState::exit() {
	bool success = true;
	return success;
}
void IntroState::handleEvent(SDL_Event& e) {

	//do stuff
}
void IntroState::update(const float& dT) {
	if (SDL_GetTicks() - start_time_ >= 500) {

		StateMachine::get()->setNextState(MainMenuState::get());
	}

	//do stuff
}
void IntroState::render(SDL_Renderer* ren) {
	//do stuff
}