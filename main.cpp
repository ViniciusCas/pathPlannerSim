#include "window.h"
#include "pathfinding/RRT.h"

using namespace std;

int main(){
    
    Window* win = new Window(800, 600, "RRT");

    win->addAlgorithm(new RRT());
    win->addAlgorithm(new RRT());

    while (win->isOpen()) {
        sf::Event event;
        if (win->pollEvent(event)) {
            if (event.type == sf::Event::Closed) break;

            win->act(sf::Mouse::getPosition(*win), event);
        }
        win->paint();
    }   
    
    win->close();

    return 0;
}