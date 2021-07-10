#include "SFML/Graphics.hpp"
#include <stdc++.h>
#include "Btn.h"
#include <ctime>
#include <chrono>
#include <time.h>

class Record
{
	public:
		sf::RectangleShape rect;
		sf::CircleShape Cleft, Cright;
		sf::Font font;
		sf::Text timeT;
		sf::Text durationT;
		sf::Text dayT;
		std::vector<std::string> recordData;
		sf::Vector2f rectPos;
		sf::FloatRect rectBounds;
		sf::FloatRect timeTBounds;
		sf::FloatRect durationTBounds;

		
		Record(sf::Font& f)
		{
			this->font = f;
			this->timeT.setFont(f);
			this->timeT.setCharacterSize(16);
			this->durationT.setCharacterSize(16);
			this->durationT.setFont(f);
			this->dayT.setFont(f);
			this->dayT.setCharacterSize(16);

			this->rect.setSize({700.f, 30.f});
			this->rect.setOrigin({ 350, 15.f });

			this->Cleft.setRadius(15.f);
			this->Cright.setRadius(15.f);
			this->Cleft.setOrigin({ 15.f, 15.f });
			this->Cright.setOrigin({ 15.f, 15.f });
		}

		void SetText(std::vector<std::string> data)
		{
			this->recordData = data;
			this->timeT.setString(this->recordData[0]);
			this->durationT.setString(this->recordData[1]);
			this->timeT.setFillColor(sf::Color::Black);
			this->durationT.setFillColor(sf::Color::Black);

			this->rect.setFillColor(sf::Color(200, 200, 200));
			this->Cleft.setFillColor(sf::Color(200, 200, 200));
			this->Cright.setFillColor(sf::Color(200, 200, 200));

			this->timeT.setOrigin({ this->timeT.getGlobalBounds().width / 2, this->timeT.getGlobalBounds().height / 2 });
			this->durationT.setOrigin({ this->durationT.getGlobalBounds().width / 2, this->durationT.getGlobalBounds().height / 2 });

			this->timeT.setPosition({ this->rectPos.x - timeT.getGlobalBounds().width, this->rectPos.y - this->timeT.getGlobalBounds().height / 3 });
			this->durationT.setPosition({ 700.f - durationT.getGlobalBounds().width, this->rectPos.y - this->timeT.getGlobalBounds().height / 3 });
			
		}

		// Overloaded
		void SetText(std::string data)
		{
			this->dayT.setString(data);
			this->dayT.setFillColor(sf::Color::White);
			std::cout << "What happened" << std::endl;
			this->rect.setFillColor(sf::Color::Black);
			this->Cleft.setFillColor(sf::Color::Black);
			this->Cright.setFillColor(sf::Color::Black);

			this->dayT.setOrigin({ this->dayT.getGlobalBounds().width / 2, this->dayT.getGlobalBounds().height / 2 });
			this->dayT.setPosition({ 50.f, this->rectPos.y - this->timeT.getGlobalBounds().height / 4 });
		}
		

		void SetRectPosition(sf::Vector2f pos)
		{
			this->rect.setPosition(pos);
			this->rectBounds = this->rect.getGlobalBounds();
			this->rectPos = this->rect.getPosition();
	
			this->Cleft.setPosition({rectBounds.left, rectBounds.top + rectBounds.height/2});
			this->Cright.setPosition({ rectBounds.left + rectBounds.width, rectBounds.top + rectBounds.height / 2 });

		}
		
		void DrawTo(sf::RenderWindow& window)
		{
			window.draw(this->rect);
			window.draw(this->Cleft);
			window.draw(this->Cright);
			window.draw(this->timeT);
			window.draw(this->durationT);
			window.draw(this->dayT);
		}
};


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
	sf::Text uiText("Engineering", font, 30);

	// The SESSION NAME
	uiText.setPosition({ winCenter.x - uiText.getGlobalBounds().width / 2, 35.f });
	uiText.setFillColor(sf::Color::White);

	// Design Circle 
	sf::CircleShape circle(6.f);
	circle.setOrigin({ 6.f, 6.f });
	circle.setFillColor(sf::Color(8, 218, 145));
	circle.setPosition({ uiText.getGlobalBounds().left - circle.getRadius() * 2, uiText.getGlobalBounds().top + uiText.getGlobalBounds().height / 2 });

	// Button component
	sf::Font robotoFont;
	if (!robotoFont.loadFromFile("Font/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium.ttf'";

	sf::Color startColor(24, 171, 14);
	sf::Color stopColor(247, 12, 55);

	// Start session and Stop session interactive button
	Btn* startBtn = new Btn("Start Session", { winCenter.x, bgImage.getGlobalBounds().height }, 16, robotoFont);
	startBtn->SetFillColor(startColor);
	startBtn->text.setFillColor(sf::Color::White);
	bool btnColorToggle = false;

	// all about the timer
	sf::Clock clock;
	float t1;
	sf::Int32 t2;
	int seconds = 0;
	bool timerOn = false; // timer thingy


	sf::Text time, trackerText("Tracking", robotoFont, 20), designateTime("HRS        MIN        SEC", robotoFont, 10);

	// Time display
	time.setFont(robotoFont);
	time.setFillColor(sf::Color::White);
	time.setPosition({ winSizeF.x - 150.f, 120.f });
	time.setCharacterSize(24);
	std::string timeToStr; // time parsed string

	// HRS MIN SEC below the timer
	designateTime.setFillColor(sf::Color::White);
	designateTime.setPosition({time.getGlobalBounds().left+8.f, 150.f});
	
	// 'Tracking' TEXT display
	trackerText.setPosition({ winCenter.x - trackerText.getGlobalBounds().width / 2, 110.f });
	sf::CircleShape trackingShape(5.f);
	trackingShape.setOrigin({ 5.f, 5.f });
	trackingShape.setPosition({trackerText.getGlobalBounds().left+trackerText.getGlobalBounds().width+trackingShape.getRadius()*2, 
								trackerText.getGlobalBounds().top});
	trackingShape.setFillColor(stopColor);

	bool showTimer = false;

	// Records showing 
	std::vector<std::string> data = { "Time interval:   8:19am - 9:20am", "Duration:   01:00:40" };
	Record record(robotoFont);
	std::vector<Record> recordsTable;
	record.SetRectPosition({ winCenter.x, 220.f });

	Record anoRecord(robotoFont);
	std::string strData = "Today";
	
	anoRecord.SetRectPosition({ winCenter.x, 220.f });
	anoRecord.SetText(strData);
	recordsTable.push_back(anoRecord);


	for (int i = 0; i < 5; i++)
	{
		sf::Vector2f lastRecordPos = recordsTable[recordsTable.size() - 1].rect.getPosition();
		record.SetRectPosition({ lastRecordPos.x, lastRecordPos.y + 35.f });
		record.SetText(data);
		recordsTable.push_back(Record(record));
	}
	


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
			showTimer = true;

			// Working with the system time and all that thing
			std::time_t const t = std::time(NULL);
			std::tm tm = *std::localtime(&t);
			std::cout << std::put_time(&tm, "%A %T") << std::endl; // for displaying the time

			char* dt = ctime(&t);
			std::cout << dt << std::endl;

		}
		else
		{
			startBtn->SetFillColor(startColor);
			startBtn->text.setString("Start Session");
			timerOn = false;
			bgImage.setPosition({ 0.f, 0.f });
			bgStopImage.setPosition({ 0.f, -200.f });
			startBtn->SetBtnPosition({ winCenter.x, bgImage.getGlobalBounds().height });
			showTimer = false;
		}
		btnColorToggle = !btnColorToggle;
		
	};


	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		startBtn->BtnEvents(window, event, testFunc);

		if (timerOn)
		{
			t1 = clock.getElapsedTime().asSeconds();
			t2 = clock.getElapsedTime().asMilliseconds();
			if (t1 > 1.f)
			{
				seconds += 1;
				clock.restart();
			}
			timeToStr = "0" + std::to_string(seconds / 3600) + ":" + "0"
				+ std::to_string((seconds / 60) % 60) + ":" + std::to_string(seconds % 60) + "." + std::to_string(int(t2 / 10));
			time.setString(timeToStr);
		}

		window.clear(sf::Color::White);

		window.draw(bgImage);
		window.draw(bgStopImage);
		window.draw(uiText);
		if (showTimer)
		{
			window.draw(trackerText);
			window.draw(trackingShape);
			window.draw(time);
			window.draw(designateTime);
		}
		window.draw(circle);
		startBtn->DrawTo(window);

		for (auto& record : recordsTable)
		{
			record.DrawTo(window);
		}
		window.display();
	}
}