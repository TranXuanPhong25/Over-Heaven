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
void Entity::render(SDL_Renderer* ren, SDL_Rect* clip, SDL_FRect* stretch) {

	if (stretch != NULL) {
		SDL_RenderCopyF(ren, texture_, clip, stretch);
	}
	else {

		SDL_RenderCopyF(ren, texture_, NULL, &(rect_));
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
		int w, h;
		SDL_QueryTexture(texture_, NULL, NULL, &w, &h);
		rect_.w = w;
		rect_.h = h;

	}
	return texture_ == NULL;
}
void Entity::setRect(const float& x, const float& y, Camera& cam) {
	pos_.x = x;
	pos_.y = y;
	updateRect(cam);
}
SDL_FRect Entity::getRect() const {
	return rect_;
}



SDL_Texture* Entity::getTexture() {
	return texture_;
}
void Entity::updateRect(Camera& cam) {
	rect_.x = pos_.x - cam.getPos().x;
	rect_.y = pos_.y - cam.getPos().y;

}

Vector2D Entity::getPos() const
{
	return pos_;
}
