#include "Button.hpp"
Button::Button(){
    texture_ = NULL;
    alpha_ = MISFOCUSING;
}
Button::~Button()
{
	SDL_DestroyTexture(texture_);
	texture_ = NULL;
	alpha_ = MISFOCUSING;

}
void Button::render(SDL_Renderer* ren)
{
	SDL_SetTextureAlphaMod(texture_, alpha_);
	SDL_RenderCopy(ren, texture_, NULL, &rect_);
}
void Button::loadTexture(SDL_Renderer* ren, const std::string& path)
{
	texture_ = IMG_LoadTexture(ren, path.c_str());
	SDL_QueryTexture(texture_, NULL, NULL, &rect_.w, &rect_.h);
	rect_.x = (SCREEN_WIDTH - rect_.w) / 2;
}
SDL_Texture *Button::getTexture()
{
    return texture_;
}
void Button::setRectY(const int &y)
{
	rect_.y = y;
}
SDL_Rect Button::getRect() const
{
    return rect_;
}
void Button::setType(Type type)
{
	type_ = type;
}
void Button::reduceAlpha()
{
	alpha_ = Transition::easeIn(alpha_, MISFOCUSING, 0.25f);
}
void Button::enhanceAlpha()
{
	alpha_ = Transition::easeOut(alpha_, FOCUSING, 0.05f);
}
Button::Type Button::getType() const
{
	return type_;
}





