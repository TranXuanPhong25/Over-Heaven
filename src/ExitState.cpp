#include "header/ExitState.h"

ExitState ExitState::s_exit_state_;
ExitState::ExitState() {}

ExitState* ExitState::get() {
	return &s_exit_state_;
}
bool ExitState::enter() {
	return true;
}
bool ExitState::exit() {
	return true;
}
void ExitState::handleEvent(SDL_Event& e) {}
void ExitState::update() {}
void ExitState::render() {}
