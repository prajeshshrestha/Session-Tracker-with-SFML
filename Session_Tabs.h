#pragma once
#include "SFML/Graphics.hpp"
#include "Btn.h"
#include "InputField.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <functional>

#define CIRCLE_R 15.f;
class Session_Tabs
{
public:
	// CONSTRUCTORS AND DESTRUCTORS;
	Session_Tabs();
	Session_Tabs(std::string name, sf::Vector2f pos, sf::Vector2f size, sf::Font& font);
	~Session_Tabs();

	// UI COMPONENTS
	Btn* session_btn;
	sf::Font roboto_font;

	float rect_w, rect_h;
	float circle_radius;
	sf::Vector2f rect_pos;
	sf::Vector2f rect_size;
	sf::Vector2f circle_origin;

	sf::Color background_color;
	sf::RectangleShape main_rect;
	sf::RectangleShape up_rect;
	sf::RectangleShape left_rect;
	sf::RectangleShape right_rect;
	sf::RectangleShape bottom_rect;
	sf::CircleShape c_top_left;
	sf::CircleShape c_top_right;
	sf::CircleShape c_bottom_left;
	sf::CircleShape c_bottom_right;
	std::string session_name;

	// ACCESSORS
	sf::Vector2f main_rect_pos;
	sf::Vector2f main_rect_size;

	// HELPER FUNCTION
	void Set_Components();
	void Set_Dimension();
	void Set_Button();

	// UPDATE AND RENDER
	void Draw_To(sf::RenderWindow& window);
};

