#include "Game.hpp"
Game::Game() : p_window_(NULL), p_ren_(NULL)
{
	p_state_machine_ = StateMachine::get();
	p_state_machine_->setInitialState(IntroState::get());
	cur_frame_ = 0;
	pre_frame_ = 0;
	time_step_ = TARGET_TIMESTEP;
	time_step_seconds_ = TARGET_TIMESTEP / 1000.0f;
}
Game::~Game()
{

	SDL_DestroyRenderer(p_ren_);
	SDL_DestroyWindow(p_window_);
	p_window_ = NULL;
	p_ren_ = NULL;
	
	// Quit SDL subsystems
	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}
bool Game::initWindow()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	p_window_ = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
	if (p_window_ == NULL)
	{
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_ShowCursor(SDL_DISABLE);

	p_ren_ = SDL_CreateRenderer(p_window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (p_ren_ == NULL)
	{
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if (SDL_RenderSetLogicalSize(p_ren_, SCREEN_WIDTH, SCREEN_HEIGHT) != 0)
	{
		std::cerr << "SDL_RenderSetLogicalSize Error: " << SDL_GetError() << std::endl;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	return success;
}

void Game::run()
{
	if (initWindow())
	{
		p_state_machine_->getCurrentState()->enter(p_ren_);
		pre_frame_ = SDL_GetTicks64();
		SDL_Event e;
		while (p_state_machine_->getCurrentState() != ExitState::get())
		{
			launchGameLoop(e);
		}
	}
}
void Game::launchGameLoop(SDL_Event& e)
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			p_state_machine_->setNextState(ExitState::get());
			break;
		}
		p_state_machine_->getCurrentState()->handleEvent(e);
	}

	p_state_machine_->changeState(p_ren_);

	cur_frame_ = SDL_GetTicks64();
	time_step_ = static_cast<float>(cur_frame_ - pre_frame_);
	if (time_step_ < TARGET_TIMESTEP)
	{
		SDL_Delay(static_cast<Uint32>(TARGET_TIMESTEP - time_step_));
	}
	else
	{
		time_step_ = TARGET_TIMESTEP;
	}
	pre_frame_ = cur_frame_;
	time_step_seconds_ = time_step_ / 1000.0f;

	p_state_machine_->getCurrentState()->update(time_step_seconds_);

	SDL_RenderClear(p_ren_);
	p_state_machine_->getCurrentState()->render(p_ren_);
	SDL_RenderPresent(p_ren_);
}