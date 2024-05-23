#include "core/Game.hpp"
int main(int argc, char *argv[])
{
	Game game;
	try
	{
		game.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << SDL_GetError() << std::endl;
	}
	return 0;
}