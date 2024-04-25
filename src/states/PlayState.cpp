#include "PlayState.h"

PlayState PlayState::s_play_state_;
PlayState::PlayState() {}

PlayState* PlayState::get()
{
	return &s_play_state_;
}
void PlayState::loadResources(SDL_Renderer* ren)
{
	try {
		level_.loadSavedPath();
	}
	catch (const std::exception& e) {
		std::cerr << "Error loading saved path: " << e.what() << std::endl;
		// Handle the error (e.g., by loading default saved path or terminating the program)
	}

	try {
		level_.loadFromFile();
	}
	catch (const std::exception& e) {
		std::cout << SDL_GetError();
	}

	try {
		level_.loadResources(ren);
	}
	catch (const std::exception& e) {
		std::cout << SDL_GetError();

	}
	try {
		player_.loadTexture(ren, NUNU_TEXTURE_PATH_64X91);
	}
	catch (const std::exception& e) {
		std::cerr << "Error loading player texture: " << e.what() << std::endl;
		// Handle the error (e.g., by loading default texture or terminating the program)
	}

	try {
		player_.loadStats(level_);

	}
	catch (const std::exception& e) {
		std::cerr << "Error loading player stats: " << e.what() << std::endl;
		// Handle the error (e.g., by loading default stats or terminating the program)
	}
}
bool PlayState::enter(SDL_Renderer* ren)
{
	cam_.setPosition(player_.getPos().x - SCREEN_WIDTH / 2, player_.getPos().y - SCREEN_HEIGHT / 2);
	return true;
}

bool PlayState::exit()
{
	player_.saveStats();
	level_.savePath();
	return true;
}
void PlayState::handleEvent(SDL_Event& e)
{
	player_.handleInput(e);
}
void PlayState::update(const float& dT)
{

	player_.update(level_, cam_, dT);
	cam_.move(player_.getVel() * dT);
	cam_.centerOn(player_.getPos(), player_.getRect().w, player_.getRect().h, level_.getWidth() * TILE_SIZE, level_.getHeight() * TILE_SIZE);
	player_.updateRect(cam_);
	level_.update(cam_);
}
void PlayState::render(SDL_Renderer* ren)
{
	
	level_.renderFarGround(ren);
	level_.renderBackground(ren);
	player_.render(ren);
	level_.renderForeGround(ren);
	level_.renderFaceGround(ren);

}
void PlayState::deleteSave()
{
	try
	{
		std::remove("save/save_game.xml");
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
