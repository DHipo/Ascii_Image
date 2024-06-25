#define SDL_MAIN_HANDLED
#include "..\include\Game\Game.h"

int main(int argc, char** argv)
{
	Game app;
	if ( app.Init(
		"Template", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		DEFAULTSIZE_WIDTH, 
		DEFAULTSIZE_HEIGTH, 
		220, 
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED
		)
	)
	{
		app.ProcessImage(URL_ASSETS "/img/agus.png", true);
		app.Run();
	}
	return 0;

}