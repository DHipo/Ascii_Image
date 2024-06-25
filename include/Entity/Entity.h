#pragma once
#include <SDL2/sdl.h>
#include "..\Utils.h"
#include <SDL2/SDL_image.h>
#include <iostream>

class Entity
{
public:
	Entity(SDL_Rect, const char *);
	~Entity();

	virtual void Draw(SDL_Renderer*);
	virtual void Update(const Utils::TimeInter&);
	
	SDL_FRect* getPointerOfRect() { return &m_rect; };
	void setPosition();

protected:
	SDL_FRect m_rect;
	SDL_Surface * m_image;
};

