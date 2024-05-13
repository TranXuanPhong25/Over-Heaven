#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
#include "../states/ExitState.hpp"

class StateMachine {
public:
	static StateMachine* get();
	void setInitialState(GameState* initialState);
	void setNextState(GameState* next);
	void changeState(SDL_Renderer* ren);
	GameState* getCurrentState();
private:
	StateMachine();
	static StateMachine s_state_machine_;

	GameState* p_next_state_;
	GameState* p_current_state_;
};



#endif // !STATEMACHINE_H_
