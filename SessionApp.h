#pragma once
#ifndef SESSIONAPP_H
#define SESSIONAPP_H
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <ctime>

// COLOR CONTAINER
#define BACKGROUNDC 13,13,39
#define WINWIDTH 740
#define WINHEIGHT 560
#define ANTIALIASING 4



class SessionApp
{
	private:
		// Main data components
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::ContextSettings settings;
		sf::Event event;

		// UI Components
		sf::Texture text;
		sf::Sprite background;

		// Boolean data components and Methods
		

		// Initializers
		void InitVariables();
		void InitWindow();

	public:
		// Constructors & Destructors
		SessionApp();
		~SessionApp();

		// Accessors
		const bool isRunning() const;

		// Helper Functions
		void PollEvents();

		// Modifiers (UPDATE)


		// Window Update & Render
		void Update();
		void Render();
};

#endif

