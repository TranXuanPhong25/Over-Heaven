#include "header/Game.h"
Game::Game() :window_(NULL), ren_(NULL) {
	p_game_state_ = new StateMachine();
}
Game::~Game() {
	delete p_game_state_;

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

				SDL_SetWindowIcon(window_, IMG_Load("assets/img/icon64x64.png"));
			}
		}
	}

	return success;
}
void Game::run() {
	if (initWindow()) {
		player_.loadTexture(ren_, NUNU_TEXTURE_PATH_64X91);
		player_.setRect(INIT_POS_X, INIT_POS_Y);
		p_game_state_->getCurrentState()->enter();
		Timer FPS;
		FPS.start();
		Uint32 preFrame = FPS.getTicks();
		Uint32 curFrame;
		SDL_Event e;
		while (p_game_state_->getCurrentState() != ExitState::get()) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					p_game_state_->setNextState(ExitState::get());
					break;
				}
				p_game_state_->getCurrentState()->handleEvent(e);
				player_.handleInput(e);
			}
			player_.move(0.01667f);

			p_game_state_->getCurrentState()->update();
			p_game_state_->changeState();

			SDL_RenderClear(ren_);
			player_.render(ren_);
			SDL_RenderPresent(ren_);

			curFrame = FPS.getTicks();
			Uint32 delta = 50 - (curFrame - preFrame);
			/*if (delta > 0) {
				SDL_Delay(35);
			}*/
			preFrame = curFrame;
		}
	}
}