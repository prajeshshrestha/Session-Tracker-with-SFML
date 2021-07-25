#pragma once
#include "SFML/Graphics.hpp"
#include "Btn.h"
#include <vector>

#define TEXT_CHAR_SIZE 16
#define DETAIL_BAR_WIDTH 700.f
#define DATE_BAR_WIDTH 300.f
#define RECT_H 30.f
#define CIRCLE_R 15.f
#define TIME_STAMP_POSX 30.f
#define TIME_DURATION_POSX 510.f
#define DATE_TEXT_POSX 70.f
#define DATE_TEXT_POSY_OFFSET 3.f
#define BG_NAME_CIRCLE_R 6.f
#define TRACKER_CIRCLE_R 5.f

#define DETAIL_BAR_C 230, 230, 230
#define DATE_BAR_C 41, 41, 41
#define BG_CIRCLE_FILL_C 8, 218, 145
#define START_BTN_COLOR 24, 171, 14
#define STOP_BTN_COLOR 247, 12, 55


class Record
{
	public:
		// DESIGN 
		sf::RectangleShape rect;
		sf::CircleShape c_left, c_right;
		sf::Font font;
		sf::Text time_stamp_text;
		sf::Text time_duration_text;
		sf::Text date_text;

		// DATA
		std::vector<std::string> record_data;
		sf::Vector2f rect_pos;
		sf::FloatRect rect_bounds;
		sf::FloatRect time_stamp_bounds;
		sf::FloatRect time_duration_bounds;

		// BASIC
		float rect_w, rect_h, circle_radius;
		bool is_bar = false;
		bool date_bar;

		// CONSTRUCTORS 
		Record(sf::Font& f, bool is_date = 0);
		void Set_Text(std::vector<std::string> data);
		void Set_Text(std::string data);
		void Set_Rect_Position(sf::Vector2f pos);
		void Draw_To(sf::RenderWindow& window);
};

class Session
{
	public:
		// Window Property
		sf::RenderWindow window;
		sf::Vector2u win_size;
		sf::Vector2f win_sizeF;
		sf::Vector2f win_center;

		// Loading TEXTURE, SPRITE, FONT
		sf::Texture bg_image_tex, bg_stop_tex;
		sf::Font kaushan_font, roboto_font;
		sf::Sprite bg_image, bg_stop_image;

		// BACKGROUND Name and design
		sf::Text session_text;
		sf::CircleShape circle;

		// UI Components
		Btn* toggle_btn;
		bool btn_color_toggle;

		// CLOCK 
		sf::Clock clock;
		sf::Text timer_text, tracker_text, designate_time_text;
		sf::CircleShape tracking_shape;
		std::string time_to_str;
		int seconds = 0;
		int mili_sec = 0;
		int ms = 0;
		float t1;
		sf::Int32 t2;
		bool timer_on;
		bool show_timer;


		Session(sf::RenderWindow& window);
		void init_variables();
		void load_tex_font();
		void load_session_name();
		void init_UI_components();
		void create_toggle_btn();
		void load_clock_components();

};

