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
        sf::IntRect rectSourceSprite(0, 0, 23, 23);
        m_sprite.setTextureRect(rectSourceSprite);
        m_valid = true;
        sf::Vector2f direction(0, 1);
        m_direction = direction;
        m_velocity = 30.0f;
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
    if (m_valid)
        m_sprite.setPosition(x, y);
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

void Ball::checkBounds() {
    // handle x difference
    float diff = m_sprite.getGlobalBounds().left;
    if (diff < 0) {
        m_sprite.move(-diff, 0);
    }
    diff = m_sprite.getGlobalBounds().left + m_sprite.getLocalBounds().width - 896;
    if (diff > 0) {
        m_sprite.move(-diff, 0);
    }
    // handle y difference
    diff = m_sprite.getGlobalBounds().top;
    if (diff < 0) {
        m_sprite.move(0, -diff);
    }
    diff = m_sprite.getGlobalBounds().top + m_sprite.getLocalBounds().height - 700;
    if (diff > 0) {
        m_sprite.move(0, -diff);
    }
}