//
// Created by Jacob Lattie on 2018-12-29.
//

#pragma once

#include <SFML/Graphics.hpp>


class Brick {
public:
    Brick();
    virtual bool load(const std::string& filename);

    virtual void draw(sf::RenderWindow& window);

    virtual void update(float deltaT) {}

    virtual void setPosition(float x, float y);

    virtual sf::Vector2f getPosition() const;

    virtual float getHeight() const;

    virtual float getWidth() const;

    virtual void setScale(float scale);

    virtual bool checkHit(sf::Rect<float> ball_Rect);

    sf::Rect<float> getBrickRectangle();

private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    std::string m_filename;
    bool m_valid = false;
    int m_health = 4;
    sf::Rect<float> m_rectangle;
};
