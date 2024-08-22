#include "togglebutton.h"
#include <iostream>

ToggleButton::ToggleButton(sf::String onText, sf::String offText, sf::Font& font, State startState) : sf::RectangleShape() {

    __activeColor = sf::Color::Green;
    __inactiveColor = sf::Color::Red;
    __textColor = sf::Color::Black;
    __onText = onText;
    __offText = offText;
    __text.setFont(font);
    __text.setStyle(sf::Text::Bold);
    __text.setFillColor(__textColor);
    
    __state = startState;
    if (startState) {
        setFillColor(__activeColor);
        __text.setString(__onText);
    } else {
        setFillColor(__inactiveColor);
        __text.setString(__offText);
    }
}

void ToggleButton::setPosition(const sf::Vector2f& position) {
    sf::RectangleShape::setPosition(position);
}

void ToggleButton::setPosition(const float x, const float y) {
    sf::RectangleShape::setPosition(x, y);
}

void ToggleButton::setSize(const sf::Vector2f& size) {
    sf::RectangleShape::setSize(size);
}

ToggleButton::~ToggleButton() {
    delete this;
}

void ToggleButton::draw(sf::RenderWindow& window) {
    window.draw(*this);

    __text.setPosition(getPosition().x + this->getSize().x/2 -  __text.getGlobalBounds().width/2,
                       getPosition().y + this->getSize().y/2 - __text.getGlobalBounds().height/2 - 4);
    __text.setCharacterSize(getGlobalBounds().height * 0.75);
    
    window.draw(__text);
}

bool ToggleButton::isClicked(sf::Vector2i mousePos) {
    if (getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        return true;
    }
    return false;
}

ToggleButton::State ToggleButton::getState() {
    return __state;
}

void ToggleButton::toggle() {
    __state = State(!__state);
    if (__state) {
        setFillColor(__activeColor);
        __text.setString(__onText);
    } else {
        setFillColor(__inactiveColor);
        __text.setString(__offText);
    }
    setPosition(getPosition());
}

void ToggleButton::setInactiveColor(sf::Color color) {
    __inactiveColor = color;
    if (!__state) {
        setFillColor(__inactiveColor);
    }
}

void ToggleButton::setActiveColor(sf::Color color) {
    __activeColor = color;
    if (__state) {
        setFillColor(__activeColor);
    }
}

void ToggleButton::setTextColor(sf::Color color) {
    __textColor = color;
    __text.setFillColor(__textColor);
}