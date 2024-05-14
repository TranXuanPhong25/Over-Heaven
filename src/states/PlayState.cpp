#include "PlayState.hpp"

PlayState PlayState::s_play_state_;
PlayState::PlayState()
{
	loaded_player_data_ = false;
	should_change_level_ = false;
}

PlayState *PlayState::get()
{
	return &s_play_state_;
}

void PlayState::finishGetOut()
{
	should_change_level_ = true;
}

void PlayState::handleChangeLevel()
{
	if (player_.isReachedGoal())
	{
		player_.handleReachGoal();
		startGetOutEffect();
	}
	if (should_change_level_)
	{
		level_.toNextLevel();
	}
}
float PlayState::loadResources(SDL_Renderer *ren, std::atomic<float> *progress)
{

	level_.loadSavedPath();
	*progress = *progress + 1.0f / TOTAL_LOADING_STEP;

	level_.loadTiles();
	*progress = *progress + 1.0f / TOTAL_LOADING_STEP;

	level_.loadResources(ren, progress);

	if (!loaded_player_data_)
	{
		try
		{
			player_.loadData(PLAYER_DATA_PATH);
			*progress = *progress + 1.0f / TOTAL_LOADING_STEP;
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}

		player_.loadTexture(ren);
		*progress = *progress + 1.0f / TOTAL_LOADING_STEP;
		
		loaded_player_data_ = true;
	}
	else
	{
		*progress = *progress + 2.0f / TOTAL_LOADING_STEP;
	}

	player_.loadStats(level_); // this action may be redundant but it doesn't hurt to load it again
	*progress = *progress + 1.0f / TOTAL_LOADING_STEP;
	return *progress;
}
bool PlayState::enter(SDL_Renderer *ren)
{
	startGetInEffect();
	if (should_change_level_)
	{
		player_.resetStats();
		player_.setDefaultPosition(level_);
		should_change_level_ = false;
	}
	cam_.setPosition(player_.getPos().x - static_cast<float>(SCREEN_WIDTH) / 2, player_.getPos().y - static_cast<float>(SCREEN_WIDTH) / 2);
	return true;
}

bool PlayState::exit()
{
	player_.saveStats();
	level_.savePath();

	return true;
}
void PlayState::handleEvent(SDL_Event &e)
{
	player_.handleInput(e);
}
void PlayState::update(const float &dT)
{

	player_.update(level_, cam_, dT);
	cam_.move(player_.getVel() * dT);
	cam_.centerOn(player_.getPos(), player_.getRect().w, player_.getRect().h, level_.getWidth(), level_.getHeight());
	player_.updateRect(cam_);
	level_.update(cam_);
	handleChangeLevel();
	handleTransition(dT);
}
void PlayState::render(SDL_Renderer *ren)
{

	level_.renderFarGround(ren);
	level_.renderBackground(ren);
	player_.render(ren);
	level_.renderForeGround(ren);
	level_.renderNearGround(ren);
	level_.renderFaceGround(ren);
	renderTransitionFx(ren);
}
void PlayState::deleteSave()
{
	// set flag load default to true
	should_change_level_ = true;
	try
	{
		std::remove(SAVE_PATH);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
