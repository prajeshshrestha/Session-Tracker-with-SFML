#include "inputField.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(740, 560), "SFML WORKS", sf::Style::Titlebar | sf::Style::Close, settings);
	sf::Event event;
	sf::Vector2f winSize = static_cast<sf::Vector2f>(window.getSize());
	
	sf::Font font;
	if (!font.loadFromFile("Font/Roboto-Medium.ttf"))
		throw "Error in loading 'Roboto-Medium.ttf' font";


	InputField field({ winSize.x / 2, 80.f }, font);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

			}
			field.InputEvent(window, event);
		}

		window.clear(sf::Color(23, 137, 252));
		field.DrawTo(window);
		window.display();
	}
}