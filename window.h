#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include "elements/togglebutton.h"
#include "elements/node.h"
#include "elements/obstacle.h"
#include "../pathfinding/algorithm.h"
#include "../pathfinding/RRT.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>

class Window : public sf::RenderWindow {
private:
    void drawPath(std::vector<Node*> path, sf::Color color);
    void drawTree(std::vector<Node*>& tree, sf::Color color);

    void printIterations();
    void printPathDistance();

    void paintHeader();
    void paintCanvas();
    void paintFooter();
    void manageMouseEvents(sf::Vector2i mousePos, sf::Event::MouseButtonEvent btnCode);
    void manageKeyboardEvents(sf::Event::KeyEvent keyCode);
    void startAlgorithms();
    bool checkIfPlayable();

    sf::String fixNumberPrecision(float number, int precision);

    sf::Font __font;
    
    // GUI elements
        // Header elements
    sf::RectangleShape __headerBg;
    ToggleButton *__playButton;
    sf::Text __iterationsCounterText;
    sf::Text __pathDistanceText;

        // Footer elements
    sf::RectangleShape __footerBg;
    sf::Text __footerHeadingText;
    std::vector<sf::Text> __algorithmsText;
    std::vector<ToggleButton*> __algorithmsButtons;

    //algorithm elements
    std::vector<Node*> __points;
    std::vector<Obstacle*> __obstacles;
    std::vector<Algorithm*> __algorithms;
    std::vector<canvasElement*> deletedElements;

    bool __isErasingCanvas = false;
    bool __isAddingObstacle = false;
public:
    Window(int width, int height, sf::String title);
    ~Window();

    std::vector<Node*>& getPoints();
    void addPoint(Node* point);
    void addObstacle(Obstacle* obstacle);
    void addAlgorithm(Algorithm* algorithm);

    void act(sf::Vector2i mousePos, sf::Event event);

    void paint();
};

#endif