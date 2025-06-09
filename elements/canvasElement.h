#ifndef CANVASELEMENT_H
#define CANVASELEMENT_H

#include <SFML/Graphics.hpp>

class canvasElement {
private:
    /* data */
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void setFont(sf::Font& font) = 0;
    virtual void setText(sf::String text) = 0;

};

#endif
