#include "Entity.h"

Entity::Entity() {
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
	texture_ = NULL;

}
Entity::~Entity() {
	free();
}
void Entity::free() {
	if (texture_ != NULL) {
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
		rect_.x = 0;
		rect_.y = 0;
	}
}
void Entity::render(SDL_Renderer* ren, SDL_Rect* clip, SDL_Rect* stretch) {

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
bool Entity::loadTexture(SDL_Renderer* ren, const std::string& path) {
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
void Entity::setRect(const int& x, const int& y) {
	pos_.x = x;
	pos_.y = y;
	updateRect();
}
SDL_Rect Entity::getRect()const {
	return rect_;
}

SDL_Texture* Entity::getTexture() {
	return texture_;
}
void Entity::updateRect() {
	rect_.x = pos_.x;
	rect_.y = pos_.y;
}