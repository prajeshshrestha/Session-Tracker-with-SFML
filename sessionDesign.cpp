#include "SFML/Graphics.hpp"
#include <stdc++.h>
#include "Btn.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(740, 560), "Session", sf::Style::Default, settings);
	sf::Event event;

	// Window component
	sf::Vector2u winSize = window.getSize();
	sf::Vector2f winSizeF = static_cast<sf::Vector2f>(winSize);
	sf::Vector2f winCenter({ winSizeF.x / 2, winSizeF.y / 2 });

	//Background thingy
	sf::Texture bgImageTex, bgStopTex;
	if (!bgImageTex.loadFromFile("Texture/bgImageText.png"))
		throw "Error in loading the 'bgImageText'";

	if (!bgStopTex.loadFromFile("Texture/stopTimer.png"))
		throw "Error in loading the 'stopTimer.png'";
	sf::Sprite bgImage, bgStopImage;
	bgImage.setTexture(bgImageTex);
	bgImage.setPosition({ 0.f, 0.f });
	bgStopImage.setTexture(bgStopTex);
	bgStopImage.setPosition({ 0.f, -200.f });

	//UI font 
	sf::Font font;
	if (!font.loadFromFile("Font/KaushanScript-Regular.ttf"))
		throw "Error in loading 'Roboto-Medium.ttf";
	sf::Text uiText("Session Name", font, 30);

	uiText.setPosition({ winCenter.x - uiText.getGlobalBounds().width / 2, 50.f });
	uiText.setFillColor(sf::Color::White);

	// Design Circle 
	sf::CircleShape circle(8.f);
	circle.setOrigin({ 8.f, 8.f });
	circle.setFillColor(sf::Color(8, 218, 145));
	circle.setPosition({ uiText.getGlobalBounds().left - circle.getRadius() * 2, uiText.getGlobalBounds().top + uiText.getGlobalBounds().height / 2 });

	// Button component
	sf::Font robotoFont;
	if (!robotoFont.loadFromFile("Font/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium.ttf'";

	sf::Color startColor(24, 171, 14);
	sf::Color stopColor(247, 12, 55);

	Btn* startBtn = new Btn("Start Session", { winCenter.x, bgImage.getGlobalBounds().height }, 16, robotoFont);
	startBtn->SetFillColor(startColor);
	startBtn->text.setFillColor(sf::Color::White);
	bool btnColorToggle = false;

	// all about the timer
	sf::Clock clock;
	float t1;
	float t2;
	int seconds = 0;
	bool timerOn = false; // timer thingy

	sf::Text time;
	time.setFont(robotoFont);
	time.setFillColor(sf::Color::Black);
	time.setPosition({ winCenter.x, winCenter.y });
	std::string timeToStr;


	auto testFunc = [&]()
	{
		if (!btnColorToggle)
		{
			startBtn->SetFillColor(stopColor);
			startBtn->text.setString("Stop Session");
			clock.restart();
			timerOn = true;
			bgStopImage.setPosition({0.f, 0.f});
			bgImage.setPosition({ 0.f, -200.f });
			startBtn->SetBtnPosition({ winCenter.x, bgStopImage.getGlobalBounds().height });
		}
		else
		{
			startBtn->SetFillColor(startColor);
			startBtn->text.setString("Start Session");
			timerOn = false;
			bgImage.setPosition({ 0.f, 0.f });
			bgStopImage.setPosition({ 0.f, -200.f });
			startBtn->SetBtnPosition({ winCenter.x, bgImage.getGlobalBounds().height });
	
		}
		btnColorToggle = !btnColorToggle;
		
	};

	bool smthng = false;

	

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		startBtn->BtnEvents(window, event, testFunc, smthng);

		if (timerOn)
		{
			t1 = clock.getElapsedTime().asSeconds();
			t2 = clock.getElapsedTime().asMilliseconds();
			if (t1 > 1.f)
			{
				seconds += 1;
				clock.restart();
				std::cout << seconds / 3600 << ":" << (seconds / 60) % 60 << ":" << seconds % 60;
				
			}
			timeToStr = "0" + std::to_string(seconds / 3600) + ":" + "0"
				+ std::to_string((seconds / 60) % 60) + ":" + std::to_string(seconds % 60) + "." + std::to_string(int(t2 / 10));
			std::cout << int(t2 / 10) << std::endl;
			time.setString(timeToStr);
		}
		

		window.clear(sf::Color::White);

		window.draw(bgImage);
		window.draw(bgStopImage);
		window.draw(uiText);
		window.draw(circle);
		startBtn->DrawTo(window);
		window.draw(time);
		window.display();
	}
}