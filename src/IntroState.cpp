#include "header/IntroState.h"
IntroState IntroState::s_intro_state_;
IntroState::IntroState() {}
IntroState* IntroState::get() {
	return &s_intro_state_;
}
bool IntroState::enter() {

	bool success = true;
	return success;
}
bool IntroState::exit() {
	bool success = true;
	return success;
}
void IntroState::handleEvent(SDL_Event& e) {
	//do stuff
}
void IntroState::update() {
	//do stuff
}
void IntroState::render() {
	//do stuff
}