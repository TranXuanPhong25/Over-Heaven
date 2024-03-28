#include "header/Ammo.h"

Ammo::Ammo() {
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
	texture_ = NULL;

	x_vel_ = 0;
	y_vel_ = 0;
	is_move_ = true;
	type_ = DEFAULT;
	shoot_time_ = SDL_GetTicks();

}
Ammo::~Ammo() {
	free();
}
void Ammo::move(const float& dT) {
	rect_.x += int(round((AMMO_VEL)*dT));
	rect_.x += int(round((AMMO_A * (SDL_GetTicks() - shoot_time_) / 100.f) * dT));


	if ((rect_.x < 0) || (rect_.x > SCREEN_WIDTH)) {
		free();
		is_move_ = false;
	}
	/*if ((rect_.y < 0) || (rect_.y + AMMO_HEIGHT > SCREEN_HEIGHT)) {
		free();
	}*/
}
bool Ammo::isMoving() const {
	return is_move_;
}
void Ammo::setType(const int& type) {
	type_ = type;
}
int Ammo::getType() const {
	return type_;
}