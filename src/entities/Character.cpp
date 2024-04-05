#include "Character.h"
Character::Character() {
	speed_ = 540;
	vel_ = { 0,0 };
	state_ = IDLE_RIGHT;
	spacekey_pressed_ = false;
	/*accelerator_ = 0;*/
	on_ground_ = false;
	dir_left_ = 0;
	dir_right_ = 0;
	gravity_scalar_ = 2;
	jump_count_ = 1;

	dashing_ = false;
	dash_counter_ = 1;
	dashing_frame_ = 0;
	dash_dir_ = 0;
	dash_cooldown_ = 0;

	wall_collided_ = false;
	collide_x_ = false;
	coyote_time_ = 0;
	jump_buffer_ = 0;
}
Character::~Character() {
	free();
}

void Character::handleInput(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {

		if (e.key.keysym.sym == SDLK_SPACE) {
			spacekey_pressed_ = true;

		}
		if ((e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)) {

			dir_left_ = 1;
			if (state_ < JUMP_LEFT) {
				state_ = MOVE_LEFT;
			}

			if (state_ == JUMP_RIGHT) {
				state_ = JUMP_LEFT;
			}
		}
		if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)) {
			dir_right_ = 1;
			if (state_ < JUMP_LEFT) {
				state_ = MOVE_RIGHT;
			}

			if (state_ == JUMP_LEFT) {
				state_ = JUMP_RIGHT;
			}
		}
		//dash
		if (e.key.keysym.sym == SDLK_LSHIFT && e.key.repeat == 0) {

			if (dash_counter_ && !dash_cooldown_) {
				std::cout << dash_counter_ << " " << dash_cooldown_ << std::endl;

				if (state_ == MOVE_LEFT || state_ == IDLE_LEFT || state_ == JUMP_LEFT) {
					state_ = DASH_LEFT;
					dash_dir_ = LEFT;
				}
				else if (state_ == MOVE_RIGHT || state_ == IDLE_RIGHT || state_ == JUMP_RIGHT) {
					state_ = DASH_RIGHT;
					dash_dir_ = RIGHT;
				}

				dashing_ = true;
				if (dash_counter_)dash_counter_--;
			}
		}
	}
	if (e.type == SDL_KEYUP) {
		if (e.key.keysym.sym == SDLK_SPACE) {
			spacekey_pressed_ = false;
		}
		if ((e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)) {
			if (state_ < JUMP_LEFT) {
				state_ = IDLE_LEFT;
			}
			dir_left_ = 0;
		}
		if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)) {
			dir_right_ = 0;
			if (state_ < JUMP_LEFT) {
				state_ = IDLE_RIGHT;
			}
		}
	}



}

bool Character::shoudSlowDown() const {
	//return (state_ == MOVE_LEFT && accelerator_ < 0 && vel_.x == 0)
	//	|| (state_ == MOVE_RIGHT && accelerator_ > 0 && vel_.x == 0);
	return true;
}
Vector2D Character::getVel() const {
	return vel_;
}
bool Character::checkCollision(const SDL_Rect& a, const SDL_Rect& s) {
	return  a.x < s.x + s.w &&
		a.x + a.w > s.x &&
		a.y < s.y + s.h &&
		a.y + a.h > s.y;
}
void Character::update(Level& level, Camera& cam, const float& dT) {

	if (dashing_) {
		dash(dT);
	}
	else {
		moveX(dT);
	}
	CollideX(level);
	moveY(dT);
	CollideY(level);
}

void Character::moveX(const float& dT) {
	vel_.x = (dir_right_ - dir_left_) * speed_ / RUN_SPEED * 10;
	pos_.x += vel_.x * dT;
}
void Character::CollideX(Level& level) {
	int tileX = pos_.x / TILE_SIZE;
	int tileY = pos_.y / TILE_SIZE;
	int startX = max(0, tileX - 1);
	int startY = max(0, tileY - 1);
	int endX = min(level.getWidth(), (pos_.x + rect_.w) / TILE_SIZE + 1);
	int endY = min(level.getHeight(), (pos_.y + rect_.h) / TILE_SIZE + 1);
	wall_collided_ = false;
	collide_x_ = false;
	for (int x = startX; x <= endX; x++) {
		for (int y = startY; y <= endY; y++)
		{
			SDL_Rect tileRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
			if (checkCollision({ (int)pos_.x ,(int)pos_.y ,rect_.w,rect_.h }, tileRect) && level.getTile(x, y)->getType() != Tile::Type::EMPTY) {
				collide_x_ = true;
				if (!on_ground_) wall_collided_ = true;
				if (vel_.x > 0) {
					pos_.x = tileRect.x - rect_.w;
				}
				else if (vel_.x < 0) {
					pos_.x = tileRect.x + tileRect.w;
				}
			}
		}
	}

}

//---------------dash---------------***********************
void Character::dash(const float& dT) {
	if (dashing_frame_ < MAX_DASH_FRAMES) {
		vel_.x = dash_dir_ * speed_ / RUN_SPEED * 20;
		pos_.x += vel_.x * dT;
		dashing_frame_++;
		vel_.y = 0;
	}
	else {
		dashing_frame_ = 0;
		dashing_ = false;
		dash_cooldown_ = 25;
		if (state_ == DASH_LEFT) state_ = IDLE_LEFT;
		if (state_ == DASH_RIGHT) state_ = IDLE_RIGHT;
	}

}
//---------------jump-**********************************************
void Character::jump(const float& dT) {
	if (state_ == MOVE_LEFT || state_ == IDLE_LEFT || state_ == DASH_LEFT) state_ = JUMP_LEFT;
	if (state_ == MOVE_RIGHT || state_ == IDLE_RIGHT || state_ == DASH_LEFT) state_ = JUMP_RIGHT;
	on_ground_ = false;
	vel_.y = -JUMP_HEIGHT;
	coyote_time_ = 0;
	gravity_scalar_ = 5;
}
void Character::applyGravity(const float& dT) {
	if (vel_.y > 90) {
		gravity_scalar_ = 4;

	}
	else  if (vel_.y > -90) {
		gravity_scalar_ = 1.3;
	}
	else if (spacekey_pressed_) {
		gravity_scalar_ -= (gravity_scalar_ > 1.55) ? 0.25 : 0;
	}
	if (wall_collided_ && vel_.y > 0) {
		gravity_scalar_ = 0.8;
	}
	if (vel_.y > MAX_FALL_SPEED * 1.5) {
		vel_.y = MAX_FALL_SPEED * 1.5;
	}
	else {

		vel_.y += GRAVITY * gravity_scalar_ * dT;
	}
}
void Character::moveY(const float& dT) {
	if (spacekey_pressed_ || jump_buffer_) {
		if (on_ground_ || coyote_time_) {
			jump(dT);
		}
		if (spacekey_pressed_) jump_buffer_ = MAX_JUMP_BUFFER;
	}

	if (jump_buffer_) {
		jump_buffer_--;
	}
	//gravity
	if (!on_ground_ && !dashing_) {
		if (coyote_time_) coyote_time_--;
		applyGravity(dT);
	}
	else if (on_ground_) {
		dash_counter_ = 1;
		coyote_time_ = MAX_COYOTE_TIME;


		vel_.y = 0;
	}
	if (!dashing_ && dash_cooldown_) {

		dash_cooldown_--;
	}
	pos_.y += vel_.y * dT;
}
void Character::CollideY(Level& level)
{

	int tileX = pos_.x / TILE_SIZE;
	int tileY = pos_.y / TILE_SIZE;
	int startX = max(0, tileX);
	int startY = max(0, tileY);
	int endX = min(level.getWidth(), (pos_.x + rect_.w) / TILE_SIZE);
	int endY = min(level.getHeight(), (pos_.y + rect_.h) / TILE_SIZE);
	SDL_Rect tileRect{};
	bool somethingBelow = false;
	for (int y = startY; y <= endY; y++) {

		for (int x = startX; x <= endX; x++)
		{

			tileRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
			if (level.getTile(x, y)->getType() != Tile::Type::EMPTY) {
				if (y == endY) {
					somethingBelow = true;
				}
				if (checkCollision({ (int)pos_.x ,(int)pos_.y ,rect_.w,rect_.h }, tileRect)) {
					if (vel_.y >= 0) {
						//move down
						on_ground_ = true;
						vel_.y = 0;
						pos_.y = tileRect.y - rect_.h;;

					}
					else if (vel_.y < 0) {
						//jump
						vel_.y = 0;
						pos_.y = tileRect.y + tileRect.h;


					}


				}
			}
		}

	}
	if (!somethingBelow) {
		on_ground_ = false;

	}
	/*if (tileY < level.getHeight() && ((level.getTile(tileX, tileY + 1)->getType() == Tile::EMPTY && level.getTile(tileX + 1, tileY + 1)->getType() == Tile::EMPTY) || (pos_.x == tileX * TILE_SIZE && (level.getTile(tileX, tileY + 1)->getType() == Tile::EMPTY)))) {

	}*/
}