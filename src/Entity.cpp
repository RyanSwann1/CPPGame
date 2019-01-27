#include "Entity.h"
#include "Level/Level.h"
#include <assert.h>

//Animation
Animation::Animation(int startingFrame, int endingFrame, sf::Vector2f drawLocationSize)
	: m_startingFrame(startingFrame),
	m_endingFrame(endingFrame),
	m_drawLocationSize(drawLocationSize),
	m_frameTime(0.75f),
	m_currentFrame(startingFrame)
{}

//Entity
Entity::Entity(sf::Vector2f startingPosition, const TileSheet& tileSheet, const std::unordered_map<std::string, Animation>& animations)
	: m_tileSheet(tileSheet),
	m_moveDirection(Direction::None),
	m_position(startingPosition),
	m_speed(sf::Vector2f(5.0f, 5.0f)),
	m_sprite(m_tileSheet.m_texture),
	m_animations(animations),
	m_currentAnimation(nullptr)
{
	setCurrentAnimation("Idle");
}

void Entity::move(Direction moveDirection)
{
	m_moveDirection = moveDirection;
}

void Entity::update(const std::vector<sf::FloatRect>& collisionLayer, float deltaTime)
{	
	handleMovement(collisionLayer);
	handleAnimations(deltaTime);

	//m_moveDirection = Direction::None;
	m_sprite.setPosition(m_position);

	assert(m_currentAnimation);
	sf::IntRect tileRect = m_tileSheet.getTileLocation(m_currentAnimation->m_currentFrame);
	tileRect.height = m_currentAnimation->m_drawLocationSize.y * m_tileSheet.m_tileSize;
	m_sprite.setTextureRect(tileRect);
}

void Entity::draw(sf::RenderWindow & window) const
{

	window.draw(m_sprite);
}

void Entity::handleMovement(const std::vector<sf::FloatRect>& collisionLayer)
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
}

void Entity::handleCollision(const std::vector<sf::FloatRect>& collisionLayer, sf::Vector2f& movement) const
{
	//sf::FloatRect entityAABB(m_position + movement, m_rect.getSize());
	//for (const sf::FloatRect collision : collisionLayer)
	//{
	//	sf::FloatRect intersection;
	//	if (entityAABB.intersects(collision, intersection))
	//	{
	//		if (m_moveDirection == Direction::Right || m_moveDirection == Direction::Down)
	//		{
	//			movement.x -= intersection.width;
	//			movement.y -= intersection.height;
	//		}
	//		else
	//		{
	//			movement.x += intersection.width;
	//			movement.y += intersection.height;
	//		}
	//		break;
	//	}
	//}
}

void Entity::handleAnimations(float deltaTime)
{
	switch (m_moveDirection)
	{
	case Direction::Left :
	{
		setCurrentAnimation("WalkLeft");
		break;
	}
	case Direction::Right :
	{
		setCurrentAnimation("WalkRight");
		break;
	}
	case Direction::Up :
	{
		setCurrentAnimation("WalkUp");
		break;
	}
	case Direction::Down :
	{
		setCurrentAnimation("WalkDown");
		break;
	}
	case Direction::None :
	{
		setCurrentAnimation("Idle");
		break;
	}
	}

	m_currentAnimation->m_elaspedTime += deltaTime;
	if (m_currentAnimation->m_elaspedTime >= m_currentAnimation->m_frameTime)
	{
		++m_currentAnimation->m_currentFrame;
		m_currentAnimation->m_elaspedTime = 0;
		if (m_currentAnimation->m_currentFrame == m_currentAnimation->m_endingFrame)
		{
			m_currentAnimation->m_currentFrame = m_currentAnimation->m_startingFrame;
		}
	}
}

void Entity::setCurrentAnimation(const std::string & name)
{
	auto iter = m_animations.find(name);
	assert(iter != m_animations.cend());
	m_currentAnimation = &iter->second;
}