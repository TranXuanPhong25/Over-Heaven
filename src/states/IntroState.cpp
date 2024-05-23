#include "IntroState.hpp"
IntroState IntroState::s_intro_state_;
IntroState::IntroState() {
	start_time_ = SDL_GetTicks();
}
IntroState* IntroState::get() {
	return &s_intro_state_;
}
bool IntroState::enter(SDL_Renderer* ren) {
	bool success = true;
	startGetInEffect();
	intro_ = IMG_LoadTexture(ren, INTRO_SCREEN_PATH.c_str());
	start_time_ = SDL_GetTicks();
	return success;
}
bool IntroState::exit() {
	SDL_DestroyTexture(intro_);
	
	bool success = true;
	return success;
}
void IntroState::handleEvent(SDL_Event& e) {}
void IntroState::update(const float& dT) {
	if (SDL_GetTicks() - start_time_ >= INTRO_DURATION) {
		startGetOutEffect();
	}
	handleTransition(dT);
}
void IntroState::render(SDL_Renderer* ren) {
	SDL_RenderCopy(ren,intro_,NULL,NULL);
	renderTransitionFx(ren);
}

void IntroState::finishGetOut()
{
	StateMachine::get()->setNextState(MainMenuState::get());
}

void IntroState::finishGetIn()
{
	start_time_ = SDL_GetTicks();
	
}
