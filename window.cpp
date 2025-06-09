#include "window.h"


void Window::addPoint(Node* point) {
    __points.push_back(point);
}

void Window::addObstacle(Obstacle* obstacle) {
    __obstacles.push_back(obstacle);
}


std::vector<Node*>& Window::getPoints() {
    return __points;
}

void Window::addAlgorithm(Algorithm* algorithm) {
    __algorithms.push_back(algorithm);

    static int startXPos = __footerHeadingText.getGlobalBounds().width + 50;
    int randG = rand() % 255;
    int randR = rand() % 255;
    int randB = rand() % (255 - 200 + 1) + 200;

    ToggleButton* algorithmButton = new ToggleButton("On", "Off", __font, ToggleButton::State::OFF);  
    algorithmButton->setSize(sf::Vector2f(60, 20));
    algorithmButton->setPosition(startXPos, getSize().y - __footerBg.getSize().y/2 - 10);
    algorithmButton->setActiveColor(sf::Color(randR, randG, randB));
    algorithmButton->setInactiveColor(sf::Color(randR, randG, randB, 80));
    algorithmButton->setOutlineColor(sf::Color::Black);
    algorithmButton->setOutlineThickness(2);
    __algorithmsButtons.push_back(algorithmButton);

    startXPos += algorithmButton->getSize().x + 10;

    sf::Text algorithmText(algorithm->getName(), __font, 15);
    algorithmText.setFillColor(sf::Color::Black);
    algorithmText.setPosition(startXPos, getSize().y - __footerBg.getSize().y/2 - 8);
    startXPos += algorithmText.getGlobalBounds().width + 10;
    __algorithmsText.push_back(algorithmText);

    startXPos += algorithmText.getGlobalBounds().width + 30;
}

void Window::drawPath(std::vector<Node*> path, sf::Color color) {
    if (path.empty() && path.size() < 2) return;

    for (size_t i = 1; i < path.size(); ++i) {
        sf::Vertex line[] = {
            sf::Vertex(path.at(i-1)->getPosition(), color),
            sf::Vertex(path.at(i)->getPosition(), color)
        };
        draw(line, 2, sf::Lines);
    }
}

void Window::drawTree(std::vector<Node*>& tree, sf::Color color) {
    if (tree.empty()) return;

    Node* aux = tree.at(tree.size()-1);
    while (aux->getParent()) {
        sf::Vertex line[] = {
            sf::Vertex(aux->getPosition(), color),
            sf::Vertex(aux->getParent()->getPosition(), color)
        };
        draw(line, 2, sf::Lines);
        aux = aux->getParent();
    }
}

void Window::printIterations() {
    int winWidth = getSize().x;

    sf::String str = "Iterations: [";
    if (__algorithms.empty()) {
        str += "-";
    } else {        
        for (int i = 0; i < __algorithms.size(); i++) {
            if (!__algorithmsButtons.at(i)->getState()) {
                str += "off";
            } else {
                str += std::to_string(__algorithms.at(i)->getIterations());
            }

            if (i != __algorithms.size() - 1) {
                str += ", ";
            }
        }
    }
    str += "]";

    __iterationsCounterText.setFont(__font);
    __iterationsCounterText.setString(str);
    __iterationsCounterText.setCharacterSize(11);
    float textWidth = __iterationsCounterText.getGlobalBounds().width;
    __iterationsCounterText.setFillColor(sf::Color::Black);
    __iterationsCounterText.setPosition(winWidth - textWidth -10, 10);

    draw(__iterationsCounterText);
}

void Window::printPathDistance() {
    int winWidth = getSize().x;

    sf::String str = "Path distance: [";
    if (__algorithms.empty()) {
        str += "-";
    } else {
        for (int i = 0; i < __algorithms.size(); i++) {
            if (!__algorithmsButtons.at(i)->getState()) {
                str += "off";
            } else {
                str += fixNumberPrecision(__algorithms.at(i)->getPathDistance(), 2);
            }

            if (i != __algorithms.size() - 1) {
                str += ", ";
            }
        }
    }
    str += "]";

    __pathDistanceText.setFont(__font);
    __pathDistanceText.setString(str);
    __pathDistanceText.setCharacterSize(11);
    float textWidth = __pathDistanceText.getGlobalBounds().width;
    __pathDistanceText.setFillColor(sf::Color::Black);
    __pathDistanceText.setPosition(winWidth - textWidth -10, 30);

    draw(__pathDistanceText);
}

void Window::paintHeader() {
    draw(__headerBg);

    __playButton->draw(*this);

    if (__isErasingCanvas) {
        sf::RectangleShape eraserIcon(sf::Vector2f(90, 30));
        eraserIcon.setPosition(getSize().x/2 - eraserIcon.getSize().x/2,
                               __headerBg.getSize().y/2 - eraserIcon.getSize().y/2);
        eraserIcon.setFillColor(sf::Color::Yellow);
        eraserIcon.setOutlineColor(sf::Color::Black);
        eraserIcon.setOutlineThickness(1);
        
        sf::Text eraserText("Eraser ON", __font, eraserIcon.getSize().y * 0.6);
        eraserText.setPosition(
            eraserIcon.getPosition().x + eraserIcon.getSize().x/2 - eraserText.getGlobalBounds().width/2,
            eraserIcon.getPosition().y + eraserText.getGlobalBounds().height/2 - eraserText.getGlobalBounds().height/4
        );
        eraserText.setFillColor(sf::Color::Black);

        draw(eraserIcon);
        draw(eraserText);
    }

    printIterations();
    printPathDistance();
}

void Window::paintCanvas() {
    for (int i = 0; i < __obstacles.size(); ++i) {
        __obstacles.at(i)->draw(*this);
    }
    
    bool drawPathCondition = !__isErasingCanvas && !__algorithms.empty();

    std::cout << "path[0]: " << __algorithms.at(0)->getPath().at(0)->getPosition().x << std::endl;
    std::cout << "path[1]: " << __algorithms.at(1)->getPath().at(0)->getPosition().x << std::endl;
    for (int i = 0; drawPathCondition && i < __algorithms.size(); i++) {
        if (!__algorithmsButtons.at(i)->getState()) continue;


        std::vector<Node*> path = __algorithms.at(i)->getPath();
        drawPath(__algorithms.at(i)->getPath(), __algorithmsButtons.at(i)->getFillColor());
    }

    if (__points.size() >= 2) {
        __points.at(0)->setFillColor(sf::Color::Green);
        __points.at(0)->setText("Start");
        __points.at(__points.size()-1)->setFillColor(sf::Color::Magenta);
        __points.at(__points.size()-1)->setText("Goal");
    } 
    
    for (int i = 0; i < __points.size(); ++i) { 
        if (__points.size() < 2 || (i > 0 && i < __points.size()-1)) {
            std::string numberStr = std::to_string(i);
            __points.at(i)->setText(numberStr);
            __points.at(i)->setFillColor(sf::Color::White); 
        }
        __points.at(i)->draw(*this);
    }

}

void Window::paintFooter() {
    draw(__footerBg);

    if (__algorithms.empty()) {
        __footerHeadingText.setString("No algorithms available");
        __footerHeadingText.setFillColor(sf::Color::Yellow);
        draw(__footerHeadingText);
        __footerHeadingText.setFillColor(sf::Color::Black);

        return;
    }

    for (const auto& button : __algorithmsButtons) {
        button->draw(*this);
    }   
    for (const auto& text : __algorithmsText) {
        draw(text);
    }


    draw(__footerHeadingText);
}

void Window::paint() {
    clear();

    paintHeader();    
    paintCanvas();
    paintFooter();

    display();
}

Window::Window(int width, int height, sf::String title) 
: sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close) {


    __points = std::vector<Node*>();
    __obstacles = std::vector<Obstacle*>();
    __algorithms = std::vector<Algorithm*>();
    deletedElements = std::vector<canvasElement*>();

    try {
        __font.loadFromFile("assets/arial.ttf");
    } catch(const std::exception& e)
    {
        std::cerr << "Error loading font" << '\n';
    }

    __headerBg.setSize(sf::Vector2f(getSize().x, 50));
    __headerBg.setPosition(0, 0);
    __headerBg.setFillColor(sf::Color(100, 100, 100)); // Gray color

    __playButton = new ToggleButton("Play", "Stop", __font, ToggleButton::State::ON);
    __playButton->setSize(sf::Vector2f(100, 30));
    __playButton->setPosition(10, 10);
    __playButton->setInactiveColor(sf::Color(180, 20, 0));
    __playButton->setActiveColor(sf::Color(20, 180, 0));

    __footerBg.setSize(sf::Vector2f(getSize().x, 50));
    __footerBg.setPosition(0, getSize().y - __footerBg.getSize().y);
    __footerBg.setFillColor(sf::Color(100, 100, 100)); // Gray color

    __footerHeadingText.setFont(__font);
    __footerHeadingText.setString("Algorithm selector");
    __footerHeadingText.setCharacterSize(20);
    __footerHeadingText.setFillColor(sf::Color::Black);
    __footerHeadingText.setPosition(10, getSize().y - __footerBg.getSize().y/2 - 10);

    srand(time(0));
}

void Window::act(sf::Vector2i mousePos, sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) manageMouseEvents(mousePos, event.mouseButton);
    else if (event.type == sf::Event::KeyPressed) manageKeyboardEvents(event.key);

    if (event.type == sf::Event::MouseButtonReleased) {
        if (__isAddingObstacle) {
            __isAddingObstacle = false;
            __obstacles.back()->setOutlineThickness(0);
        }
    }

    if (__isAddingObstacle) {
        __obstacles.back()->setOutlineThickness(2);
        __obstacles.back()->setSize(sf::Vector2f(mousePos.x - __obstacles.back()->getPosition().x,
                                    mousePos.y - __obstacles.back()->getPosition().y));
    }
}

void Window::startAlgorithms() {
    for (int i = 0;!__algorithms.empty() && i < __algorithms.size(); ++i) {
        if (__algorithmsButtons.at(i)->getState()) {
            std::cout << "Running alg: " << __algorithms.at(i)->getName() << std::endl;
            __algorithms.at(i)->setPoints(__points);
            __algorithms.at(i)->setObstacles(__obstacles);
            __algorithms.at(i)->run();
        }
    }

    if (!__playButton->getState()) __playButton->toggle();
}

bool Window::checkIfPlayable() {
    __playButton->toggle();
    if (__playButton->getState() == ToggleButton::State::OFF) return true;
    if (__points.size() < 2) return true;

    return false;
}

void Window::manageMouseEvents(sf::Vector2i mousePos, sf::Event::MouseButtonEvent btnCode) {
    if (__playButton->isClicked(mousePos) && checkIfPlayable()) {
        startAlgorithms();
        return;
    }

    for (auto& button : __algorithmsButtons) {
        if (button->isClicked(mousePos)) {
            button->toggle();
            return;    
        }
    }

    // Canvas events
    if (mousePos.y > 50 && mousePos.y < getSize().y - 50) {
        if (btnCode.button == sf::Mouse::Button::Left) {
            if (__isErasingCanvas) {
                for (auto& point : __points) {
                    if (point->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        __points.erase(
                            std::remove(__points.begin(), __points.end(), point),
                            __points.end()
                        );
                        deletedElements.push_back(point);
                        return;
                    }
                }

                for (auto& obstacle : __obstacles) {
                    if (obstacle->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        __obstacles.erase(
                            std::remove(__obstacles.begin(), __obstacles.end(), obstacle),
                            __obstacles.end()
                        );
                        deletedElements.push_back(obstacle);
                        return;
                    }
                }
            }

            if (__isAddingObstacle) return;
            if (__isErasingCanvas) return;
    
            //check if the point is inside an obstacle
            for (auto& obstacle : __obstacles) {
                if (obstacle->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return;
                }
            }
            for (auto& point : __points) {
                if (point->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return;
                }
            }


            Node* point = new Node(mousePos.x, mousePos.y);

            point->setFont(__font);
            addPoint(point);

            return;
        } 

        if (btnCode.button == sf::Mouse::Button::Right) {
            if (__isAddingObstacle) return;
            if (__isErasingCanvas) return;

            __isAddingObstacle = true;
            Obstacle* obstacle = new Obstacle(mousePos.x, mousePos.y);
            
            obstacle->setFont(__font);
            addObstacle(obstacle);

            return;
        }
    }
}

void Window::manageKeyboardEvents(sf::Event::KeyEvent keyCode) {
    if (keyCode.code == sf::Keyboard::Space && checkIfPlayable()) {
        startAlgorithms();
        return;
    }
    
    if (keyCode.code == sf::Keyboard::Delete) {
        __points.clear();
        __obstacles.clear();
    }

    if (keyCode.code == sf::Keyboard::E) {
        __isErasingCanvas = !__isErasingCanvas;
    }
}

sf::String Window::fixNumberPrecision(float number, int precision) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << number;
    return ss.str();
}


Window::~Window() {
    delete __playButton;    

    for (auto& point : deletedElements) {
        delete point;
    }
    deletedElements.clear();
    
    for (auto button : __algorithmsButtons) {
        delete button;
    }
    __algorithmsButtons.clear();

    for (auto algorithm : __algorithms) {
        delete algorithm;
    }
    __algorithms.clear();

    for (auto obstacle : __obstacles) {
        delete obstacle;
    }
    __obstacles.clear();

    for (auto point : __points) {
        delete point;
    }
    __points.clear();

    __font.~Font();
}