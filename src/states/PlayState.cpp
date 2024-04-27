#include "PlayState.h"

PlayState PlayState::s_play_state_;
PlayState::PlayState() {
	loaded_player_spritesheet_ = false;
	is_get_in_ = false;
	get_in_fx_ = NULL;
	
}

PlayState* PlayState::get()
{
	return &s_play_state_;
}
void PlayState::getOut()
{

}
void PlayState::getIn()
{
	
}
float PlayState::loadResources(SDL_Renderer *ren, std::atomic<float> *progress)
{
	float totalSteps = 5.0f;
	level_.loadSavedPath();
	*progress = *progress + 1.0f / totalSteps;


	level_.loadResources(ren);
	*progress = *progress + 1.0f / totalSteps;

	level_.loadTiles();
	*progress = *progress + 1.0f / totalSteps;

	if (!loaded_player_spritesheet_) {
		player_.loadTexture(ren, PLAYER_SPRITESHEET_PATH);
		loaded_player_spritesheet_ = true;
	}
	*progress = *progress + 1.0f / totalSteps;

	player_.loadStats(level_);
	*progress = *progress + 1.0f / totalSteps;

	return *progress;
}
bool PlayState::enter(SDL_Renderer* ren)
{
	cam_.setPosition(player_.getPos().x - static_cast<float>(SCREEN_WIDTH) / 2, player_.getPos().y - static_cast<float>(SCREEN_WIDTH) / 2);
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
