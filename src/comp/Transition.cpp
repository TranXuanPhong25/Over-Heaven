#include "Transition.hpp"
Transition::Transition()
{
	overlay_alpha_ = 1.0f;
	is_on_enter_ = false;
	is_on_exit_ = false;
}
void Transition::getIn(const float &dT)
{
	overlay_alpha_ = lerp(overlay_alpha_, -0.1f, dT * 3);
	if (overlay_alpha_ <= 0.0f)
	{
		overlay_alpha_ = 0.0f;
		is_on_enter_ = false;
		finishGetIn();
	}
}
void Transition::getOut(const float &dT)
{
	overlay_alpha_ += dT / 0.4f;
	if (overlay_alpha_ > 1.0f)
	{
		overlay_alpha_ = 1.0f;
		is_on_exit_ = false;
		finishGetOut();
	}
}
void Transition::finishGetIn()
{
}
void Transition::finishGetOut()
{
}
void Transition::handleTransition(const float &dT)
{
	if (is_on_enter_)
	{
		getIn(dT);
	}
	if (is_on_exit_)
	{
		getOut(dT);
	}
}
void Transition::renderTransitionFx(SDL_Renderer *ren)
{
	if (is_on_enter_ || is_on_exit_ || overlay_alpha_ == 1)
	{
		SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(ren, 0, 0, 0, static_cast<Uint8>(overlay_alpha_ * 255));
		SDL_RenderFillRect(ren, &ENTIRE_SCREEN);
	}
}

void Transition::startGetInEffect()
{
	is_on_enter_ = true;
	is_on_exit_ = false;
}

void Transition::startGetOutEffect()
{
	is_on_enter_ = false;
	is_on_exit_ = true;
}
