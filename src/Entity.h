#pragma once

#include <SFML/Graphics.hpp>


enum class Direction
{
	Left = 0,
	Right,
	Up,
	Down
};

class TileSheet;
class Entity
{
public:
	Entity(const TileSheet& tileSheet, sf::Vector2f startingPosition);

	void update();
	void draw(sf::RenderWindow& window) const;

private:
	const TileSheet& m_tileSheet;
	Direction m_moveDirection;
	sf::Vector2f m_position;
	sf::Vector2f m_speed;
	sf::Sprite m_sprite;
};