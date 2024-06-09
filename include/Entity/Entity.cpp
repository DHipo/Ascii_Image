#include "Entity.h"

Entity::Entity(SDL_Rect _rect, const char* _path)
{
	m_rect.x = _rect.x;
	m_rect.y = _rect.y;
	m_rect.w = _rect.w;
	m_rect.h = _rect.h;
	this->m_image = IMG_Load(_path);
}

Entity::~Entity() 
{
}

void Entity:: Update(const Utils::TimeInter&)
{
	m_rect.x += 1;
}

void Entity::Draw(SDL_Renderer* _renderer)
{
}

void Entity::setPosition() 
{
}