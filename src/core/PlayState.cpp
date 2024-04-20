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
	cam_.centerOn(player_.getPos(), player_.getRect().w, player_.getRect().h, level_.getWidth() * TILE_SIZE, level_.getHeight() * TILE_SIZE);
	player_.loadStats(level_);
	level_.bg = IMG_LoadTexture(ren, "assets/level/bg1.png");
	level_.far_ground_ = IMG_LoadTexture(ren, "assets/level/farground.png");
	level_.far_ground_clip_.x = 0;
	level_.far_ground_clip_.y = 0;
	level_.far_ground_clip_.w = 1920;
	level_.far_ground_clip_.h = 1080;
	level_.fore_ground_ = IMG_LoadTexture(ren, "assets/level/foreground.png");
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
	level_.far_ground_clip_.x = cam_.getPos().x / 5760 * 1642;
}
void PlayState::render(SDL_Renderer* ren) {
	//level_.render(ren, cam_);
	SDL_Rect sr;
	sr.x = cam_.getPos().x;
	sr.y = cam_.getPos().y;
	sr.w = SCREEN_WIDTH;
	sr.h = SCREEN_HEIGHT;
	SDL_RenderCopy(ren, level_.far_ground_, &level_.far_ground_clip_, NULL);

	SDL_RenderCopy(ren, level_.bg, &sr, NULL);
	player_.render(ren);
	SDL_RenderCopy(ren, level_.fore_ground_, &sr, NULL);
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
