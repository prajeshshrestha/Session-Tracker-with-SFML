#include "Button.h"



int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML ROCKS", sf::Style::Titlebar | sf::Style::Close, settings);
	window.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("Fonts/Roboto-Medium.ttf"))
		return EXIT_FAILURE;

	Button btn("Click me", { 90.f, 30.f }, { 200.f, 200.f }, font);

	sf::CircleShape shape(40.f);
	shape.setPosition({ window.getPosition().x / 2 - shape.getRadius(), window.getPosition().y / 2 - shape.getRadius() });

	srand(static_cast<unsigned>(time(NULL)));

	std::function<void()> shapeColorChange = [&]()
	{
		shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	};


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			default:
				break;
			}
			btn.btnEvents(event, window, shapeColorChange);
		}

		window.clear(sf::Color(13, 13, 39));
		window.draw(shape);
		btn.drawTo(window);
		window.display();
	}
}