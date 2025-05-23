#pragma once
#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "SFML/Graphics.hpp"
#include <iostream>
#include <ctime>
#include <functional>

class Btn
{
	public:
		// Button UI components
		sf::RectangleShape shape;
		sf::CircleShape C1, C2;
		sf::Text text;
		sf::Font uiFont;

		// Vectors and Rects
		sf::Vector2f inputBtnPos;
		sf::FloatRect textBounds;
		sf::FloatRect shapeBounds;
		sf::Vector2i mousePos;
		sf::Vector2f mousePosView;
		sf::FloatRect wholeBtnRect;

		// String and other
		std::string btnText;

		// Initialized values
		float fixFactor = 4.5f;
		float btnScale = 1.02f;
		uint8_t charSize = 0;

		// Boolean data members
		bool mouseInside = false;
		bool mouseHeld = false;

		// Constructors and Destructor
		Btn() {}
		Btn(std::string BtnText, sf::Vector2f btnPos,uint8_t charSize, sf::Font& font);
		~Btn() {}

		void LoadText();
		void SetBtnShape();
		void SetBtnPosition(sf::Vector2f pos);
		void SetText();
		void SetBtnRect();
		void SetFillColor(sf::Color color);
		void BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func, bool &btnHide);
		void BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func);
		void BtnEvents(sf::RenderWindow& window, sf::Event& event, std::function<void()> func, std::string name, std::string& selected_session_name);
		void BtnEvents(sf::RenderWindow& window, sf::Event& event, bool& btn_show);
		void DrawTo(sf::RenderWindow &window);
};

#endif