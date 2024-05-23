#include "PlayState.hpp"

PlayState PlayState::s_play_state_;
PlayState::PlayState()
{
	loaded_player_data_ = false;
	should_change_level_ = false;
	navigate_sound_ = NULL;
	select_sound_ = NULL;
	adjust_sound_ = NULL;
	background_music_ = NULL;
	pause_menu_bg_ = NULL;
	buttons_[0].setType(Button::CONTINUE);
	buttons_[1].setType(Button::OPTIONS);
	buttons_[2].setType(Button::EXIT);
	buttons_[3].setType(Button::VOLUME_SLIDER);
	buttons_[4].setType(Button::SLIDER);
	buttons_[5].setType(Button::BACK);


	current_button_ = PauseMenuButton::CONTINUE;

	state_ = PLAY;
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

	background_music_ = Mix_LoadMUS(PLAY_MUSIC_PATHS[level_.getLevelIndex()].c_str());

	select_sound_ = Mix_LoadWAV(BUTTON_SOUND_PATH[Channel::SELECT].c_str());
	navigate_sound_ = Mix_LoadWAV(BUTTON_SOUND_PATH[Channel::NAVIGATE].c_str());
	adjust_sound_ = Mix_LoadWAV(BUTTON_SOUND_PATH[Channel::ADJUST].c_str());

	pause_menu_bg_ = IMG_LoadTexture(ren, MENU_BACKGROUND_TEXTURE_PATH.c_str());
	for (int i = 0; i < NUM_OF_PAUSE_MENU_BUTTONS-NUM_OF_OPTIONS_BUTTONS; i++)
	{
		buttons_[i].loadTexture(ren, BUTTON_TEXTURE_PATHS[i]);
	}
	buttons_[PauseMenuButton::VOLUME_SLIDER].loadTexture(ren, BUTTON_TEXTURE_PATHS[Button::VOLUME_SLIDER]);
	buttons_[PauseMenuButton::SLIDER].loadTexture(ren, BUTTON_TEXTURE_PATHS[Button::SLIDER]);
	buttons_[PauseMenuButton::BACK].loadTexture(ren, BUTTON_TEXTURE_PATHS[Button::BACK]);
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
	state_=PLAY;
	startGetInEffect();

	if (should_change_level_)
	{
		player_.resetStats();
		player_.setDefaultPosition(level_);
		should_change_level_ = false;
	}

	// load button
	for (int i = 0; i < NUM_OF_PAUSE_MENU_BUTTONS-NUM_OF_OPTIONS_BUTTONS; i++)
	{
		buttons_[i].setRectY(SCREEN_HEIGHT / 2 + i * BUTTON_PADDING);
	}

	buttons_[PauseMenuButton::VOLUME_SLIDER].setRectY(SCREEN_HEIGHT / 2 + BUTTON_PADDING);

	buttons_[PauseMenuButton::SLIDER].setRectXCenterOn(buttons_[PauseMenuButton::VOLUME_SLIDER].getRect().x + buttons_[Button::VOLUME_SLIDER].getRect().w*Mix_VolumeMusic(-1)/MIX_MAX_VOLUME);
	buttons_[PauseMenuButton::SLIDER].setRectY(buttons_[PauseMenuButton::VOLUME_SLIDER].getRect().y + SLIDER_PADDING);

	buttons_[PauseMenuButton::BACK].setRectY(SCREEN_HEIGHT / 2 + 3 * BUTTON_PADDING);

	cam_.setPosition(player_.getPos().x - static_cast<float>(SCREEN_WIDTH) / 2, player_.getPos().y - static_cast<float>(SCREEN_WIDTH) / 2);
	return true;
}

bool PlayState::exit()
{
	
	player_.saveStats();
	level_.savePath();
	Mix_FreeMusic(background_music_);
	background_music_ = NULL;
	Mix_FreeChunk(navigate_sound_);
	Mix_FreeChunk(select_sound_);
	Mix_FreeChunk(adjust_sound_);
	SDL_DestroyTexture(pause_menu_bg_);
	return true;
}
void PlayState::handleEvent(SDL_Event &e)
{
	if (state_ == PLAY)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
		{
			state_ = PAUSE;
			current_button_ = PauseMenuButton::CONTINUE;
		}
		player_.handleInput(e);
	}
	else

		if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)
		{
			handleNavigateUp();
		}
		else if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
		{
			handleNavigateDown();
		}
		else if (e.key.keysym.sym == SDLK_RETURN)
		{
			handleEnter();
		}
		else if (e.key.keysym.sym == SDLK_ESCAPE)
		{
			if (state_ == OPTIONS)
			{
				current_button_ = PauseMenuButton::OPTIONS;
				state_ = PAUSE;
			}
			else
			{
				state_ = PLAY;
				current_button_ = PauseMenuButton::CONTINUE;
			}
		}
		else if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)
		{
			handleAdjustVolume(LEFT);
		}
		else if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)
		{
			handleAdjustVolume(RIGHT);
		}
	}
}
void PlayState::update(const float &dT)
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(background_music_, -1);
	}
	if (state_ == PLAY)
	{

		player_.update(level_, cam_, dT);
		cam_.move(player_.getVel() * dT);
		cam_.centerOn(player_.getPos(), player_.getRect().w, player_.getRect().h, level_.getWidth(), level_.getHeight());
		player_.updateRect(cam_);
		level_.update(cam_);
		handleChangeLevel();
		handleTransition(dT);
	}
	else
	{
		for (int i = 0; i < NUM_OF_PAUSE_MENU_BUTTONS; i++)
		{

			if (current_button_ == PauseMenuButton::VOLUME_SLIDER)
			{
				buttons_[PauseMenuButton::SLIDER].enhanceAlpha();
			}
			else
			{
				buttons_[PauseMenuButton::SLIDER].reduceAlpha();
			}
			if (buttons_[state_ + i].getType() == current_button_)
			{

				buttons_[state_ + i].enhanceAlpha();
			}
			else
			{
				buttons_[state_ + i].reduceAlpha();
			}
		}
	}
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
	if (state_ == PAUSE)
	{
		SDL_RenderCopy(ren, pause_menu_bg_, NULL, NULL);
		for (int i = 0; i < NUM_OF_PAUSE_MENU_BUTTONS - NUM_OF_OPTIONS_BUTTONS; i++)
		{
			buttons_[i + state_].render(ren);
		}
	}
	else if (state_ == OPTION)
	{
		SDL_RenderCopy(ren, pause_menu_bg_, NULL, NULL);

		for (int i = 0; i < NUM_OF_OPTIONS_BUTTONS; i++)
		{
			buttons_[i + state_].render(ren);
		}
	}
}
void PlayState::deleteSave()
{
	// set load default data flag to true
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

void PlayState::handleNavigateUp()
{
	Mix_PlayChannel(Channel::NAVIGATE, navigate_sound_, 0);
	if (state_ == PAUSE)
	{
		if (current_button_ == PauseMenuButton::CONTINUE)
		{
			current_button_ = PauseMenuButton::EXIT;
		}
		else
		{

			current_button_ = current_button_ == PauseMenuButton::CONTINUE ? PauseMenuButton::EXIT : static_cast<PauseMenuButton>(current_button_ - 1);
		}
	}
	else
	{
		if (current_button_ == PauseMenuButton::BACK)
			current_button_ = PauseMenuButton::VOLUME_SLIDER;
		else if (current_button_ == PauseMenuButton::VOLUME_SLIDER)
			current_button_ = PauseMenuButton::BACK;
	}
}

void PlayState::handleNavigateDown()
{
	Mix_PlayChannel(Channel::NAVIGATE, navigate_sound_, 0);

	if (state_ == PAUSE)
	{
		if (current_button_ == PauseMenuButton::EXIT)
		{
			current_button_ = PauseMenuButton::CONTINUE ;
		}
		else
		{
			current_button_ = static_cast<PauseMenuButton>((current_button_ + 1));
		}
	}
	else
	{
		if (current_button_ == PauseMenuButton::VOLUME_SLIDER)
			current_button_ = PauseMenuButton::BACK;
		else if (current_button_ == PauseMenuButton::BACK)
			current_button_ = PauseMenuButton::VOLUME_SLIDER;
	}
}

void PlayState::handleEnter()
{
	Mix_PlayChannel(Channel::SELECT, select_sound_, 0);
	if (state_ == PAUSE)
	{
		switch (current_button_)
		{
		case PauseMenuButton::CONTINUE:
			state_ = PLAY;
			current_button_ = PauseMenuButton::CONTINUE;
			break;

		case PauseMenuButton::OPTIONS:
			state_ = OPTION;
			current_button_ = PauseMenuButton::VOLUME_SLIDER;
			break;
		case PauseMenuButton::EXIT:
			StateMachine::get()->setNextState(ExitState::get());
			break;
		}
	}
	else
	{
		if (current_button_ == PauseMenuButton::BACK)
		{
			current_button_ = PauseMenuButton::OPTIONS;
			state_ = PAUSE;
		}
	}
}
void PlayState::handleAdjustVolume(int direction)
{
	if (current_button_ == PauseMenuButton::VOLUME_SLIDER)
	{

		int volume = Mix_Volume(-1, -1);
		int volumeMusic = Mix_VolumeMusic(-1);
		volume += direction * 2;
		volumeMusic += direction * 2;
		volume = volume < 0 ? 0 : volume;
		volumeMusic = volumeMusic < 0 ? 0 : volumeMusic;
		volume = volume > MIX_MAX_VOLUME ? MIX_MAX_VOLUME : volume;
		volumeMusic = volumeMusic > MIX_MAX_VOLUME ? MIX_MAX_VOLUME : volumeMusic;
		Mix_VolumeMusic(volume);
		Mix_Volume(-1, volume);

		Mix_PlayChannel(Channel::ADJUST, adjust_sound_, 0);
		// move slider relative with volume
		buttons_[PauseMenuButton::SLIDER].setRectXCenterOn(buttons_[PauseMenuButton::VOLUME_SLIDER].getRect().x + volume * buttons_[PauseMenuButton::VOLUME_SLIDER].getRect().w / MIX_MAX_VOLUME);
	}
}
