#include "Game.h"

Game::Game() { std::cout << "Game object created. Now you must initialize it with the init method." << std::endl; }
Game::~Game() { std::cout << "Game object destruct" << std::endl; }

bool Game::Init(const char *title, int xpos, int ypos, int w, int h, int _FrameRate, uint32_t flags)
{
	bool status = true;
	std::cout << "Initializing sub-systems" << std::endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		LOG_ERROR(SDL_GetError());
		status = false;
	}

	std::cout << "Creating window..." << std::endl;
	m_window = SDL_CreateWindow(title, xpos, ypos, w, h, flags);
	if (!m_window)
	{
		status = false;
		LOG_ERROR("Failed creating window...");
	}

	std::cout << "Creating renderer..." << std::endl;
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_renderer)
	{
		status = false;
		LOG_ERROR("Failed creating renderer...");
	}

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	std::cout << "Creating surface..." << std::endl;
	m_surface = SDL_GetWindowSurface(m_window);
	if (!m_surface)
	{
		status = false;
		LOG_ERROR("Failed creating surface...");
	}

	std::cout << "Intializing text system..." << std::endl;
	if (TTF_Init() < 0)
	{
		status = false;
		LOG_ERROR("TTF initialization failed. ");
	}

	m_font = TTF_OpenFont("./res/fonts/HackRegularNerdFontCompleteMono.ttf", 24);
	if (!m_font)
		LOG_ERROR("Failed to open font.");

	// Declarations
	g_player = new Player({50, 50, 100, 100}, "./Assets/Ogro/Sprite_0.png", 1000);

	std::cout << "Loading Textures..." << std::endl;
	
	// All passed
	std::cout << "----------- ALL DONE -----------" << std::endl;
	m_event = new SDL_Event();

	m_framerate = 1000.0f / _FrameRate;
	m_running = status;
	return status;
};

void Game::ProcessImage(const char * _path, bool _renderIt)
{
	SDL_Surface * image = IMG_Load(_path);

	if (!image)
	{
		LOG_ERROR("Failed loading textures...");
		return;
	}

	SDL_PixelFormat *fmt = image->format;
	Uint32 temp = 0;
	if (fmt->BitsPerPixel != 8)
		fprintf(stderr, "Not an 8-bit surface.\n");

	std::string letters = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft|()1{}[]?-_+~<>i!lI;:,^`'. _-. ";
	
	//Create file with image
	std::ofstream file("./bin/output.txt");

	std::cout << (int)fmt->BytesPerPixel << " Bytes\n";
	SDL_LockSurface(image);

	for (int y = 0; y < image->h; y ++)
	{
		for (int x = 0; x < image->w; x ++)
		{
			Uint32 *pixel = (Uint32 *)((Uint8*) image->pixels + y * image->pitch + x * fmt->BytesPerPixel);

			Uint8 red	= *pixel & fmt->Rmask;
			Uint8 green = *pixel & fmt->Gmask;
			Uint8 blue 	= *pixel & fmt->Bmask;
			Uint8 alpha = *pixel & fmt->Amask;

			int promedio = Utils::promedio(std::vector<int>{red, green, blue});
			
			if (promedio > 0) *pixel = SDL_MapRGBA(fmt, promedio, promedio, promedio, 200);

			file << letters[Utils::map_value(promedio, 0, 255, letters.size(), 0)];
		}
		file << "\n";
	}

	file.close();
	if(_renderIt)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, image);
		SDL_RenderCopy(m_renderer, texture, NULL, NULL);
		SDL_RenderPresent(m_renderer);
	}

	SDL_UnlockSurface(image);
}

// Manejador de eventos
void Game::HandleEvents()
{
	SDL_PollEvent(m_event);

	switch (m_event->type)
	{
	case SDL_QUIT:
		m_running = false;
		break;
	case SDL_KEYDOWN:
		m_keys[m_event->key.keysym.sym] = true;
		SDL_Log("%c", m_event->key.keysym.sym);
		break;
	case SDL_KEYUP:
		m_keys[m_event->key.keysym.sym] = false;
		break;
	case SDL_MOUSEMOTION:
		m_mouse.pos = {m_event->motion.x, m_event->motion.y};
		break;
	case SDL_MOUSEBUTTONDOWN:
		m_mouse.button = m_event->button.button;
		break;
	case SDL_MOUSEBUTTONUP:
		m_mouse.button = 0;
		break;
	default:
		break;
	}

	g_player->setMousePosition(m_mouse);
	g_player->setKeys(m_keys);
}

/// @brief Display objects on the screen
/// @param none
/// @returns nothing
void Game::Renderer()
{
	//SDL_RenderClear(m_renderer);
	// Add stuff to render

	//SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
	SDL_RenderPresent(m_renderer);
}

/// @brief Clear the main objects and quit the program with a output message.
/// @param none
/// @returns nothing
void Game::Clear()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	TTF_CloseFont(m_font);
	TTF_Quit();
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

/// @brief  Function to update the all things that must update.
/// @param none
/// @returns nothing
void Game::Update()
{
}

///	Main while of the game
/// @param none
/// @returns nothing
void Game::Run()
{

	while (m_running)
	{
		m_time.p_start = SDL_GetPerformanceCounter();
		m_time.t_start = SDL_GetTicks();

		this->HandleEvents();
		m_time.deltaTime = double(m_time.t_start - m_time.t_end) / 1000.f;

		this->Update();
		this->Renderer();
		m_time.p_end = SDL_GetPerformanceCounter();
		m_time.p_elapsed = m_time.p_end - m_time.p_start;

		m_time.t_end = SDL_GetTicks();
		m_time.t_elapsed = m_time.t_end - m_time.t_start;
		m_time.deltaTime = float(m_time.t_elapsed) / 1000.f;

		if (m_framerate > m_time.t_elapsed)
		{
			SDL_Delay(floor(m_framerate - m_time.t_elapsed));
		}

		//SDL_Log("DELTA TIME: %f", m_time.deltaTime);
	}

	this->Clear();
}

void Game::displayText(const std::string _text, const Utils::Vec2 _position, const Utils::Vec2 _size)
{
	SDL_Surface *text = TTF_RenderText_Solid(m_font, _text.c_str(), {0, 0, 0, 255});
	if (!text)
		return;

	SDL_Texture *text_texture = SDL_CreateTextureFromSurface(m_renderer, text);

	SDL_RenderCopy(m_renderer, text_texture, NULL, new SDL_Rect{_position.x, _position.y, (int)_text.size() * FONT_SIZE, _size.y});
}