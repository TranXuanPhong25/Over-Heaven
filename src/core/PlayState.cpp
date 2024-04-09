#include "PlayState.h"

PlayState PlayState::s_play_state_;
PlayState::PlayState() {}

PlayState* PlayState::get() {
	return &s_play_state_;
}
bool PlayState::enter(SDL_Renderer* ren) {
	level_.loadSavedPath();
	level_.loadSpriteTiles(ren);
	player_.loadTexture(ren, NUNU_TEXTURE_PATH_64X91);
	cam_.setPosition(0, level_.getHeight() - cam_.getViewport().h);
	player_.loadStats(level_);
	return true;
}

bool PlayState::exit() {
	player_.saveStats();
	level_.savePath();
	return true;
}
void PlayState::handleEvent(SDL_Event& e) {
	player_.handleInput(e);
}
void PlayState::update(const float& dT) {

	player_.update(level_, cam_, dT);
	cam_.move(player_.getVel() * dT);
	cam_.centerOn(player_.getPos(), player_.getRect().w, player_.getRect().h, level_.getWidth() * TILE_SIZE, level_.getHeight() * TILE_SIZE);
	player_.updateRect(cam_);
	//SDL_Delay(50);

}
void PlayState::render(SDL_Renderer* ren) {
	level_.render(ren, cam_);
	player_.render(ren);
}
