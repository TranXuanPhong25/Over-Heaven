#include "header/BaseObject.h"

BaseObject::BaseObject() {
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
	texture_ = NULL;

}
BaseObject::~BaseObject() {
	free();
}
void BaseObject::free() {
	if (texture_ != NULL) {
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
		rect_.x = 0;
		rect_.y = 0;
	}
}
void BaseObject::render(SDL_Renderer* ren, SDL_Rect* clip, SDL_Rect* stretch) {

	if (stretch != NULL) {
		if (clip != NULL) {
			SDL_RenderCopy(ren, texture_, clip, stretch);
		}
		else {
			SDL_RenderCopy(ren, texture_, NULL, stretch);
		}
	}
	else {
		SDL_RenderCopy(ren, texture_, NULL, &(rect_));
	}
}
bool BaseObject::loadTexture(SDL_Renderer* ren, const std::string& path) {
	free();
	texture_ = IMG_LoadTexture(ren, path.c_str());
	if (texture_ == NULL)
	{
		std::cout << IMG_GetError() << std::endl;
	}
	else {
		SDL_QueryTexture(texture_, NULL, NULL, &rect_.w, &rect_.h);
	}
	return texture_ == NULL;
}
void BaseObject::setRect(const int& x, const int& y) {
	rect_.x = x;
	rect_.y = y;
}
SDL_Rect BaseObject::getRect() const {
	return rect_;
}

SDL_Texture* BaseObject::getTexture() {
	return texture_;
}