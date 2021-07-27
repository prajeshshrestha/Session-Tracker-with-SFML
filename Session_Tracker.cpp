#include "Session_Tracker.h"

Session_Tracker::Session_Tracker(sf::RenderWindow& window)
{
	win_size = window.getSize();
	win_sizeF = static_cast<sf::Vector2f>(win_size);
	Init_Variables();
	Init_Background();
	Init_UI_Components();
}

Session_Tracker::~Session_Tracker()
{
	delete this->add_session_btn;
	delete this->input_session_field;
}

void Session_Tracker::Init_Variables()
{
	this->rect.setPosition({ 0.f, 0.f });
	this->rect.setSize({ 740.f, 30.f });
	this->rect.setFillColor(sf::Color(240, 240, 240));
	this->test_text.setPosition({ 0.f, 0.f });
	this->test_text.setFillColor(sf::Color::Black);
	this->test_text.setCharacterSize(16);
	btn_hide = false;
	input_hide = true;
	enter_pressed = false;
}

void Session_Tracker::Init_Background()
{
	if (!texture.loadFromFile("Images/BG_Title.png"))
		throw "Error in loading the 'BG_Title.png'";
	background.setTexture(texture);
	background.setPosition({ 0.f, 0.f });
}

void Session_Tracker::Init_UI_Font()
{
	if (!kaushan_font.loadFromFile("Font/KaushanScript-Regular.ttf"))
		throw "Error in loading the 'KaushanScript-Regular.ttf'";

	if (!roboto_font.loadFromFile("Font/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium.ttf'";
	ui_text.setFont(kaushan_font);
	test_text.setFont(roboto_font);
}

void Session_Tracker::Init_UI_Components()
{
	Init_UI_Font();
	add_session_btn = new Btn("+ Add new session", { win_sizeF.x / 2, 110.f }, static_cast<uint8_t>(16), roboto_font);
	add_session_btn->SetFillColor(sf::Color(23, 137, 252));
	add_session_btn->text.setFillColor(sf::Color::White);

	input_session_field = new InputField({ win_sizeF.x / 2, 110.f }, roboto_font);

	add_rect = [&]()
	{
		btn_hide = true;
		input_hide = false;
	};

	//add_session_tab = [&]()
	//{
	//	test_text.setString(input_texts[input_texts.size() - 1]);
	//	if (this->rects.size() >= 1)
	//	{
	//		sf::Vector2f lastRectPos = rects[rects.size() - 1].getPosition();
	//		rect.setPosition({ 0.f, lastRectPos.y + 32.f });
	//		test_text.setPosition(rect.getPosition());
	//		rects.push_back(sf::RectangleShape(rect));
	//		text_vec.push_back(sf::Text(test_text));
	//	}
	//	else
	//	{
	//		rects.push_back(sf::RectangleShape(this->rect));
	//		text_vec.push_back(sf::Text(test_text));
	//	}
	//};
}

void Session_Tracker::Update_Rects()
{

	test_text.setString(input_texts[input_texts.size() - 1]);
	if (this->rects.size() >= 1)
	{
		sf::Vector2f lastRectPos = rects[rects.size() - 1].getPosition();
		rect.setPosition({ 0.f, lastRectPos.y + 32.f });
		test_text.setPosition(rect.getPosition());
		rects.push_back(sf::RectangleShape(rect));
		text_vec.push_back(sf::Text(test_text));
	}
	else
	{
		rects.push_back(sf::RectangleShape(this->rect));
		text_vec.push_back(sf::Text(test_text));
	}

}

void Session_Tracker::Render_In_Main_Window(sf::RenderWindow& window)
{
	window.draw(this->background);
	if (!btn_hide)
	{
		add_session_btn->DrawTo(window);
	}
	if (!input_hide)
	{
		input_session_field->DrawTo(window);
	}
}

void Session_Tracker::Run_InputField_Event(sf::RenderWindow& window, sf::Event& event)
{
	input_session_field->InputEvent(window, event, input_hide, btn_hide, input_texts, enter_pressed);
	if (enter_pressed)
	{
		Update_Rects();
		enter_pressed = false;
	}
}

void Session_Tracker::Render_In_View(sf::RenderWindow& window)
{
	for (auto& rect : rects)
	{
		window.draw(rect);
	}
	for (auto& text : text_vec)
	{
		window.draw(text);
	}
}

void Session_Tracker::Run_Btn_Event(sf::RenderWindow& window, sf::Event& event)
{
	add_session_btn->BtnEvents(window, event, add_rect, btn_hide);
}

