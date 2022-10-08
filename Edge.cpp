#include "Edge.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the Edge's methods
 **************************************************************************************************/

// Constructor
Edge::Edge(int targetId)
{
    this->targetId = targetId;
    this->nextEdge = nullptr;
    this->weight = 0;
}

// Destructor
Edge::~Edge()
{
    if (this->nextEdge != nullptr)
    {
        delete this->nextEdge;
        this->nextEdge = nullptr;
    }
}

// Getters
int Edge::getTargetId() { return this->targetId; }
Edge *Edge::getNextEdge() { return this->nextEdge; }
float Edge::getWeight() { return this->weight; }

// Setters
void Edge::setNextEdge(Edge *edge) { this->nextEdge = edge; }
void Edge::setWeight(float weight) { this->weight = weight; }
