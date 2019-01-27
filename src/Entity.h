#pragma once

#include "SFML/Graphics.hpp"
#include <vector>

enum class Direction
{
	Left = 0,
	Right,
	Up,
	Down,
	None
};

class Entity
{
public:
	Entity(sf::Vector2f startingPosition, sf::Vector2f speed, sf::Vector2f size, Direction moveDirection = Direction::None);

	void move(Direction moveDirection);
	void update(const std::vector<sf::FloatRect>& collisionLayer);
	void draw(sf::RenderWindow& window) const;

private:
	Direction m_moveDirection;
	sf::Vector2f m_position;
	sf::Vector2f m_speed;
	sf::RectangleShape m_rect;

	void handleCollision(const std::vector<sf::FloatRect>& collisionLayer, sf::Vector2f& movement) const;
};