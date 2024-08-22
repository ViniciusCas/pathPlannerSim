#include "node.h"

Node::Node() : sf::CircleShape() {
    setRadius(5);
    setOrigin(5, 5);
    setPosition(0, 0);
    
    __text.setFillColor(sf::Color::White);
}

Node::Node(float x, float y) : sf::CircleShape() {
    setRadius(5);
    setOrigin(5, 5);
    setPosition(x, y);

    __text.setFillColor(sf::Color::White);
}

Node::Node(sf::Vector2f position, float radius, sf::String &text, sf::Font &font)
    : sf::CircleShape(radius) {
    setRadius(radius);
    setOrigin(radius, radius);
    setPosition(position);

    __text.setFont(font);
    __text.setString(text);
}

void Node::draw(sf::RenderWindow& window) {
    window.draw(*this);

    __text.setFillColor(sf::Color::White);
    __text.setCharacterSize(8);
    __text.setPosition(getPosition().x + getRadius() - __text.getGlobalBounds().width/2,
                       getPosition().y + getRadius() - __text.getGlobalBounds().height/4);
    window.draw(__text);
}

void Node::setFont(sf::Font& font) {
    __text.setFont(font);
}

void Node::setText(sf::String text) {
    __text.setString(text);
}

void Node::setParent(Node* parent) {
    __parent = parent;
}

Node* Node::getParent() {
    return __parent;
}