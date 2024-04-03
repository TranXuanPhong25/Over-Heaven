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
	double_jump_ = false;
	hurtbox_ = { rect_.x + rect_.w / 2,rect_.y + rect_.h / 2,30,30 };
	rolling_ = false;
	can_roll_ = true;
	rolling_frame_ = 0;
	roll_dir_ = 0;
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
		if (rolling_frame_ < 30) {
			vel_.x = roll_dir_ * speed_ / RUN_SPEED * 20;
			//std::cout << roll_dir_ << " " << state_ << std::endl;;
			std::cout << vel_.x;
			pos_.x += vel_.x * dT;
			rolling_frame_++;
		}
		else {
			rolling_frame_ = 0;
			rolling_ = false;
			can_roll_ = true;
		}

	}
	else {
		vel_.x = (dir_right_ - dir_left_) * speed_ / RUN_SPEED * 10;
		pos_.x += vel_.x * dT;

	}

}
void Character::moveY(const float& dT) {
	if (spacekey_pressed_) {
		if (on_ground_) {
			on_ground_ = false;
			vel_.y -= static_cast<int>(speed_ * 1.4);
		}
		else if (double_jump_) {
			double_jump_ = false;
			vel_.y -= static_cast<int>(speed_ * 1.4);
		}
	}
	//gravity
	if (!on_ground_) {
		if (vel_.y > 0) {
			vel_.y += static_cast<int>(GRAVITY * 1.3 * dT);
		}
		vel_.y += static_cast<int>(GRAVITY * 2.3 * dT);
		pos_.y += int(round(vel_.y * dT));
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