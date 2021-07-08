#pragma once
#ifndef INPUTFIELD.H
#define INPUTFIELD.H
#include "SFML/Graphics.hpp"
#include <iostream>
#include <functional>
#include <ctime>

class InputField
{
	public:
		// UI Components
		sf::RectangleShape shape;
		sf::CircleShape Cleft, Cright;
		sf::Text text;
		sf::Font inputFont;

		// Supporting data members
		std::string inputText;
		std::string bufferString;
		size_t charSize = 16;
		
		// Boolean data members
		bool isFocused = false;
		bool mouseHeld = false;

		// Vectors and Rects
		sf::Vector2i mousePos;
		sf::Vector2f mousePosView;
		sf::Vector2f inputFieldPos;
		sf::Vector2f rectSize;
		sf::FloatRect textBounds;
		sf::FloatRect wholeInputRect;
		sf::FloatRect rectBounds;


		// Constructors and destructors
		InputField() {} // default 

		InputField(sf::Vector2f fieldPos, sf::Font& font);

		~InputField() {}

		void LoadText();
		void SetText(std::string inText);
		void CreateInputShape();
		void SetWholeRect();
		void InputEvent(sf::RenderWindow& window, sf::Event& event);
		void DrawTo(sf::RenderWindow& window);
};


#endif
