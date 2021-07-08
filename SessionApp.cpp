#include "SessionApp.h"

void SessionApp::InitVariables()
{
	this->videoMode.width = WINWIDTH;
	this->videoMode.height = WINHEIGHT;
	this->settings.antialiasingLevel = ANTIALIASING;

	this->rect.setPosition({ 0.f, 0.f });
	this->rect.setSize({ 740.f, 30.f });
	this->sessionView.reset(sf::FloatRect(0, 0, 740.f, 560.f));
	this->sessionView.setViewport(sf::FloatRect(0, 0.3035, 1.0f, 1.0f));
}

void SessionApp::InitWindow()
{
	this->window = new sf::RenderWindow(this->videoMode, "SESSION TRACKER", sf::Style::Titlebar | sf::Style::Close, this->settings);
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
	this->addSessionBtn = new Btn("+ Add new session", { winSizeF.x / 2, 110.f },static_cast<uint8_t>(16), this->fontRoboto);
	this->addSessionBtn->SetFillColor(sf::Color(23, 137, 252));
	this->addSessionBtn->text.setFillColor(sf::Color::White);

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
	delete this->addSessionBtn;
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
	this->addSessionBtn->BtnEvents(*this->window, this->event, this->addRect);
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
	this->window->clear(sf::Color(13,13,39));

	
	this->window->setView(this->window->getDefaultView());
	this->window->draw(this->background);
	//this->addProjectBtn.drawTo(*this->window);
	this->addSessionBtn->DrawTo(*this->window);

	this->window->setView(this->sessionView);
	for (auto& rect : rects)
	{
		this->window->draw(rect);
	}
	
	this->window->display();
}
