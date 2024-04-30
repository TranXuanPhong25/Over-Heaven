#include "PlayState.h"

PlayState PlayState::s_play_state_;
PlayState::PlayState() {
	loaded_player_spritesheet_ = false;
	is_on_enter_ = false;
	is_on_exit_ = false;
	overlay_alpha_ = 1.0f;
	should_change_level_ = false;
}

PlayState* PlayState::get()
{
	return &s_play_state_;
}
void PlayState::getOut(const float& dT)
{
	overlay_alpha_ += dT * 2;
	if (overlay_alpha_ > 1.0f) {
		overlay_alpha_ = 1.0f;
		should_change_level_ = true;
	}
}
void PlayState::getIn(const float& dT)
{

	overlay_alpha_ = Transition::lerp(overlay_alpha_, -0.01f, dT * 2);
	if (overlay_alpha_ < 0) {
		overlay_alpha_ = 0.0f;
		is_on_enter_ = false;
	}
}
void PlayState::handleTransition(const float& dT)
{
	if (is_on_enter_)
	{
		getIn(dT);
	}
	if (is_on_exit_)
	{
		getOut(dT);
	}

}
void PlayState::renderTransitionFx(SDL_Renderer* ren)
{
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, static_cast<Uint8>(overlay_alpha_ * 255));
	SDL_RenderFillRect(ren, &ENTIRE_WINDOW);
}
void PlayState::handleChangeLevel()
{
	if (player_.isReachedGoal()) {
		player_.handleReachGoal();
		is_on_exit_ = true;
	}
	if (should_change_level_) {
		level_.toNextLevel();
	}
}
float PlayState::loadResources(SDL_Renderer* ren, std::atomic<float>* progress)
{

	level_.loadSavedPath();
	*progress = *progress + 1.0f / TOTAL_LOADING_STEP;

	level_.loadTiles();
	*progress = *progress + 1.0f / TOTAL_LOADING_STEP;

	level_.loadResources(ren, progress);

	if (!loaded_player_spritesheet_) {
		player_.loadTexture(ren, PLAYER_SPRITESHEET_PATH);
		loaded_player_spritesheet_ = true;
	}
	*progress = *progress + 1.0f / TOTAL_LOADING_STEP;

	//this action may be redundant but it doesn't hurt to load it again
	player_.loadStats(level_);
	*progress = *progress + 1.0f / TOTAL_LOADING_STEP;

	return *progress;
}
bool PlayState::enter(SDL_Renderer* ren)
{
	is_on_enter_ = true;
	if (should_change_level_) {
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
	is_on_exit_ = false;
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
	handleChangeLevel();
	handleTransition(dT);
}
void PlayState::render(SDL_Renderer* ren)
{

	level_.renderFarGround(ren);
	level_.renderBackground(ren);
	player_.render(ren);
	level_.renderForeGround(ren);
	level_.renderNearGround(ren);
	level_.renderFaceGround(ren);
	if (is_on_enter_ || is_on_exit_) {
		renderTransitionFx(ren);
	}
}
void PlayState::deleteSave()
{
	//set flag load default to true
	should_change_level_ = true;
	try
	{
		std::remove("save/save_game.xml");
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
