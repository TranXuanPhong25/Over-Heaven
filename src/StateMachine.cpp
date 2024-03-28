#include "header/StateMachine.h"

StateMachine::StateMachine() {
	p_next_state_ = NULL;
	p_current_state_ = IntroState::get();
}
StateMachine::~StateMachine() {
	p_next_state_ = NULL;
	p_current_state_ = NULL;
}
void StateMachine::setNextState(GameState* next) {
	if (p_next_state_ != ExitState::get()) {
		p_next_state_ = next;
	}
}
void StateMachine::changeState() {
	if (p_next_state_ != NULL) {
		p_current_state_->exit();
		p_next_state_->enter();

		p_current_state_ = p_next_state_;
		p_next_state_ = NULL;
	}

}
GameState* StateMachine::getCurrentState() {
	return p_current_state_;
}


