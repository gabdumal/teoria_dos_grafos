#include "Edge.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the Edge's methods
 **************************************************************************************************/

// Constructor
Edge::Edge(int sourceId, int sourceLabel, int targetId, int targetLabel)
{
    this->sourceId = sourceId;
    this->targetId = targetId;
    this->targetLabel = targetLabel;
    this->nextEdge = nullptr;
    this->weight = 0;
}

// Destructor
Edge::~Edge()
{
    this->sourceId = -1;
    this->targetId = -1;
    this->targetLabel = -1;
    this->nextEdge = nullptr;
    this->weight = 0;
}

// Getters
int Edge::getSourceId() { return this->sourceId; }
int Edge::getTargetId() { return this->targetId; }
int Edge::getTargetLabel() { return this->targetLabel; }
Edge *Edge::getNextEdge() { return this->nextEdge; }
float Edge::getWeight() const { return this->weight; }

// Setters
void Edge::setNextEdge(Edge *edge) { this->nextEdge = edge; }
void Edge::setWeight(float weight) { this->weight = weight; }
