//
// Created by Jacob Lattie.
//

#include "Game.h"

Game::Game() :
	m_window(sf::VideoMode(960, 720), "Brick Breaker")
{
	//load the platform
	m_platform.load("/Users/jacoblattie/Desktop/Git/BrickBreaker/BrickBreakerClone/build/content/Platform.png");
	m_platform.setScale(2.0f);
	m_platform.setPosition(400.0f, 700.0f);
	// load the ball
	m_ball.load("/Users/jacoblattie/Desktop/Git/BrickBreaker/BrickBreakerClone/build/content/Ball.png");
	m_ball.setScale(1.0f);
    m_ball.setPosition(450.0f, 10.0f);

}

void Game::run() {
	sf::Clock clock;

	while (m_window.isOpen()) {
		sf::Time deltaT = clock.restart();
		processEvents();
		update(deltaT);
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::KeyPressed:
			//handle key down here
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			m_window.close();
			break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isDown) {
	if (key == sf::Keyboard::Left)
		m_left = isDown;
	if (key == sf::Keyboard::Right)
		m_right = isDown;
}

//use time since last update to get smooth movement
void Game::update(sf::Time deltaT) {
	// Platform update
	sf::Vector2f plat_movement(0.0f, 0.0f);
	if (m_up)
		plat_movement.y -= m_platform.getSpeed();
	if (m_down)
		plat_movement.y += m_platform.getSpeed();
	if (m_left)
		plat_movement.x -= m_platform.getSpeed();
	if (m_right)
		plat_movement.x += m_platform.getSpeed();
    m_platform.checkBounds();
	m_platform.move(plat_movement * deltaT.asSeconds());

	// Ball update
	float ball_radius = 12.5f;
	const sf::Time update_ms = sf::seconds(1.f);
	const auto pos = m_ball.getPosition();
	const auto delta = deltaT.asSeconds() * m_ball.getVelocity();
	sf::Vector2f new_pos(pos.x + m_ball.getDirection().x * delta, pos.y + m_ball.getDirection().y * delta);
	m_ball.setPosition(new_pos.x, new_pos.y);
	m_ball.checkBounds();

}

void Game::render() {
	m_window.clear();

	m_platform.draw(m_window);
	m_ball.draw(m_window);

	m_window.display();
}