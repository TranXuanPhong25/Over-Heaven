#include "Game.hpp"
Game::Game() : window_(NULL), ren_(NULL)
{
	state_machine_ = StateMachine::get();
	state_machine_->setInitialState(IntroState::get());
	curFrame = 0;
	preFrame = 0;
	time_step_ = TARGET_TIMESTEP;
}
Game::~Game()
{

	SDL_DestroyRenderer(ren_);
	SDL_DestroyWindow(window_);
	window_ = NULL;
	ren_ = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
bool Game::initWindow()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	window_ = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
	if (window_ == NULL)
	{
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_ShowCursor(SDL_DISABLE);

	ren_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren_ == NULL)
	{
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if (SDL_RenderSetLogicalSize(ren_, SCREEN_WIDTH, SCREEN_HEIGHT) != 0)
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

	return success;
}

void Game::run()
{
	if (initWindow())
	{
		state_machine_->getCurrentState()->enter(ren_);
		preFrame = SDL_GetTicks64();
		SDL_Event e;
		while (state_machine_->getCurrentState() != ExitState::get())
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
			state_machine_->setNextState(ExitState::get());
			break;
		}
		state_machine_->getCurrentState()->handleEvent(e);
	}

	state_machine_->changeState(ren_);
	curFrame = SDL_GetTicks64();
	time_step_ = static_cast<float>(curFrame - preFrame);
	if (time_step_ < TARGET_TIMESTEP)
	{
		SDL_Delay(static_cast<Uint32>(TARGET_TIMESTEP - time_step_));
	}
	else
	{
		time_step_ = TARGET_TIMESTEP;
	}
	preFrame = curFrame;

	state_machine_->getCurrentState()->update(time_step_ / 1000.0f);

	SDL_RenderClear(ren_);
	state_machine_->getCurrentState()->render(ren_);
	SDL_RenderPresent(ren_);
}