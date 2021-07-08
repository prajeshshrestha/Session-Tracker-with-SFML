//#include "Btn.h"
#include "SFML/Graphics.hpp"


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(740, 560), "Button", sf::Style::Default, settings);


	sf::Vector2f winCenter;
	winCenter.x = window.getSize().x / 2.f;
	winCenter.y = window.getSize().y / 2.f;

	sf::Font font;
	if (!font.loadFromFile("Font/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium' font";

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setString("I don't have any idea");
	text.setPosition({ 400.f,400.f });

	// Testing the button 
	/*Btn *btn;
	btn = new Btn("Santosh Pandey", { winCenter.x, winCenter.y }, font);*/

	sf::RectangleShape rect;
	rect.setSize({ 300.f, 30.f });
	rect.setOrigin({ 150.f, 15.f });
	rect.setPosition({ winCenter.x ,winCenter.y - 200.f });

	 
	srand(static_cast<unsigned>(time(NULL)));
	auto rectColorChange = [&]()
	{
		rect.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
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
			}
	
		}
		//btn.BtnEvents(window, event, rectColorChange);

		
		
		window.clear(sf::Color(23, 137, 252));
		window.draw(text);
		/*btn->DrawTo(window);*/
		window.draw(rect);
		window.display();
	}
}