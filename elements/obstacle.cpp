#include "obstacle.h"

Obstacle::Obstacle(float x, float y, float width, float height) {
    this->setPosition(x, y);
    this->setSize(sf::Vector2f(width, height));
    this->setFillColor(sf::Color::Blue);
}

Obstacle::Obstacle(float x, float y) {
    this->setPosition(x, y);
    this->setFillColor(sf::Color::Blue);
}

void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(*this);
    __text.setCharacterSize(getSize().y * 0.4);
    __text.setPosition(getPosition().x + getSize().x/2 - __text.getGlobalBounds().width/2,
                       getPosition().y + getSize().y/2 - __text.getGlobalBounds().height/4);
    window.draw(__text);
}

void Obstacle::setFont(sf::Font& font) {
    __text.setFont(font);
}

void Obstacle::setText(sf::String text) {
    __text.setString(text);
    
}

Obstacle::~Obstacle() {}
