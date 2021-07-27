#pragma once
#include "SFML/Graphics.hpp"
#include "Btn.h"
#include "InputField.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <functional>

class Session_Tab
{
public:

};


class Session_Tracker
{
	public:
		// CONSTRUCTORS and DESTRUCTORS
		Session_Tracker(sf::RenderWindow& window);
		~Session_Tracker();

		// UI Components
		sf::Texture texture;
		sf::Sprite background;
		sf::RectangleShape rect;

		// BUTTONS and INPUTFIELD
		Btn* add_session_btn;
		InputField* input_session_field;

		// COMPONENTS CONTAINER
		std::vector<sf::RectangleShape> rects;
		std::vector<sf::Text> text_vec;
		std::vector<std::string> input_texts;

		// UI TYPOGRAPHY
		sf::Font kaushan_font;
		sf::Font roboto_font;
		sf::Text ui_text;
		sf::Text test_text;
		std::vector<sf::Text> al_UI_text;

		// DATA ACCESSORS
		sf::Vector2u win_size;
		sf::Vector2f win_sizeF;

		// BOOLEAN DATA COMPONENTS AND METHODS
		std::function<void()> add_rect;
		std::function<void()> add_session_tab;
		bool btn_hide;
		bool input_hide;

		// INITIALIZERS
		void Init_Variables();
		void Init_Background();
		void Init_UI_Font();
		void Init_UI_Components();
		void Update_Rects();

		bool enter_pressed;


		// EVENTS
		void Run_InputField_Event(sf::RenderWindow& window, sf::Event& event);
		void Run_Btn_Event(sf::RenderWindow& window, sf::Event& event);

		void Render_In_Main_Window(sf::RenderWindow& window);
		void Render_In_View(sf::RenderWindow& window);
};

