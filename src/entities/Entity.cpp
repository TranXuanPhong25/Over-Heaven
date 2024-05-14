#include "Entity.hpp"

Entity::Entity()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
	texture_ = NULL;
	pos_.x = 0;
	pos_.y = 0;
	width_offset_ = 0;
	height_offset_ = 0;
	current_frame_clip_ = std::make_pair(0, 0);
	width_ = 0;
	height_ = 0;
	flip_ = false;
	frame_duration_ = 0;
	animation_time_ = 0;
	
}
Entity::~Entity()
{
	free();
	frames_clips_.clear();
}
void Entity::free()
{
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
	}
}
void Entity::render(SDL_Renderer *ren)
{
	SDL_RenderCopyEx(ren,
					 texture_,
					 &frames_clips_[current_frame_clip_.first][current_frame_clip_.second],
					 &rect_,
					 0,
					 NULL,
					 flip_ ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
	);
}
bool Entity::loadTexture(SDL_Renderer *ren)
{
	free();
	texture_ = IMG_LoadTexture(ren, sprite_sheet_path_.c_str());
	if (texture_ == NULL)
	{
		std::cout << IMG_GetError() << std::endl;
	}
	return texture_ == NULL;
}

SDL_Rect Entity::getRect() const
{
	return rect_;
}

SDL_Texture *Entity::getTexture()
{
	return texture_;
}
void Entity::updateRect(Camera &cam)
{
	rect_.x = pos_.x - cam.getPos().x - width_offset_;
	rect_.y = pos_.y - cam.getPos().y - height_offset_;
}

Vector2D Entity::getPos() const
{
	return pos_;
}
