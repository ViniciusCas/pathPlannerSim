#ifndef RRT_H
#define RRT_H

#include "algorithm.h"

class RRT : public Algorithm {

private:
    std::vector<Node*> path;
    std::vector<std::vector<Node*>> tree;
    std::vector<Node*> points;
    std::vector<Obstacle*> obstacles;
    int iterations;
    float pathDistance;
    const std::string name;
    float stepSize = 10;

public:
    static const int MAX_ITERATIONS = 5 * 10e3;

    RRT(std::vector<Node*>& points, std::vector<Obstacle*>& obstacles, float stepSize = 150); 
    RRT();
    ~RRT() override;
    
    // RRT(RRT&&) = default;
    // RRT& operator=(RRT&&) = default;

    virtual void run() override;
    virtual std::vector<Node*> getPath() override;
    virtual std::vector<std::vector<Node*>>& getTrees() override;
    virtual int getIterations() override;
    virtual float getPathDistance() override;
    virtual std::string getName() override;

    virtual void setPoints(std::vector<Node*>& points) override;
    virtual void setObstacles(std::vector<Obstacle*>& obstacles) override;

    Node* operator=(Node* node) {
        return node;
    }
private:
    Node* generateRandomPoint();
    Node* findNearest(Node* point, std::vector<Node*>& tree);
    Node* steer(Node* nearest, Node* randomPoint);
    bool collides(Node* point);
    float distance(Node* a, Node* b);
};

#endif // RRT_H
