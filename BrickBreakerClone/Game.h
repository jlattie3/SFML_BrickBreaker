//
// Created by bswenson3 on 11/9/16.
//
#pragma once

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Ball.h"
#include "Brick.h"

class Game {
public:
	//use default screen size
	Game();
	//run the game
	void run();

private:
	void processEvents();
	//update the game objects
	void update(sf::Time deltaT);
	//draw the scene
	void render();
	//handle input from the user
	void handlePlayerInput(sf::Keyboard::Key key, bool isDown);

	sf::RenderWindow m_window;
	Platform m_platform;
	Ball m_ball;
	Brick m_brick;
	std::vector<Brick*> m_bricks;

	bool m_left = false;
	bool m_right = false;
};

