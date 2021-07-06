#pragma once
#ifndef SESSIONAPP_H
#define SESSIONAPP_H
#include "SFML/Graphics.hpp"
#include "Button.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <functional>

// COLOR CONTAINER
#define BACKGROUNDC 13,13,39
#define WINWIDTH 740
#define WINHEIGHT 560
#define ANTIALIASING 8
#define FPS 60


class SessionApp
{
	private:
		// Main data components
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::ContextSettings settings;
		sf::Event event;

		// UI Components
		sf::Texture texture;
		sf::Sprite background;
		Button addProjectBtn;
		sf::RectangleShape rect;
		std::vector<sf::RectangleShape> rects;
		sf::View sessionView;

		// UI Typogrphy
		sf::Font fontKaushan;
		sf::Font fontRoboto;
		sf::Text uiText;
		std::vector<sf::Text> allUIText;

		// Data Accessors
		sf::Vector2u winSize;
		sf::Vector2f winSizeF;

		// Boolean data components and Methods
		std::function<void()> addRect;

		// Initializers
		void InitVariables();
		void InitWindow();
		void InitBackground();
		void InitUIFont();
		void InitUIComponents();

	public:
		// Constructors & Destructors
		SessionApp();
		~SessionApp();

		// Accessors
		const bool isRunning() const;

		// Helper Functions
		void PollEvents();

		// UIText Updaters
		void LogoUITextUpdate();

		// Modifiers (UPDATE)
		void UITextUpdate();
		void ViewUpdate();

		// Window Update & Render
		void Update();
		void Render();
};

#endif

