#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#include <SFML/Graphics.hpp>

// namespace ToggleButton {

class ToggleButton : public sf::RectangleShape {
    public:
        enum State {
            ON = true,
            OFF = false
        };

        ToggleButton(sf::String onText, sf::String offText, sf::Font& font, State startState = State::OFF);
        ~ToggleButton();
        void draw(sf::RenderWindow& window);    
        bool isClicked(sf::Vector2i mousePos);
        void toggle();
        State getState();

        void setInactiveColor(sf::Color color);
        void setActiveColor(sf::Color color);
        void setTextColor(sf::Color color);
        void setPosition(const sf::Vector2f& position);
        void setPosition(const float x, const float y);
        void setSize(const sf::Vector2f& size);
    private:

        sf::Text __text;
        sf::String __onText;
        sf::String __offText;
        State __state;

        sf::Color __activeColor;
        sf::Color __inactiveColor;
        sf::Color __textColor;
};
// }   // namespace ToggleButton
#endif