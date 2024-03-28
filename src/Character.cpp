#include "header/Character.h"
Character::Character() {
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
	texture_ = NULL;
	speed_ = 540;
	x_vel_ = 0;
	y_vel_ = 0;
	state_ = REST;
	spacekey_pressed_ = false;
	accelerator_ = 0;
	on_ground_ = true;
}
Character::~Character() {
	free();
}

void Character::handleInput(SDL_Event e) {
	//NOTE: update state on here only 
	//NEVER do logic update here

	if (e.type == SDL_KEYDOWN) {

		if (e.key.keysym.sym == SDLK_SPACE) {
			spacekey_pressed_ = true;
		}
		if ((e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)) {
			x_vel_ = LEFT;
			if (accelerator_ <= 0) {
				state_ = MOVE_LEFT;
			}
		}
		if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)) {
			x_vel_ = RIGHT;
			if (accelerator_ >= 0) {

				state_ = MOVE_RIGHT;
			}
		}
	}
	if (e.type == SDL_KEYUP) {
		if (e.key.keysym.sym == SDLK_SPACE) {
			spacekey_pressed_ = false;
		}
		/*if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s) {
			y_vel_ -= speed_;*/

			//}
		if ((e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)) {
			x_vel_ = 0;
		}
		if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)) {
			x_vel_ = 0;
		}
	}
	if (e.type == SDL_MOUSEBUTTONDOWN) {

	}
	if (e.type == SDL_MOUSEBUTTONUP) {

	}


}
bool Character::shoudSlowDown() const {
	return (state_ == MOVE_LEFT && accelerator_ < 0 && x_vel_ == 0)
		|| (state_ == MOVE_RIGHT && accelerator_ > 0 && x_vel_ == 0);
}
int Character::getVelX()const {
	return x_vel_;
}
void Character::move(const float& dT) {

	if (shoudSlowDown()) {
		if (state_ == MOVE_RIGHT) {
			accelerator_ -= RIGHT * speed_ / RUN_SPEED;
		}
		else {
			accelerator_ -= LEFT * speed_ / RUN_SPEED;
		}
	}
	else if (x_vel_ != 0) {
		accelerator_ += x_vel_ * speed_ / RUN_SPEED;
	}
	else {
		accelerator_ = 0;
	}
	if (accelerator_ >= MAX_RUN_SPEED) {
		accelerator_ = MAX_RUN_SPEED;
	}
	if (accelerator_ <= -MAX_RUN_SPEED) {
		accelerator_ = -MAX_RUN_SPEED;
	}
	//std::cout << accelerator_ << " " << x_vel_ << " " << state_ << std::endl;
	rect_.x += static_cast<int>(round(accelerator_ * dT));

	//jump
	if (spacekey_pressed_) {
		if (on_ground_) {
			on_ground_ = false;
			y_vel_ -= static_cast<int>(speed_ * 2.8);
		}
	}
	//gravity
	if (!on_ground_) {
		if (y_vel_ > 0) {
			y_vel_ -= static_cast<int>(GRAVITY * 0.7 * dT);
		}
		y_vel_ += static_cast<int>(GRAVITY * dT);

		rect_.y += int(round(y_vel_ * dT));
	}


	//Character wrapper screen
	if (rect_.x + rect_.w > SCREEN_WIDTH) {
		rect_.x = SCREEN_WIDTH - rect_.w;
	}
	if (rect_.y >= INIT_POS_Y) {
		rect_.y = INIT_POS_Y;
		y_vel_ = 0;
		on_ground_ = true;
	}
	if (rect_.x < 0) {
		rect_.x = 0;
	}
	if (rect_.y < 0) {
		rect_.y = 0;
	}


}
