#include "Session_Tracker.h"

std::vector<std::string> db_session_list_data;
std::vector<std::string> new_input_texts;

Session_Tracker::Session_Tracker(sf::RenderWindow& window)
{
	win_size = window.getSize();
	win_sizeF = static_cast<sf::Vector2f>(win_size);
	Init_Variables();
	Init_Background();
	Init_UI_Components();
	session = new Session(window, "Digital Logic");
	Get_DB_Data();
}

Session_Tracker::~Session_Tracker()
{
	delete this->add_session_btn;
	delete this->input_session_field;
}

void Session_Tracker::Update_Rects_After_DB()
{
	if (session_tab_vec.size() < 12)
	{
		for (size_t i = 0; i < input_texts.size(); ++i)
		{
			if (session_tab_vec.empty())
			{
				initial_pos = { 132.f, 225.125f };
			}
			else if (session_tab_vec.size() <= 2)
			{
				initial_pos.x += 248.f;
			}
			else if (session_tab_vec.size() > 2 && session_tab_vec.size() <= 5)
			{
				if (session_tab_vec.size() == 3)
				{
					initial_pos.x = 132.f;
					initial_pos.y += 126.25f;
				}
				else
				{
					initial_pos.x += 248.f;
				}
			}
			else if (session_tab_vec.size() > 5 && session_tab_vec.size() <= 8)
			{
				if (session_tab_vec.size() == 6)
				{
					initial_pos.x = 132.f;
					initial_pos.y += 126.25f;
				}
				else
				{
					initial_pos.x += 248.f;
				}
			}
			else if (session_tab_vec.size() > 8 && session_tab_vec.size() <= 11)
			{
				if (session_tab_vec.size() == 9)
				{
					initial_pos.x = 132.f;
					initial_pos.y += 126.25f;
				}
				else
				{
					initial_pos.x += 248.f;
				}
			}
			session_tab = Session_Tab(input_texts[i], initial_pos, session_tab_size, roboto_font);
			session_tab_vec.push_back(Session_Tab(session_tab));
			//btn_event_func = [&]()
			//{
			//	show_session = true;
			//	show_session_tab = false;
			//	std::cout << selected_session_name << std::endl;
			//};
			//all_btn_event_func.push_back(std::function<void()>(btn_event_func));
		}
	}
}

void Session_Tracker::Get_DB_Data()
{
	session_tracker::select_data(dir);
	input_texts = db_session_list_data;
	Update_Rects_After_DB();
}

void Session_Tracker::Update_DB_Data()
{
	if (!new_input_texts.empty())
	{
		session_tracker::insert_data(dir);
	}
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
	session_tab_size = { 202.f, 80.25f };
	btn_show = true;
	show_session = false;
	show_session_tab = true;
	dir = "C:\\Users\\Progosta\\Desktop\\Tori Laure\\Session Tracker\\Session Tracker\\Session.db";

	btn_event_func = [&]()
	{
		std::cout << "Here" << std::endl;
		show_session = true;
		show_session_tab = false;
		session->Run_Functions(selected_session_name);
	};
}

void Session_Tracker::Init_Background()
{
	if (!texture.loadFromFile("Images/BBG.png"))
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
}

void Session_Tracker::Update_Rects()
{
	if (input_texts.back() != "" )
	{
		if (session_tab_vec.size() < 12)
		{
			if (session_tab_vec.empty())
			{
				initial_pos = { 132.f, 225.125f };
			}
			else if (session_tab_vec.size() <= 2)
			{
				initial_pos.x += 248.f;
			}
			else if (session_tab_vec.size() > 2 && session_tab_vec.size() <= 5)
			{
				if (session_tab_vec.size() == 3)
				{
					initial_pos.x = 132.f;
					initial_pos.y += 126.25f;
				}
				else
				{
					initial_pos.x += 248.f;
				}
			}
			else if (session_tab_vec.size() > 5 && session_tab_vec.size() <= 8)
			{
				if (session_tab_vec.size() == 6)
				{
					initial_pos.x = 132.f;
					initial_pos.y += 126.25f;
				}
				else
				{
					initial_pos.x += 248.f;
				}
			}
			else if (session_tab_vec.size() > 8 && session_tab_vec.size() <= 11)
			{
				if (session_tab_vec.size() == 9)
				{
					initial_pos.x = 132.f;
					initial_pos.y += 126.25f;
				}
				else
				{
					initial_pos.x += 248.f;
				}
			}
			session_tab = Session_Tab(input_texts.back(), initial_pos, session_tab_size, roboto_font);
			session_tab_vec.push_back(Session_Tab(session_tab));
			new_input_texts.push_back(input_texts.back());

			/*all_btn_event_func.push_back(std::function<void()>(btn_event_func));*/
		}
	}
	else
	{
		input_texts.pop_back();
	}

}

void Session_Tracker::Render_In_Main_Window(sf::RenderWindow& window)
{
	if (show_session_tab)
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
		if (!session_tab_vec.empty() and btn_show)
		{
			for (auto& session_tab : session_tab_vec)
			{
				session_tab.Draw_To(window);
			}
		}
	}

	if (show_session)
	{
		session->Draw_To_Main_Window(window);
	}
}

void Session_Tracker::Run_InputField_Event(sf::RenderWindow& window, sf::Event& event, sf::View& scroll_view)
{
	if (show_session_tab)
	{
		input_session_field->InputEvent(window, event, input_hide, btn_hide, input_texts, enter_pressed);
		if (enter_pressed)
		{
			Update_Rects();
			enter_pressed = false;
		}
	}
	if (show_session)
	{
		session->View_Scroll_Event(event, scroll_view);
	}
}

void Session_Tracker::Render_In_View(sf::RenderWindow& window)
{
	if (show_session)
	{
		session->Draw_To_View(window);
	}
}

void Session_Tracker::Run_Btn_Event(sf::RenderWindow& window, sf::Event& event)
{
	if (show_session_tab)
	{
		add_session_btn->BtnEvents(window, event, add_rect, btn_hide);
		for (size_t i = 0; i < session_tab_vec.size(); ++i)
		{
			session_tab_vec[i].session_btn->BtnEvents(window, event, btn_event_func, input_texts[i], selected_session_name);
		}
	}
	if (show_session)
	{
		session->Run_Events(window, event, show_session, show_session_tab);
	}
}

Session_Tab::Session_Tab()
{
}

Session_Tab::Session_Tab(std::string name, sf::Vector2f pos, sf::Vector2f size, sf::Font& font)
{
	session_name = name;
	rect_pos = pos;
	rect_size = size;
	roboto_font = font;
	Set_Components();
	Set_Dimension();
	Set_Button();
}

Session_Tab::~Session_Tab()
{
	
}

void Session_Tab::Set_Components()
{
	circle_radius = CIRCLE_RR;
	background_color = sf::Color(23, 137, 252);
}

void Session_Tab::Set_Dimension()
{
	main_rect.setSize(rect_size);
	up_rect.setSize({ rect_size.x, circle_radius });
	left_rect.setSize({ circle_radius, rect_size.y });
	right_rect.setSize({ circle_radius, rect_size.y});
	bottom_rect.setSize({ rect_size.x, circle_radius });
	
	main_rect.setOrigin({ main_rect.getSize().x / 2, main_rect.getSize().y / 2 });
	main_rect.setPosition(rect_pos);

	main_rect_pos = main_rect.getPosition();
	main_rect_size = main_rect.getSize();
	circle_origin = { circle_radius, circle_radius };

	c_top_left.setRadius(circle_radius);
	c_top_right.setRadius(circle_radius);
	c_bottom_left.setRadius(circle_radius);
	c_bottom_right.setRadius(circle_radius);

	c_top_left.setOrigin(circle_origin);
	c_top_right.setOrigin(circle_origin);
	c_bottom_left.setOrigin(circle_origin);
	c_bottom_right.setOrigin(circle_origin);

	c_top_left.setPosition({ main_rect_pos.x - main_rect_size.x / 2, main_rect_pos.y - main_rect_size.y / 2 });
	c_top_right.setPosition({ main_rect_pos.x + main_rect_size.x / 2, main_rect_pos.y - main_rect_size.y / 2 });
	c_bottom_left.setPosition({ main_rect_pos.x - main_rect_size.x / 2, main_rect_pos.y + main_rect_size.y / 2 });
	c_bottom_right.setPosition({ main_rect_pos.x + main_rect_size.x / 2, main_rect_pos.y + main_rect_size.y / 2 });

	up_rect.setOrigin({ up_rect.getSize().x / 2, up_rect.getSize().y / 2 });
	left_rect.setOrigin({ left_rect.getSize().x / 2, left_rect.getSize().y / 2 });
	right_rect.setOrigin({ right_rect.getSize().x / 2, right_rect.getSize().y / 2 });
	bottom_rect.setOrigin({ bottom_rect.getSize().x / 2, bottom_rect.getSize().y / 2 });

	up_rect.setPosition({ main_rect_pos.x, main_rect_pos.y - main_rect_size.y / 2 - up_rect.getSize().y / 2 });
	bottom_rect.setPosition({ main_rect_pos.x, main_rect_pos.y + main_rect_size.y / 2 + up_rect.getSize().y / 2 });
	left_rect.setPosition({ main_rect_pos.x - main_rect_size.x / 2 - left_rect.getSize().x / 2, main_rect_pos.y });
	right_rect.setPosition({ main_rect_pos.x + main_rect_size.x / 2 + left_rect.getSize().x / 2, main_rect_pos.y });

	c_top_left.setFillColor(background_color);
	c_top_right.setFillColor(background_color);
	c_bottom_left.setFillColor(background_color);
	c_bottom_right.setFillColor(background_color);

	up_rect.setFillColor(background_color);
	left_rect.setFillColor(background_color); 
	right_rect.setFillColor(background_color);
	bottom_rect.setFillColor(background_color);
	main_rect.setFillColor(background_color);
	std::cout << up_rect.getPosition().x << std::endl;
}

void Session_Tab::Set_Button()
{
	session_btn = new Btn(session_name, {main_rect_pos.x, main_rect_pos.y - 20.f}, 15, roboto_font);
}

void Session_Tab::Draw_To(sf::RenderWindow& window)
{
	window.draw(main_rect);
	window.draw(c_top_left);
	window.draw(c_top_right);
	window.draw(c_bottom_left);
	window.draw(c_bottom_right);

	window.draw(up_rect);
	window.draw(left_rect);
	window.draw(right_rect);
	window.draw(bottom_rect);
	session_btn->DrawTo(window);
}


static int session_tracker::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	db_session_list_data.push_back(argv[1]);
	return 0;
}

static int session_tracker::select_data(const char* s)
{
	sqlite3* DB;
	char* messageError;

	std::string sql = "SELECT * FROM SESSION;";

	int exit = sqlite3_open(s, &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
	exit = sqlite3_exec(DB, sql.c_str(), session_tracker::callback, NULL, &messageError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error in selectData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records selected Successfully!" << std::endl;

	return 0;
}

static int session_tracker::insert_data(const char* s)
{
	sqlite3* DB;
	char* messageError;
	int exit = sqlite3_open(s, &DB);
	std::string sql;

	if (!new_input_texts.empty())
	{
		std::string tester = "";
		for (size_t i = 0; i < new_input_texts.size(); ++i)
		{
			tester += "('" + new_input_texts[i] + "'),";
		}
		tester.erase(tester.size() - 1, 1);

		sql = "INSERT INTO SESSION (session_name) VALUES" + tester + ";";
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			std::cerr << "Error in insertData function." << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "Records inserted Successfully!" << std::endl;
	}

	return 0;
}