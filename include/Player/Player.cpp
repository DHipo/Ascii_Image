#include "Player.h"

Player::Player(SDL_Rect _rect, const char* _path, int _health)
	: Entity(_rect, _path)
{
	
}

void Player::Update (const Utils::TimeInter& _time)
{
	velocityUpdate(_time);
	if (m_mouse.button == SDL_BUTTON_LEFT) doAtack();
}

void Player::Draw(SDL_Renderer* _renderer)
{	
	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	SDL_RenderFillRectF(_renderer, &m_rect);
}

void Player::velocityUpdate(const Utils::TimeInter& _time) 
{
	m_velocity.y += -1.2 * int(m_velocity.y > 0) + 1.2 * int(m_velocity.y < 0);
	m_velocity.x += -1.2 * int(m_velocity.x > 0) + 1.2 * int(m_velocity.x < 0);

	m_velocity.y += m_aceleration.y * 2.5 * -((int)(*this->m_keys)[119])
		+ m_aceleration.y * 2.5 * (int)(*this->m_keys)[115];

	m_velocity.x += m_aceleration.x * 2 * -((int)(*this->m_keys)[97])
		+ m_aceleration.x * 2 * (int)(*this->m_keys)[100];
	
	m_rect.x += (m_velocity.x * _time.deltaTime);
	m_rect.y += (m_velocity.y * _time.deltaTime);
}

void Player::doAtack() 
{
	std::cout << m_mouse.pos.x << " | " << m_mouse.pos.y << std::endl;
}