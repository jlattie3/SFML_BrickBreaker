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
	m_ball.load("/Users/jacoblattie/Desktop/Git/BrickBreaker/BrickBreakerClone/build/content/BreakerBall.png");
	m_ball.setScale(1.0f);
    m_ball.setPosition(450.0f, 680.0f);
    // load sample brick
    m_brick.load("/Users/jacoblattie/Desktop/Git/BrickBreaker/BrickBreakerClone/build/content/BrickTexture.png");
    m_brick.setPosition(450.0f, 300.0f);
    m_brick.setScale(2.0f);
	// load vector of bricks
	for (int i = 0; i < 3; i++) {
		auto brick = new Brick();
		m_bricks.push_back(brick);
	}
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
	if (m_left)
		plat_movement.x -= m_platform.getSpeed();
	if (m_right)
		plat_movement.x += m_platform.getSpeed();
    m_platform.checkBounds();
	m_platform.move(plat_movement * deltaT.asSeconds());

	// Brick Update
	bool isHit = m_brick.checkHit(m_ball.getBallRectangle());
//	for (auto brick : m_bricks) {
//	    brick->checkHit(m_ball.getBallRectangle());
//	}
	// Ball update for brick
	if (isHit) {
		m_ball.bounce(deltaT, m_brick.getBrickRectangle());
	}

	// Ball for platform
	float width = m_platform.getWidth();
	sf::Vector2f plat_pos = m_platform.getPosition();
	sf::Vector2f platform_bounds(plat_pos.x, plat_pos.x + width * 2);
	m_ball.checkBounds(deltaT, platform_bounds);


}


void Game::render() {
	m_window.clear();

	m_platform.draw(m_window);
	m_ball.draw(m_window);
	m_brick.draw(m_window);
//    for (int i = 0; i < 3; i++) {
//        m_bricks[i]->draw(m_window);
//    }
	m_window.display();
}