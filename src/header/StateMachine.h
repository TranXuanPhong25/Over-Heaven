#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
#include "IntroState.h"
#include "ExitState.h"

class StateMachine {
public:
	StateMachine();
	void setNextState(GameState* next);
	void changeState();
	GameState* getCurrentState();
	~StateMachine();
private:
	GameState* p_next_state_;
	GameState* p_current_state_;
};



#endif // !STATEMACHINE_H_
