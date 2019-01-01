//
// Created by Jacob Lattie on 2018-12-29.
//

#include "Brick.h"

Brick::Brick() {

}

bool Brick::load(const std::string& filename) {
    if (m_texture.loadFromFile(filename)) {
        m_filename = filename;
        m_sprite.setTexture(m_texture);
        sf::IntRect rectSourceSprite(0, 37, 64, 27);
        m_sprite.setTextureRect(rectSourceSprite);
        m_valid = true;
        return true;
    }
    return false;
}

void Brick::draw(sf::RenderWindow& window) {
    if (m_valid)

            if (m_health == 4) {
                window.draw(m_sprite);
            } else if (m_health == 3) {
                sf::IntRect rectSourceSprite3(0, 37 + 64, 64, 27);
                m_sprite.setTextureRect(rectSourceSprite3);
                window.draw(m_sprite);
            } else if (m_health == 2) {
                sf::IntRect rectSourceSprite2(0, 37 + 64, 64, 27);
                m_sprite.setTextureRect(rectSourceSprite2);
                window.draw(m_sprite);
            } else if (m_health == 1) {
                sf::IntRect rectSourceSprite1(0, 37 + 64 + 64, 64, 27);
                m_sprite.setTextureRect(rectSourceSprite1);
                window.draw(m_sprite);
            } else if (m_health == 0) {
                m_valid = false;
            }
}

void Brick::setPosition(float x, float y) {
    if (m_valid) {
        m_sprite.setPosition(x, y);
        sf::Rect<float> rect(x, y, 128, 52);
        m_rectangle = rect;
    }
}

sf::Vector2f Brick::getPosition() const {
    if (m_valid)
        return m_sprite.getPosition();
    else
        return sf::Vector2f(0, 0);
}

float Brick::getHeight() const {
    return m_sprite.getLocalBounds().height;
}

float Brick::getWidth() const {
    return m_sprite.getLocalBounds().width;
}

void Brick::setScale(float scale) {
    if (m_valid)
        m_sprite.setScale(scale, scale);
}

bool Brick::checkHit(sf::Rect<float> ball_Rect) {
    if (ball_Rect.intersects(m_rectangle)) {
        std::printf("BRICK COLLISION");
        m_health--;
        return true;
    }
    return false;
}

sf::Rect<float> Brick::getBrickRectangle() {
    return m_rectangle;
}

