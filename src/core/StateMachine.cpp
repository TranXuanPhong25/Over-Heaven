#include "StateMachine.hpp"
StateMachine::StateMachine() {
	p_current_state_ = NULL;
	p_next_state_ = NULL;
}
StateMachine StateMachine::s_state_machine_;
void StateMachine::setInitialState(GameState* initialState) {
	p_current_state_ = initialState;
}
StateMachine* StateMachine::get() {
	return &s_state_machine_;
}
void StateMachine::setNextState(GameState* next) {
	if (p_next_state_ != ExitState::get()) {
		p_next_state_ = next;
	}
}
void StateMachine::changeState(SDL_Renderer* ren) {
	if (p_next_state_ != NULL) {
		p_current_state_->exit();
		p_next_state_->enter(ren);

		p_current_state_ = p_next_state_;
		p_next_state_ = NULL;
	}
}
GameState* StateMachine::getCurrentState() {
	return p_current_state_;
}


