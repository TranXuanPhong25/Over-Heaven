#include "PlayState.h"

PlayState PlayState::s_play_state_;
PlayState::PlayState() {}

PlayState* PlayState::get() {
	return &s_play_state_;
}
bool PlayState::enter(SDL_Renderer* ren) {
	level_.setPath("assets/level/map1.csv");
	level_.loadSpriteTiles(ren, "assets/level/0.png");
	player_.loadTexture(ren, NUNU_TEXTURE_PATH_64X91);
	cam_.setPosition(0, level_.getHeight() - cam_.getViewport().h);

	player_.setRect(TILE_SIZE * 3, level_.getHeight() * TILE_SIZE - TILE_SIZE * 8, cam_);

	return true;
}
bool PlayState::exit() {
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
	//player_.handleLevelInteraction(level_);
	//SDL_Delay(100);
}
void PlayState::render(SDL_Renderer* ren) {

	level_.render(ren, cam_);
	player_.render(ren);
}
