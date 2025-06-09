#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "../elements/node.h"
#include "../elements/obstacle.h"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>

class Algorithm {
private:
    
public:
    virtual ~Algorithm() = 0;

    virtual void run() = 0;
    virtual std::vector<Node*> getPath() = 0;
    virtual std::vector<std::vector<Node*>> &getTrees() = 0;
    virtual int getIterations() = 0;
    virtual float getPathDistance() = 0;
    virtual std::string getName() = 0;


    virtual void setPoints(std::vector<Node*>& points) = 0;
    virtual void setObstacles(std::vector<Obstacle*>& obstacles) = 0;
};

#endif // ALGORITHM_H   