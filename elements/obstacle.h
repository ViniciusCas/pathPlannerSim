#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>
#include "canvasElement.h"

class Obstacle : public sf::RectangleShape, public canvasElement {
private:
    sf::Text __text;
public:
    Obstacle(float x, float y, float width, float height);
    Obstacle(float x, float y);
    ~Obstacle();

    void draw(sf::RenderWindow& window);
    void setFont(sf::Font& font);
    void setText(sf::String text);
};

#endif