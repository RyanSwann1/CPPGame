#include "Level/Level.h"
#include "Level/LevelParser.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML_WINDOW", sf::Style::Default);
	Level level(LevelParser::parseLevel("MapTwo.tmx"));
	
	while (window.isOpen())
	{
		sf::Event sfmlEvent;
		while (window.pollEvent(sfmlEvent))
		{
			if (sfmlEvent.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		level.draw(window);
		window.display();
	}

	return -1;
}