#include "header/Util.h"

bool initWindow(SDL_Window** window, SDL_Renderer** ren) {
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
		*window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			*ren = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (*ren == NULL)
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(*ren, 0xFF, 0xFF, 0xFF, 0xFF);

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
				SDL_Surface* icon = IMG_Load("assets/img/icon64x64.png");
				std::cout << IMG_GetError();

				SDL_SetWindowIcon(*window, icon);
			}
		}
	}

	return success;
}
void closeWindow(SDL_Window* window, SDL_Renderer* ren, TTF_Font* font)
{
	//Free the surfaces


	//Close the font that was used
	TTF_CloseFont(font);
	font = NULL;

	//Destroy windows
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
	window = NULL;
	ren = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}