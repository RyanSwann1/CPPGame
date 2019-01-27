#include "Entity.h"

Entity::Entity(sf::Vector2f startingPosition, sf::Vector2f speed, sf::Vector2f size, Direction moveDirection)
	: m_moveDirection(moveDirection),
	m_position(startingPosition),
	m_speed(speed),
	m_rect(size)
{
	m_rect.setFillColor(sf::Color::Red);
	m_rect.setPosition(startingPosition);
}

void Entity::move(Direction moveDirection)
{
	m_moveDirection = moveDirection;
}

void Entity::update()
{	
	switch (m_moveDirection)
	{
	case Direction::Left:
	{
		m_position.x -= m_speed.x;
		break;
	}
	case Direction::Right:
	{
		m_position.x += m_speed.x;
		break;
	}
	case Direction::Up:
	{
		m_position.y -= m_speed.y;
		break;
	}
	case Direction::Down:
	{
		m_position.y += m_speed.y;
		break;
	}
	}
	
	m_moveDirection = Direction::None;
	m_rect.setPosition(m_position);
}

void Entity::draw(sf::RenderWindow & window) const
{
	window.draw(m_rect);
}
