#include "MainMenuState.hpp"

MainMenuState MainMenuState::s_main_menu_state_;
MainMenuState::MainMenuState()
{
	p_video_streamer_ = new VideoStreamer();
	bg_ = NULL;
	background_music_ = NULL;

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
	if (bg_ != NULL)
	{
		SDL_DestroyTexture(bg_);
		bg_ = NULL;
	}
	delete p_video_streamer_;
}
MainMenuState *MainMenuState::get()
{
	return &s_main_menu_state_;
}
bool MainMenuState::enter(SDL_Renderer *ren)
{
	background_music_ = Mix_LoadMUS(MENU_MUSIC_PATH.c_str());

	startGetInEffect();

	p_video_streamer_->init(ren, VIDEO_MENU_BACKGROUND_PATH.c_str());
	bg_ = IMG_LoadTexture(ren, MENU_BACKGROUND_TEXTURE_PATH.c_str());
	for (int i = 0; i < Button::NUM_BUTTONS; i++)
	{
		buttons_[i].loadTexture(ren, BUTTON_TEXTURE_PATHS[i]);
		buttons_[i].setRectY(SCREEN_HEIGHT / 2 + i * buttons_[i].getRect().h * 2);
	}

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
	return true;
}
void MainMenuState::handleFocusUp()
{
	if (state_ == MAINMENU)
	{
		if (current_button_ == Button::NEWGAME)
		{
			current_button_ =continue_available_ ? Button::CONTINUE : Button::EXIT;
		}
		else
		{
			
			current_button_ =current_button_== Button::CONTINUE?Button::EXIT:static_cast<Button::Type>(current_button_ - 1);

		}
	}
	else
	{
		if(current_button_ == Button::BACK)
			current_button_ = Button::VOLUME_SLIDER;
		else if(current_button_ == Button::VOLUME_SLIDER)
			current_button_ = Button::BACK;
	}
}
void MainMenuState::handleAdjustVolume()
{
}
void MainMenuState::handleFocusDown()
{
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
		if(current_button_ == Button::VOLUME_SLIDER)
			current_button_ = Button::BACK;
		else if(current_button_ == Button::BACK)
			current_button_ = Button::VOLUME_SLIDER;
	}
}
void MainMenuState::handleEnter()
{
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
void MainMenuState::handleEvent(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)
		{
			handleFocusUp();
		}
		else if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
		{
			handleFocusDown();
		}
		else if (e.key.keysym.sym == SDLK_RETURN)
		{
			handleEnter();
		}
	}
}
void MainMenuState::update(const float &dT)
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(background_music_, -1);
	}
	// update all regardless which state is
	current_num_buttons_ = (state_ == MAINMENU) ? NUM_OF_MAIN_MENU_BUTTONS : NUM_OF_OPTIONS_BUTTONS;
	for (int i = 0; i < current_num_buttons_; i++)
	{
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
		if (buttons_[state_ + i].getType() == current_button_)
		{
			buttons_[state_ + i].render(ren);
		}
		else
			buttons_[state_ + i].render(ren);
	}
	renderTransitionFx(ren);
}

void MainMenuState::finishGetOut()
{
	StateMachine::get()->setNextState(LoadingState::get());
}
