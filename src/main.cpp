#define SDL_MAIN_HANDLED
#include "..\include\Game\Game.h"

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		std::cout << "No se ha pasado un path de la imagen como argumento.\n"
				<< "Por favor ejecute make IMAGE_NAME={direccion de la imagen} run.\n"
				<< "Tener en cuenta que la imagen debe estar en el directorio ./assets/img\n";
		return 0;
	}

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

		std::string path(URL_ASSETS "img/");
		path.append(argv[1]);
		app.ProcessImage(path.c_str(), true);
		app.Run();
	}
	return 0;

}