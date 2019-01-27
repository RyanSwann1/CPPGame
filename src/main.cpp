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
	Entity player(sf::Vector2f(150, 150), sf::Vector2f(5, 5), sf::Vector2f(16, 16));

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

		player.update();
		
		//Window
		window.clear(sf::Color::Black);
		level.draw(window);
		player.draw(window);
		window.display();
	}

	return -1;
}