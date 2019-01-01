//
// Created by Jacob Lattie on 2018-12-29.
//

#include "Ball.h"
#include <random>
#include <functional>
#include <cstdlib>
#include <cmath>

Ball::Ball() {

}

bool Ball::load(const std::string& filename) {
    if (m_texture.loadFromFile(filename)) {
        m_filename = filename;
        m_sprite.setTexture(m_texture);
        sf::IntRect rectSourceSprite(0, 0, 23, 24);
        m_sprite.setTextureRect(rectSourceSprite);
        m_valid = true;
        sf::Vector2f direction(-1, -1);
        m_direction = direction;
        m_velocity = 500.0f;
        return true;
    }
    return false;
}

void Ball::draw(sf::RenderWindow& window) {
    if (m_valid)
        window.draw(m_sprite);
}

void Ball::move(sf::Vector2f loc) {
    if (m_valid)
        m_sprite.move(loc);
}

void Ball::setPosition(float x, float y) {
    if (m_valid) {
        m_sprite.setPosition(x, y);
        sf::Rect<float> rect(x, y, 23, 24);
        m_rectangle = rect;
    }
}

sf::Vector2f Ball::getPosition() const {
    if (m_valid)
        return m_sprite.getPosition();
    else
        return sf::Vector2f(0, 0);
}

float Ball::getHeight() const {
    return m_sprite.getLocalBounds().height;
}

float Ball::getWidth() const {
    return m_sprite.getLocalBounds().width;
}

void Ball::setScale(float scale) {
    if (m_valid)
        m_sprite.setScale(scale, scale);
}

sf::Vector2f Ball::getDirection() {
    return m_direction;
}

float Ball::getVelocity() {
    return m_velocity;
}

void Ball::checkBounds(sf::Time deltaT, sf::Vector2f platform_bounds) {
    // update rectangle
    sf::Rect<float> rect(m_sprite.getPosition().x, m_sprite.getPosition().y, 23, 24);
    m_rectangle = rect;

    // handle x difference
    float ball_radius = 5.f;
    const auto pos = m_sprite.getPosition();
    const auto delta = deltaT.asSeconds() * m_velocity;
    sf::Vector2f new_pos(pos.x + m_direction.x * delta, pos.y + m_direction.y * delta);

    if (new_pos.x - ball_radius < 0) { // left window edge
        m_direction.x *= -1;
        new_pos.x = 0 + ball_radius;
    } else if (new_pos.x + ball_radius >= 940) { // right window edge
        m_direction.x *= -1;
        new_pos.x = 940 - ball_radius;
    } else if (new_pos.y - ball_radius < 0) { // top of window
        m_direction.y *= -1;
        new_pos.y = 0 + ball_radius;
    } else if (new_pos.y + ball_radius >= 690 && new_pos.x >= platform_bounds.x && new_pos.x <= platform_bounds.y) { // platform collision
        m_direction.y *= -1;
        new_pos.y = 690 - ball_radius;
//        new_pos.y = 700 - ball_radius;
//        m_valid = false;
        std::printf("PLATFORM COLLISION\n");
    } else if (new_pos.y + ball_radius >= 715) { // bottom of window
//        m_direction.y *= -1;
//        new_pos.y = 700 - ball_radius;
        m_valid = false;
    }

    m_sprite.setPosition(new_pos.x, new_pos.y);

}

sf::Rect<float> Ball::getBallRectangle() {
    return m_rectangle;
}

void Ball::bounce(sf::Time deltaT, sf::Rect<float> brickRect) {
    float ball_radius = 5.f;
    const auto pos = m_sprite.getPosition();
    const auto delta = deltaT.asSeconds() * m_velocity;
    sf::Vector2f new_pos(pos.x + m_direction.x * delta, pos.y + m_direction.y * delta);

    if (new_pos.x - ball_radius < 0) { // left brick edge
        m_direction.x *= -1;
        new_pos.x = 0 + ball_radius;
    } else if (new_pos.x + ball_radius >= 940) { // right brick edge
        m_direction.x *= -1;
        new_pos.x = 940 - ball_radius;
    } else if (new_pos.y - ball_radius < 0) { // top of brick
        m_direction.y *= -1;
        new_pos.y = 0 + ball_radius;
    } else if (new_pos.y + ball_radius >= 715) { // bottom of brick
        m_direction.y *= -1;
        new_pos.y = 700 - ball_radius;
    }

    m_sprite.setPosition(new_pos.x, new_pos.y);

}