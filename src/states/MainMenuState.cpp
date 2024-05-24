#include "MainMenuState.hpp"

MainMenuState MainMenuState::s_main_menu_state_;
MainMenuState::MainMenuState()
{
	p_video_streamer_ = new VideoStreamer();
	bg_ = NULL;
	background_music_ = NULL;
	navigate_sound_ = NULL;
	select_sound_ = NULL;
	adjust_sound_ = NULL;
	for (int i = 0; i < Button::NUM_BUTTONS; i++)
	{
		buttons_[i].setType(static_cast<Button::Type>(i));
	}

	current_button_ = Button::NEWGAME;

	continue_available_ = false;
	state_ = MAINMENU;
	current_num_buttons_ = NUM_OF_MAIN_MENU_BUTTONS;
}
MainMenuState::~MainMenuState()
{
	delete p_video_streamer_;
}
MainMenuState *MainMenuState::get()
{
	return &s_main_menu_state_;
}
bool MainMenuState::enter(SDL_Renderer *ren)
{
	VolumeLoader::loadVolume();
	background_music_ = Mix_LoadMUS(MENU_MUSIC_PATH.c_str());
	navigate_sound_ = Mix_LoadWAV(BUTTON_SOUND_PATH[Channel::NAVIGATE].c_str());
	select_sound_ = Mix_LoadWAV(BUTTON_SOUND_PATH[Channel::SELECT].c_str());
	adjust_sound_ = Mix_LoadWAV(BUTTON_SOUND_PATH[Channel::ADJUST].c_str());
	startGetInEffect();

	p_video_streamer_->init(ren, VIDEO_MENU_BACKGROUND_PATH.c_str());
	bg_ = IMG_LoadTexture(ren, MENU_BACKGROUND_TEXTURE_PATH.c_str());
	for (int i = 0; i < NUM_OF_MAIN_MENU_BUTTONS; i++)
	{
		buttons_[i].loadTexture(ren, BUTTON_TEXTURE_PATHS[i]);
		buttons_[i].setRectY(SCREEN_HEIGHT / 2 + i * BUTTON_PADDING);
	}
	buttons_[Button::VOLUME_SLIDER].loadTexture(ren, BUTTON_TEXTURE_PATHS[Button::VOLUME_SLIDER]);
	buttons_[Button::VOLUME_SLIDER].setRectY(SCREEN_HEIGHT / 2 + BUTTON_PADDING);

	buttons_[Button::SLIDER].loadTexture(ren, BUTTON_TEXTURE_PATHS[Button::SLIDER]);
	buttons_[Button::SLIDER].setRectY(buttons_[Button::VOLUME_SLIDER].getRect().y + SLIDER_PADDING);
	buttons_[Button::SLIDER].setRectXCenterOn(buttons_[Button::VOLUME_SLIDER].getRect().x + buttons_[Button::VOLUME_SLIDER].getRect().w * Mix_VolumeMusic(-1)/ MIX_MAX_VOLUME);

	buttons_[Button::BACK].loadTexture(ren, BUTTON_TEXTURE_PATHS[Button::BACK]);
	buttons_[Button::BACK].setRectY(SCREEN_HEIGHT / 2 + 3 * BUTTON_PADDING);

	std::ifstream save_file(SAVE_PATH);
	continue_available_ = save_file.good();
	save_file.close();
	current_button_ = continue_available_ ? Button::CONTINUE : Button::NEWGAME;
	return true;
}
bool MainMenuState::exit()
{
	p_video_streamer_->free();
	Mix_FreeMusic(background_music_);
	background_music_ = NULL;
	Mix_FreeChunk(navigate_sound_);
	Mix_FreeChunk(select_sound_);
	Mix_FreeChunk(adjust_sound_);
	SDL_DestroyTexture(bg_);
	for (int i = 0; i < Button::NUM_BUTTONS; i++)
	{
		buttons_[i].free();
	}
	VolumeLoader::saveVolume();
	return true;
}
void MainMenuState::handleNavigateUp()
{
	Mix_PlayChannel(Channel::NAVIGATE, navigate_sound_, 0);
	if (state_ == MAINMENU)
	{
		if (current_button_ == Button::NEWGAME)
		{
			current_button_ = continue_available_ ? Button::CONTINUE : Button::EXIT;
		}
		else
		{

			current_button_ = current_button_ == Button::CONTINUE ? Button::EXIT : static_cast<Button::Type>(current_button_ - 1);
		}
	}
	else
	{
		if (current_button_ == Button::BACK)
			current_button_ = Button::VOLUME_SLIDER;
		else if (current_button_ == Button::VOLUME_SLIDER)
			current_button_ = Button::BACK;
	}
}

void MainMenuState::handleNavigateDown()
{
	Mix_PlayChannel(Channel::NAVIGATE, navigate_sound_, 0);

	if (state_ == MAINMENU)
	{
		if (current_button_ == Button::EXIT)
		{
			current_button_ = continue_available_ ? Button::CONTINUE : Button::NEWGAME;
		}
		else
		{
			current_button_ = static_cast<Button::Type>((current_button_ + 1) % NUM_OF_MAIN_MENU_BUTTONS);
		}
	}
	else
	{
		if (current_button_ == Button::VOLUME_SLIDER)
			current_button_ = Button::BACK;
		else if (current_button_ == Button::BACK)
			current_button_ = Button::VOLUME_SLIDER;
	}
}

void MainMenuState::handleEnter()
{
	Mix_PlayChannel(Channel::SELECT, select_sound_, 0);
	if (state_ == MAINMENU)
	{
		switch (current_button_)
		{
		case Button::CONTINUE:
			startGetOutEffect();
			break;
		case Button::NEWGAME:
			startGetOutEffect();
			PlayState::get()->deleteSave();
			break;
		case Button::OPTIONS:
			state_ = OPTIONS;
			current_button_ = Button::VOLUME_SLIDER;
			break;
		case Button::EXIT:
			StateMachine::get()->setNextState(ExitState::get());
			break;
		}
	}
	else
	{
		if (current_button_ == Button::BACK)
		{
			current_button_ = Button::OPTIONS;
			state_ = MAINMENU;
		}
	}
}
void MainMenuState::handleAdjustVolume(int direction)
{
	if (current_button_ == Button::VOLUME_SLIDER)
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
		buttons_[Button::SLIDER].setRectXCenterOn(buttons_[Button::VOLUME_SLIDER].getRect().x + volume * buttons_[Button::VOLUME_SLIDER].getRect().w / MIX_MAX_VOLUME);
	}
}

void MainMenuState::handleEsc()
{
	if (state_ == OPTIONS)
	{
		current_button_ = Button::OPTIONS;
		state_ = MAINMENU;
	}
}

void MainMenuState::handleEvent(SDL_Event &e)
{
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
			handleEsc();
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
void MainMenuState::update(const float &dT)
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(background_music_, -1);
	}

	current_num_buttons_ = (state_ == MAINMENU) ? NUM_OF_MAIN_MENU_BUTTONS : NUM_OF_OPTIONS_BUTTONS;
	for (int i = 0; i < current_num_buttons_; i++)
	{

		if (current_button_ == Button::VOLUME_SLIDER)
		{
			buttons_[Button::SLIDER].enhanceAlpha();
		}
		else
		{
			buttons_[Button::SLIDER].reduceAlpha();
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

	p_video_streamer_->readFrame();
	handleTransition(dT);
}
void MainMenuState::render(SDL_Renderer *ren)
{
	p_video_streamer_->render(ren);
	SDL_RenderCopy(ren, bg_, NULL, NULL);

	for (int i = 0; i < current_num_buttons_; i++)
	{
		buttons_[state_ + i].render(ren);
	}
	renderTransitionFx(ren);
}

void MainMenuState::finishGetOut()
{
	StateMachine::get()->setNextState(LoadingState::get());
}

