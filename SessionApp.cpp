#include "SessionApp.h"

void SessionApp::InitVariables()
{
	this->videoMode.width = WINWIDTH;
	this->videoMode.height = WINHEIGHT;
	this->settings.antialiasingLevel = ANTIALIASING;
	this->rect.setPosition({ 0.f, 170.f });
	this->rect.setSize({ 740.f, 30.f });
	this->sessionView.reset(sf::FloatRect(0, 170.f, 740.f, 390.f));
	this->sessionView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	
}

void SessionApp::InitWindow()
{
	this->window = new sf::RenderWindow(this->videoMode, "SESSION TRACKER");
	this->window->setFramerateLimit(FPS);
	this->winSize = this->window->getSize();
	this->winSizeF = static_cast<sf::Vector2f>(this->winSize);
}

void SessionApp::InitBackground()
{
	if (!this->texture.loadFromFile("Images/backToTitle.png"))
		throw "Error in loading the 'backToback.png'";
	this->background.setTexture(this->texture);
	this->background.setPosition({ 0.f, 0.f });
}

void SessionApp::InitUIFont()
{
	if (!this->fontKaushan.loadFromFile("Font/KaushanScript-Regular.ttf"))
		throw "Error in loading the 'KaushanScript-Regular.ttf'";
	if (!this->fontRoboto.loadFromFile("Font/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium.ttf'";
	this->uiText.setFont(fontKaushan);
}

void SessionApp::InitUIComponents()
{
	this->InitUIFont();
	addProjectBtn = Button("+ Add new session", { 190.f, 30.f }, { winSizeF.x / 2 - 95, 100.f }, this->fontRoboto);
	addProjectBtn.setTextSize(18);
	this->addRect = [&]()
	{
		
		if (this->rects.size() >= 1)
		{
			sf::Vector2f lastRectPos = this->rects[rects.size() - 1].getPosition();
			this->rect.setPosition({ 0.f, lastRectPos.y + 32.f });
			this->rect.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
			this->rects.push_back(sf::RectangleShape(this->rect));
		}
		else 
		{
			this->rect.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
			this->rects.push_back(sf::RectangleShape(this->rect));
		}
	};
}

SessionApp::SessionApp()
{
	this->InitVariables();
	this->InitWindow();
	this->InitBackground();
	this->InitUIComponents();
}

SessionApp::~SessionApp()
{
	delete this->window;
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
		this->addProjectBtn.btnEvents(this->event, *this->window, this->addRect);
	}
}

void SessionApp::LogoUITextUpdate()
{
	this->uiText.setString(sf::String("Session Tracker"));
	this->uiText.setCharacterSize(40);
	this->uiText.setLetterSpacing(1.f);
	sf::FloatRect textBounds = this->uiText.getGlobalBounds();
	this->uiText.setPosition({winSizeF.x/2-textBounds.width/2, 20.f});
	this->allUIText.push_back(this->uiText);
}

void SessionApp::UITextUpdate()
{
	this->LogoUITextUpdate();
}

void SessionApp::ViewUpdate()
{
}

void SessionApp::Update()
{
	this->PollEvents();
	this->UITextUpdate();

}

void SessionApp::Render()
{
	this->window->clear(sf::Color::White);

	
	this->window->setView(this->window->getDefaultView());
	this->window->draw(this->background);
	this->addProjectBtn.drawTo(*this->window);

	this->window->setView(this->sessionView);
	for (auto& rect : rects)
	{
		this->window->draw(rect);
	}
	
	this->window->display();
}
