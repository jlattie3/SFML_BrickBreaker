//
// Created by Jacob Lattie on 2018-12-29.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <functional>
#include <cstdlib>
#include <cmath>

class Ball {
public:
    Ball();
    virtual bool load(const std::string& filename);

    virtual void draw(sf::RenderWindow& window);

    virtual void update(float deltaT) {}

    virtual void setPosition(float x, float y);

    virtual void move(sf::Vector2f);

    virtual sf::Vector2f getPosition() const;

    virtual float getHeight() const;

    virtual float getWidth() const;

    virtual void setScale(float scale);

    virtual sf::Vector2f getDirection();

    virtual float getVelocity();

    virtual void checkBounds(sf::Time deltaT, sf::Vector2f platform_bounds);

    sf::Rect<float> getBallRectangle();

    void bounce(sf::Time deltaT, sf::Rect<float> brickRect);

private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    std::string m_filename;
    bool m_valid = false;
    sf::Vector2f m_direction;
    float m_velocity;
    sf::Rect<float> m_rectangle;
};