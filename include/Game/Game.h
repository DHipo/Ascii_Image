#pragma once

#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <fstream>
#include "..\Utils.h"
#include "..\Entity\Entity.h"
#include "..\Global.h"

class Game
{
private:
	Utils::Vec2 m_windowSize;
	bool m_running;
	Uint32 m_flags;
	float m_framerate;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Surface* m_surface;
	SDL_Event* m_event;
	TTF_Font* m_font;
	std::map<SDL_Keycode, bool> m_keys;
	Utils::TimeInter m_time = { 0,0,0,	0,0,0,	0};
	Utils::MouseInfo m_mouse = { 0,0, 0, 0 };

public:
	Game();
	~Game();

	bool Init(const char* title, int xpos, int ypos, int w, int h, int maxframerate,uint32_t flags);
	bool Init();

	void HandleEvents();
	void Run();
	void Update();
	void Clear();
	void Renderer();

	void ProcessImage(const char *, bool _renderIt = true);
	void displayText(const std::string, const Utils::Vec2, const Utils::Vec2);

	inline bool GetRunningState() {return m_running;}
	inline SDL_Window* GetWindow() {return m_window;}

};