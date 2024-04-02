#include "Game.h"
Game::Game() :window_(NULL), ren_(NULL) {
	state_machine_ = StateMachine::get();
	state_machine_->setInitialState(IntroState::get());
}
Game::~Game() {

	SDL_DestroyRenderer(ren_);
	SDL_DestroyWindow(window_);
	window_ = NULL;
	ren_ = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
bool Game::initWindow() {
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize!SDL Error : " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
		}

		//Create window
		window_ = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window_ == NULL)
		{
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			SDL_SetWindowIcon(window_, IMG_Load("assets/img/icon64x64.png"));
			//SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
			//Create vsynced renderer for window
			ren_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (ren_ == NULL)
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
					success = false;
				}

			}
		}
	}

	return success;
}
void Game::run() {
	if (initWindow()) {

		state_machine_->getCurrentState()->enter(ren_);
		Timer FPS;
		FPS.start();
		Uint32 preFrame = FPS.getTicks();
		Uint32 curFrame;
		float dT = TARGET_TIMESTEP;
		SDL_Event e;
		while (state_machine_->getCurrentState() != ExitState::get()) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					state_machine_->setNextState(ExitState::get());
					break;
				}
				state_machine_->getCurrentState()->handleEvent(e);

			}

			curFrame = FPS.getTicks();
			dT = (curFrame - preFrame);
			if (dT < TARGET_TIMESTEP) {
				SDL_Delay(TARGET_TIMESTEP - dT);
			}
			preFrame = curFrame;
			state_machine_->getCurrentState()->update(dT / 1000.f);
			state_machine_->changeState(ren_);

			SDL_RenderClear(ren_);
			state_machine_->getCurrentState()->render(ren_);
			SDL_RenderPresent(ren_);


		}
	}
}