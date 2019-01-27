#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include <unordered_map>
#include <string>

struct Animation
{
	Animation(int startingFrame, int endingFrame, sf::Vector2f drawLocationSize);

	const int m_startingFrame;
	const int m_endingFrame;
	const sf::Vector2f m_drawLocationSize;
	const float m_frameTime;
	float m_elaspedTime;
	int m_currentFrame;
};

enum class Direction
{
	Left = 0,
	Right,
	Up,
	Down,
	None
};

struct TileSheet;
class Entity
{
public:
	Entity(sf::Vector2f startingPosition, const TileSheet& tileSheet, const std::unordered_map<std::string, Animation>& animations);

	void move(Direction moveDirection);
	void update(const std::vector<sf::FloatRect>& collisionLayer, float deltaTime);
	void draw(sf::RenderWindow& window) const;

private:
	const TileSheet& m_tileSheet;
	Direction m_moveDirection;
	sf::Vector2f m_position;
	sf::Vector2f m_speed;
	sf::Sprite m_sprite;
	std::unordered_map<std::string, Animation> m_animations;
	Animation* m_currentAnimation;


	void handleMovement(const std::vector<sf::FloatRect>& collisionLayer);
	void handleCollision(const std::vector<sf::FloatRect>& collisionLayer, sf::Vector2f& movement) const;
	void handleAnimations(float deltaTime);
	void setCurrentAnimation(const std::string& name);
};