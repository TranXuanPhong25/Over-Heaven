#include "PlayState.h"

PlayState PlayState::s_play_state_;
PlayState::PlayState() {
	cam_ = new Camera();

}

PlayState* PlayState::get() {
	return &s_play_state_;
}
bool PlayState::enter(SDL_Renderer* ren) {
	player_.loadTexture(ren, NUNU_TEXTURE_PATH_64X91);
	player_.setRect(INIT_POS_X, INIT_POS_Y);
	level_.setPath("assets/level/map1.csv");
	level_.loadSpriteTiles(ren, "assets/level/0.png");
	return true;
}
bool PlayState::exit() {
	return true;
}
void PlayState::handleEvent(SDL_Event& e) {
	player_.handleInput(e);

}
void PlayState::update(const float& dT) {
	player_.update(level_, 1);
	//player_.handleLevelInteraction(level_);
}
void PlayState::render(SDL_Renderer* ren) {

	level_.render(ren, cam_);
	player_.render(ren);
}
