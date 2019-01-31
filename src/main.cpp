#include "Level/Level.h"
#include "Level/LevelParser.h"

//https://gamedev.stackexchange.com/questions/44037/what-are-the-most-common-ai-systems-implemented-in-tower-defense-games

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 1200), "SFML_WINDOW", sf::Style::Default);
	window.setFramerateLimit(60);
	
	Level level(LevelParser::parseLevel("MapOne.tmx"));

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

		sf::IntRect mouseAABB(sf::Vector2i(sf::Mouse::getPosition(window).x - 64, sf::Mouse::getPosition(window).y - 64), sf::Vector2i(64, 64));
		sf::RectangleShape mouseRect;
		mouseRect.setSize(sf::Vector2f(64, 64));
		mouseRect.setOutlineColor(sf::Color::Red);
		mouseRect.setOutlineThickness(2.5f);
		mouseRect.setFillColor(sf::Color::Transparent);

		const std::vector<std::vector<int>>& tileLayer = level.getTileLayer().getTileLayer();
		for (int y = 0; y < level.getSize().y; ++y)
		{
			for (int x = 0; x < level.getSize().x; ++x)
			{
				sf::IntRect tileRect(sf::Vector2i(x * 64, y * 64), sf::Vector2i(64, 64));
				if (mouseAABB.intersects(tileRect))
				{
					mouseRect.setPosition(tileRect.left, tileRect.top);
				}
			}
		}


		level.update();

		//Window
		window.clear(sf::Color::Black);
		
		level.draw(window);
		window.draw(mouseRect);
		window.display();
	}

	return -1;
}