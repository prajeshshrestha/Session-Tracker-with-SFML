#include "SessionApp.h"


void SessionApp::InitVariables()
{
	this->videoMode.width = WINWIDTH;
	this->videoMode.height = WINHEIGHT;
	this->settings.antialiasingLevel = ANTIALIASING;
}

void SessionApp::InitWindow()
{
	window = new sf::RenderWindow(this->videoMode, "SESSION TRACKER");
	this->window->setFramerateLimit(60);
}

SessionApp::SessionApp()
{
	this->InitVariables();
	this->InitWindow();
}

SessionApp::~SessionApp()
{
}

const bool SessionApp::isRunning() const
{
	return this->window->isOpen();;
}

void SessionApp::PollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					this->window->close();
				break;
		}
	}
}

void SessionApp::Update()
{
	this->PollEvents();
}

void SessionApp::Render()
{
	this->window->clear(sf::Color::White);
	this->window->display();
}
