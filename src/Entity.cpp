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

void Entity::update(const std::vector<sf::FloatRect>& collisionLayer)
{	
	switch (m_moveDirection)
	{
	case Direction::Left:
	{
		sf::Vector2f movement = sf::Vector2f(-m_speed.x, 0);
		handleCollision(collisionLayer, movement);
		m_position.x += movement.x;
		break;
	}
	case Direction::Right:
	{
		sf::Vector2f movement = sf::Vector2f(m_speed.x, 0);
		handleCollision(collisionLayer, movement);
		m_position.x += movement.x;
		break;
	}
	case Direction::Up:
	{
		sf::Vector2f movement = sf::Vector2f(0, -m_speed.y);
		handleCollision(collisionLayer, movement);
		m_position.y += movement.y;
		break;
	}
	case Direction::Down:
	{
		sf::Vector2f movement = sf::Vector2f(0, m_speed.y);
		handleCollision(collisionLayer, movement);
		m_position.y += movement.y;
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

void Entity::handleCollision(const std::vector<sf::FloatRect>& collisionLayer, sf::Vector2f& movement) const
{
	sf::FloatRect entityAABB(m_position + movement, m_rect.getSize());
	for (const sf::FloatRect collision : collisionLayer)
	{
		sf::FloatRect intersection;
		if (entityAABB.intersects(collision, intersection))
		{
			if (m_moveDirection == Direction::Right || m_moveDirection == Direction::Down)
			{
				movement.x -= intersection.width;
				movement.y -= intersection.height;
			}
			else
			{
				movement.x += intersection.width;
				movement.y += intersection.height;
			}
			break;
		}
	}
}
