#include "RRT.h"
#include <iostream>


RRT::RRT(std::vector<Node*>& points, std::vector<Obstacle*>& obstacles, float stepSize) 
: name("RRT") {
    this->points = points; 
    this->obstacles = obstacles;
    this->stepSize = stepSize;

    iterations = 0;
    pathDistance = 0;
}

RRT::RRT() : name("RRT") {
    iterations = 0;
    pathDistance = 0;
}

RRT::~RRT() {}

void RRT::run() {
    if (points.size() < 2) return;

    tree = std::vector<std::vector<Node*>>(points.size()-1);


    iterations = 0;
    for (int i = 1; i < points.size(); i++) {
        Node* start = points.at(i-1);
        Node* goal = points.at(i); 

        tree[i-1] = std::vector<Node*>();
        tree[i-1].push_back(start);
        
        while (iterations < MAX_ITERATIONS) {
            Node* randomPoint = generateRandomPoint();
            Node* nearest = findNearest(randomPoint, tree[i-1]);
            Node* newPoint = steer(nearest, randomPoint);

            if (!collides(newPoint)) {
                tree[i-1].push_back(newPoint);
                if (distance(newPoint, goal) < stepSize) {
                    tree[i-1].push_back(newPoint);

                    goal->setParent(newPoint);
                    tree[i-1].push_back(goal);
                    break;
                }
            }
            iterations++;   
        }
    }
}

Node* RRT::generateRandomPoint() {
    int x = rand() % 800;
    int y = rand() % (550 - 50 + 1) + 50;
    return new Node(x, y);
}

Node* RRT::findNearest(Node* point, std::vector<Node*>& tree) {
    Node* nearest = tree[0];
    float minDist = distance(point, tree[0]);
    
    int i = 0;
    for (auto& node : tree) {
        float dist = distance(point, node);
        if (dist < minDist) {
            minDist = dist;
            nearest = node;
        }
    }
    return nearest;
}

std::vector<Node*> RRT::getPath() {
    path = std::vector<Node*>();
    pathDistance = 0;

    if (points.size() < 2) return path;    

    for (int i = 1; i < points.size(); i++) {
        Node* start = points.at(i-1);
        Node* goal = points.at(i);

        path.push_back(goal);

        Node* aux = goal;
        while (aux->getParent() != start) {
            pathDistance += distance(aux, aux->getParent());
            aux = aux->getParent();
            path.push_back(aux);
        }
        path.push_back(start);
    }

    // for (auto a: path) {
    //     std::cout << a->getPosition().x << " " << a->getPosition().y << std::endl;
    // }

    return path;
}


//TODO: correct this to return only a std::vector<Node*> instead of std::vector<std::vector<Node*>>
std::vector<std::vector<Node*>>& RRT::getTrees() {
    return tree;
}

int RRT::getIterations() {
    return iterations;
}

float RRT::getPathDistance() {
    return pathDistance;
}

std::string RRT::getName() {
    return name;
}

void RRT::setPoints(std::vector<Node*>& points) {
    this->points = points;
}

void RRT::setObstacles(std::vector<Obstacle*>& obstacles) {
    this->obstacles = obstacles;
}

Node* RRT::steer(Node* nearest, Node* randomPoint) {
    float dist = distance(nearest, randomPoint);
    if (dist < stepSize) {
        randomPoint->setParent(nearest);
        return randomPoint;
    }
    float theta = atan2(randomPoint->getPosition().y - nearest->getPosition().y, 
                        randomPoint->getPosition().x - nearest->getPosition().x);
    float x = nearest->getPosition().x + 10 * cos(theta);
    float y = nearest->getPosition().y + 10 * sin(theta);

    Node* newPoint = new Node(x, y);
    
    newPoint->setParent(nearest);
    
    return newPoint;    
}

bool RRT::collides(Node* point) {
    for (const auto obstacle : obstacles) {
        if ((*obstacle).getGlobalBounds().contains(point->getPosition())) {
            return true;
        }
    }
    return false;
}

float RRT::distance(Node* a, Node* b) {
    return sqrt(pow(a->getPosition().x - b->getPosition().x, 2) 
            + pow(a->getPosition().y - b->getPosition().y, 2));
}






