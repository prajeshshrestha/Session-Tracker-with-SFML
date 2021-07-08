#include "Btn.h"
#include "SFML/Graphics.hpp"
#include "InputField.h"


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


	// Testing the button 
	Btn *btn;
	btn = new Btn("Clear", { winCenter.x, winCenter.y + 50.f}, 14, font);


	// Testing the inputfield
	InputField input(winCenter, font);


	 
	srand(static_cast<unsigned>(time(NULL)));
	auto changeInput = [&]()
	{
		input.bufferString = "";
		input.inputText = "";
		input.SetText("");
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
			input.InputEvent(window, event);
		}
		btn->BtnEvents(window, event, changeInput);
		

		
		
		window.clear(sf::Color(23, 137, 252));
		btn->DrawTo(window);
		input.DrawTo(window);
		window.display();
	}
}