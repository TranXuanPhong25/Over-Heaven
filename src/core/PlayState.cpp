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
	cam_.setPosition(player_.getPos().x - SCREEN_WIDTH / 2, player_.getPos().y - SCREEN_HEIGHT / 2);
	cam_.centerOn(player_.getPos(), player_.getRect().w, player_.getRect().h, level_.getWidth() * TILE_SIZE, level_.getHeight() * TILE_SIZE);
	player_.loadStats(level_);
	level_.loadResources(ren);

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
	std::cout << "enter nek" << player_.getPos().y << std::endl;
	player_.update(level_, cam_, dT);
	cam_.move(player_.getVel() * dT);
	cam_.centerOn(player_.getPos(), player_.getRect().w, player_.getRect().h, level_.getWidth() * TILE_SIZE, level_.getHeight() * TILE_SIZE);
	player_.updateRect(cam_);
	level_.update(cam_);
}
void PlayState::render(SDL_Renderer* ren) {

	level_.renderFarGround(ren);
	level_.renderBackground(ren);
	level_.renderForeGround(ren);
	level_.render(ren, cam_);
	player_.render(ren);
}
void PlayState::deleteSave()
{
	try {
		std::remove("save/save_game.xml");

	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
