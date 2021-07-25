#include "Session.h"

Record::Record(sf::Font& f, bool is_date)
{
	this->font = f;
	time_stamp_text.setFont(f);
	time_duration_text.setFont(f);
	date_text.setFont(f);
	time_stamp_text.setCharacterSize(TEXT_CHAR_SIZE);
	time_duration_text.setCharacterSize(TEXT_CHAR_SIZE);
	date_text.setCharacterSize(TEXT_CHAR_SIZE);

	rect_h = RECT_H;
	circle_radius = CIRCLE_R;
	date_bar = is_date;

	!is_date ? rect_w = DETAIL_BAR_WIDTH : rect_w = DATE_BAR_WIDTH;

	rect.setOrigin({ 0.f, rect_h / 2 });
	rect.setSize({ rect_w, rect_h });

	c_left.setRadius(circle_radius);
	c_right.setRadius(circle_radius);
	c_left.setOrigin({ CIRCLE_R, CIRCLE_R });
	c_right.setOrigin({ CIRCLE_R, CIRCLE_R });
}

void Record::Set_Text(std::vector<std::string> data)
{
	record_data = data;
	time_stamp_text.setString(this->record_data[0]);
	time_duration_text.setString(this->record_data[1]);
	time_stamp_text.setFillColor(sf::Color::Black);
	time_duration_text.setFillColor(sf::Color::Black);

	rect.setFillColor(sf::Color(DETAIL_BAR_C));
	c_left.setFillColor(sf::Color(DETAIL_BAR_C));
	c_right.setFillColor(sf::Color(DETAIL_BAR_C));

	time_stamp_text.setOrigin({ 0.f, time_stamp_text.getGlobalBounds().height / 2 });
	time_duration_text.setOrigin({ 0.f, time_duration_text.getGlobalBounds().height / 2 });

	time_stamp_text.setPosition({ TIME_STAMP_POSX, rect_pos.y - time_stamp_text.getGlobalBounds().height / 6 });
	time_duration_text.setPosition({ TIME_DURATION_POSX, rect_pos.y - time_stamp_text.getGlobalBounds().height / 3 });
}

void Record::Set_Text(std::string data)
{
	is_bar = true;
	date_text.setString(data);
	date_text.setFillColor(sf::Color::White);

	rect.setFillColor(sf::Color(DATE_BAR_C));
	c_left.setFillColor(sf::Color(DATE_BAR_C));
	c_right.setFillColor(sf::Color(DATE_BAR_C));

	date_text.setOrigin({ date_text.getGlobalBounds().width / 2, date_text.getGlobalBounds().height / 2 });
	date_text.setPosition({ DATE_TEXT_POSX, rect_pos.y - time_stamp_text.getGlobalBounds().height / 3 - DATE_TEXT_POSY_OFFSET });
}

void Record::Set_Rect_Position(sf::Vector2f pos)
{
	rect.setPosition(pos);
	rect_bounds = rect.getGlobalBounds();
	rect_pos = rect.getPosition();

	c_left.setPosition({ rect_bounds.left, rect_bounds.top + rect_bounds.height / 2 });
	c_right.setPosition({ rect_bounds.left, rect_bounds.top + rect_bounds.height / 2 });

}

void Record::Draw_To(sf::RenderWindow& window)
{
	window.draw(rect);
	window.draw(c_left);
	window.draw(c_right);
	window.draw(time_stamp_text);
	window.draw(time_duration_text);
	window.draw(date_text);
}


// Session Members
Session::Session(sf::RenderWindow& window)
{
	// setting window info
	win_size = window.getSize();
	win_sizeF = static_cast<sf::Vector2f>(win_size);
	win_center = sf::Vector2f({ win_sizeF.x / 2, win_sizeF.y / 2 });
	load_tex_font();
	load_session_name();
	init_UI_components();
	load_clock_components();
}

void Session::init_variables()
{
}

void Session::load_tex_font()
{
	if(!bg_image_tex.loadFromFile("Texture/bgImageText1.png"))
		throw "Error in loading the 'bgImageText1'";

	if (!bg_stop_tex.loadFromFile("Texture/stopTimer1.png"))
		throw "Error in loading the 'stopTimer1.png'";

	if (!kaushan_font.loadFromFile("Font/KaushanScript-Regular.ttf"))
		throw "Error in loading 'Roboto-Medium.ttf";

	if (!roboto_font.loadFromFile("Font/Roboto-Medium.ttf"))
		throw "Error in loading the 'Roboto-Medium.ttf'";

	bg_image.setTexture(bg_image_tex);
	bg_stop_image.setTexture(bg_stop_tex);
	bg_image.setPosition({ 0.f, 0.f });
	bg_stop_image.setPosition({ 0.f, -200.f });
}

void Session::load_session_name()
{
	session_text = sf::Text("Engineering", kaushan_font, 30);
	session_text.setPosition({ win_center.x - session_text.getGlobalBounds().width / 2, 35.f });
	session_text.setFillColor(sf::Color::White);

	circle.setRadius(BG_NAME_CIRCLE_R);
	circle.setOrigin({ BG_NAME_CIRCLE_R, BG_NAME_CIRCLE_R });
	circle.setFillColor(sf::Color(BG_CIRCLE_FILL_C));
	circle.setPosition({ session_text.getGlobalBounds().left - circle.getRadius() * 2, session_text.getGlobalBounds().top + session_text.getGlobalBounds().height / 2 });
}

void Session::init_UI_components()
{
	create_toggle_btn();
}

void Session::create_toggle_btn()
{
	toggle_btn = new Btn("Start Session", { win_center.x, bg_image.getGlobalBounds().height }, 16, roboto_font);
	toggle_btn->SetFillColor(sf::Color(START_BTN_COLOR));
	toggle_btn->text.setFillColor(sf::Color::White);
	btn_color_toggle = false;
}

void Session::load_clock_components()
{
	t2 = 0;
	seconds = 0;
	mili_sec = 0;
	ms = 0;
	timer_on = false;
	
	timer_text.setFont(roboto_font);
	timer_text.setFillColor(sf::Color::White);
	timer_text.setPosition({ win_sizeF.x - 150.f, 120.f });
	timer_text.setCharacterSize(24);
	time_to_str = "00:00:0.00";

	designate_time_text = sf::Text("HRS        MIN        SEC", roboto_font, 10);
	designate_time_text.setFillColor(sf::Color::White);
	designate_time_text.setPosition({ timer_text.getGlobalBounds().left + 8.f, 150.f });

	tracker_text = sf::Text("Tracking", roboto_font, 20);
	tracker_text.setPosition({ win_center.x - tracker_text.getGlobalBounds().width / 2, 110.f });

	tracking_shape.setRadius(TRACKER_CIRCLE_R);
	tracking_shape.setOrigin({ TRACKER_CIRCLE_R, TRACKER_CIRCLE_R });
	tracking_shape.setPosition({ tracker_text.getGlobalBounds().left + tracker_text.getGlobalBounds().width + tracking_shape.getRadius() * 2,
							tracker_text.getGlobalBounds().top });
	tracking_shape.setFillColor(sf::Color(STOP_BTN_COLOR));

	show_timer = false;



}
