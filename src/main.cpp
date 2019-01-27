#include "Level/Level.h"
#include "Level/LevelParser.h"
#include "Entity.h"

void handleInput(const sf::Event& sfmlEvent, Entity& player)
{
	switch (sfmlEvent.key.code)
	{
	case sf::Keyboard::A :
	{
		player.move(Direction::Left);
		break;
	}
	case sf::Keyboard::D :
	{
		player.move(Direction::Right);
		break;
	}
	case sf::Keyboard::W :
	{
		player.move(Direction::Up);
		break;
	}
	case sf::Keyboard::S :
	{
		player.move(Direction::Down);
		break;
	}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML_WINDOW", sf::Style::Default);
	window.setFramerateLimit(60);
	Level level(LevelParser::parseLevel("MapTwo.tmx"));
	sf::Time frameTime;
	sf::Clock gameClock;

	std::unordered_map<std::string, Animation> animations;
	animations.emplace(std::string("Idle"), Animation(0, 0, sf::Vector2f(1, 2)));
	animations.emplace(std::string("WalkDown"), Animation(0, 3, sf::Vector2f(1, 2)));
	animations.emplace(std::string("WalkRight"), Animation(34, 37, sf::Vector2f(1, 2)));
	animations.emplace(std::string("WalkUp"), Animation(68, 71, sf::Vector2f(1, 2)));
	animations.emplace(std::string("WalkLeft"), Animation(102, 105, sf::Vector2f(1, 2)));
	Entity player(sf::Vector2f(150, 150), level.getTileSheet("Player"), animations);

	while (window.isOpen())
	{
		sf::Event sfmlEvent;
		while (window.pollEvent(sfmlEvent))
		{
			if (sfmlEvent.type == sf::Event::Closed)
			{
				window.close();
			}
			handleInput(sfmlEvent, player);
		}

		player.update(level.getCollisionLayer(), frameTime.asSeconds());
		
		//Window
		window.clear(sf::Color::Black);
		level.draw(window);
		player.draw(window);
		window.display();

		frameTime = gameClock.restart();
	}

	return -1;
}