#include "Character.h"
Character::Character() {
	speed_ = 540;
	vel_ = { 0,0 };
	state_ = IDLE;
	spacekey_pressed_ = false;
	/*accelerator_ = 0;*/
	on_ground_ = false;
	dir_left_ = 0;
	dir_right_ = 0;
	gravity_scalar_ = 2;
	jump_count_ = 2;
	hurtbox_ = { rect_.x + rect_.w / 2,rect_.y + rect_.h / 2,30,30 };

	rolling_ = false;
	can_roll_ = true;

	rolling_frame_ = 0;
	roll_dir_ = 0;
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
			/*if (accelerator_ <= 0) {
				state_ = MOVE_LEFT;
			}*/
		}
		if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)) {
			dir_right_ = 1;
			/*if (accelerator_ >= 0) {

				state_ = MOVE_RIGHT;
			}*/
		}
		if (e.key.keysym.sym == SDLK_LSHIFT) {
			if (can_roll_) {
				if (state_ == MOVE_LEFT) {
					roll_dir_ = LEFT;
				}
				else if (state_ = MOVE_RIGHT) {
					roll_dir_ = RIGHT;
				}
				std::cout << dir_right_ << " " << dir_left_ << std::endl;
				rolling_ = true;
				can_roll_ = false;
			}
			/*if (accelerator_ >= 0) {

				state_ = MOVE_RIGHT;
			}*/
		}
	}
	if (e.type == SDL_KEYUP) {
		if (e.key.keysym.sym == SDLK_SPACE) {
			spacekey_pressed_ = false;
		}
		if ((e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)) {
			dir_left_ = 0;
		}
		if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)) {
			dir_right_ = 0;
		}
	}
	if (e.type == SDL_MOUSEBUTTONDOWN) {

	}
	if (e.type == SDL_MOUSEBUTTONUP) {

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
	if (dir_right_ - dir_left_ == RIGHT) {
		state_ = MOVE_RIGHT;
	}
	else if (dir_right_ - dir_left_ == LEFT) {
		state_ = MOVE_LEFT;
	}


	moveX(dT);
	CollideX(level);
	moveY(dT);
	CollideY(level);
}

void Character::moveX(const float& dT) {
	if (rolling_) {
		roll(dT);
	}
	else {
		vel_.x = (dir_right_ - dir_left_) * speed_ / RUN_SPEED * 10;
		pos_.x += vel_.x * dT;

	}
}
void Character::CollideX(Level& level) {
	int tileX = pos_.x / TILE_SIZE;
	int tileY = pos_.y / TILE_SIZE;
	int startX = max(0, tileX - 1);
	int startY = max(0, tileY - 1);
	int endX = min(level.getWidth(), (pos_.x + rect_.w) / TILE_SIZE + 1);
	int endY = min(level.getHeight(), (pos_.y + rect_.h) / TILE_SIZE + 1);
	for (int x = startX; x <= endX + 1; x++) {
		for (int y = startY; y <= endY + 2; y++)
		{
			SDL_Rect tileRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
			if (checkCollision({ (int)pos_.x ,(int)pos_.y ,rect_.w,rect_.h }, tileRect) && level.getTile(x, y)->getType() != Tile::Type::EMPTY) {

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

float lerp(float a, float b, float t) {
	return (1 - t) * a + t * b;
}
void Character::roll(const float& dT) {
	if (rolling_frame_ < MAX_ROLLING_FRAMES) {
		vel_.x = roll_dir_ * speed_ / RUN_SPEED * 20;
		pos_.x += vel_.x * dT;
		rolling_frame_++;
	}
	else {
		rolling_frame_ = 0;
		rolling_ = false;
		can_roll_ = true;
	}

}
void Character::jump(const float& dT) {
	on_ground_ = false;
	vel_.y = -JUMP_HEIGHT;
	coyote_time_ = 0;
	gravity_scalar_ = 5;
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
	if (!on_ground_) {
		if (coyote_time_) coyote_time_--;
		if (vel_.y > 90) {
			gravity_scalar_ = 4;

		}
		else  if (vel_.y > -90) {
			gravity_scalar_ = 1.3;
		}
		else {
			if (spacekey_pressed_) {

				gravity_scalar_ -= (gravity_scalar_ > 1.55) ? 0.25 : 0;
			}
		}
		if (vel_.y > MAX_FALL_SPEED * 1.5) {
			vel_.y = MAX_FALL_SPEED * 1.5;
		}
		else {
		}

		vel_.y += GRAVITY * gravity_scalar_ * dT;
	}
	else {
		vel_.y = 0;
		coyote_time_ = MAX_COYOTE_TIME;
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