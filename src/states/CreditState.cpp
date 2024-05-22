#include "CreditState.hpp"
#include "IntroState.hpp"
CreditState CreditState::s_exit_state_;

CreditState::CreditState()
{
	credit_ = nullptr;
	credit_rect_ = { 0,0,0,0 };
	dest_rect_ = { 0,0,0,0 };
	esc_pressed_ = false;
	credit_texture_height_ = 0;
}

CreditState* CreditState::get()
{
	return &s_exit_state_;
}

bool CreditState::enter(SDL_Renderer* ren)
{
	credit_ = IMG_LoadTexture(ren, CREDIT_SCREEN_PATH.c_str());
	SDL_QueryTexture(credit_, NULL, NULL, &credit_rect_.w, &credit_texture_height_);

	dest_rect_.x = (SCREEN_WIDTH - credit_rect_.w) / 2;
	dest_rect_.y = 0;
	dest_rect_.w = credit_rect_.w;
	dest_rect_.h = SCREEN_HEIGHT;
	credit_rect_.h = SCREEN_HEIGHT;
	esc_pressed_ = false;
	startGetInEffect();
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
		if (e.key.keysym.sym == SDLK_ESCAPE && !esc_pressed_)
		{
			esc_pressed_ = true;
			startGetOutEffect();
		}
	}
}
void CreditState::update(const float& dT)
{
	if (credit_rect_.y > credit_texture_height_ && !esc_pressed_)
	{
		esc_pressed_ = true;
		startGetOutEffect();
	}
	else credit_rect_.y += 1;
	handleTransition(dT);
}

void CreditState::render(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, credit_, &credit_rect_, &dest_rect_);
	renderTransitionFx(ren);

}

void CreditState::finishGetOut()
{
	StateMachine::get()->setNextState(IntroState::get());
}
