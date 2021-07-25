#include "SFML/Graphics.hpp"
#include "Btn.h"
#include "Session.h"
#include <stdc++.h>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::VideoMode video_mode;
	video_mode.width = 760;
	video_mode.height = 675;
	sf::RenderWindow window(video_mode, "SESSION", sf::Style::Titlebar | sf::Style::Close, settings);
	sf::Event event;

	sf::Font font;
	if (!font.loadFromFile("Fonts/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium.ttf'";


	Record record(font);
	record.Set_Text("Something");
	record.Set_Rect_Position({ 20.f, 200.f });


	
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::White);

		record.Draw_To(window);

		window.display();
	}

	return EXIT_SUCCESS;
}
