#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics.hpp>
#include "canvasElement.h"

class Node : public sf::CircleShape, public canvasElement {
private:
    sf::Text __text;
    Node* __parent;

public:
    Node();
    Node(float x, float y);
    Node(sf::Vector2f position, float radius, sf::String &text, sf::Font &font);

    virtual void draw(sf::RenderWindow& window) override;
    virtual void setFont(sf::Font& font) override;
    virtual void setText(sf::String text) override;  
    
    void setParent(Node* next);
    Node* getParent();

};

#endif