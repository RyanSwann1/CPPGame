#include "SFML/Window.hpp"

int main()
{
	sf::Window window(sf::VideoMode(640, 480), "SFML_WINDOW", sf::Style::Default);
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
	}

	return -1;
}