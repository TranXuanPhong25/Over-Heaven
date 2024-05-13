#include "CreditState.hpp"
#include "IntroState.hpp"
CreditState CreditState::s_exit_state_;

CreditState::CreditState()
{
}

CreditState* CreditState::get()
{
	return &s_exit_state_;
}

bool CreditState::enter(SDL_Renderer* ren)
{
	return true;
}

bool CreditState::exit()
{
	return true;
}

void CreditState::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
		{
			StateMachine::get()->setNextState(IntroState::get());
		}
	}
}
void CreditState::update(const float& dT)
{
}

void CreditState::render(SDL_Renderer* ren)
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	SDL_RenderPresent(ren);
}

