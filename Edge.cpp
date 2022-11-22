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
    this->targetId = -1;
    this->nextEdge = nullptr;
    this->weight = 0;
}

// Getters
int Edge::getTargetId() { return this->targetId; }
Edge *Edge::getNextEdge() { return this->nextEdge; }
float Edge::getWeight() { return this->weight; }

// Setters
void Edge::setNextEdge(Edge *edge) { this->nextEdge = edge; }
void Edge::setWeight(float weight) { this->weight = weight; }
