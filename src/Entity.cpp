#include "Entity.h"
#include "Level/Level.h"

Entity::Entity(const TileSheet& tileSheet, sf::Vector2f startingPosition)
	: m_tileSheet(tileSheet),
	m_moveDirection(Direction::Up),
	m_position(startingPosition),
	m_speed(1.f, 1.f),
	m_sprite(tileSheet.m_texture, tileSheet.getTileLocation(245))
{
	m_sprite.rotate(-90);
}

void Entity::update()
{
	switch (m_moveDirection)
	{
	case Direction::Left:
		m_position.x -= m_speed.x;
		break;
	case Direction::Right:
		m_position.x += m_speed.x;
		break;
	case Direction::Up:
		m_position.y -= m_speed.y;
		break;
	case Direction::Down:
		m_position.y += m_speed.y;
		break;

	}

	m_sprite.setPosition(m_position);
}

void Entity::draw(sf::RenderWindow & window) const
{
	window.draw(m_sprite);
}