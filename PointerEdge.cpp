#include "PointerEdge.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the PointerEdge's methods
 **************************************************************************************************/

// Constructor
PointerEdge::PointerEdge(Node *sourceNode, Node *targetNode, float weight)
{
    this->sourceNode = sourceNode;
    this->targetNode = targetNode;
    this->nextEdge = nullptr;
    this->weight = weight;
}

// Destructor
PointerEdge::~PointerEdge()
{
    this->sourceNode = nullptr;
    this->targetNode = nullptr;
    this->nextEdge = nullptr;
    this->weight = 0;
}

// Getters
Node *PointerEdge::getSourceNode() { return this->sourceNode; }
Node *PointerEdge::getTargetNode() { return this->targetNode; }
PointerEdge *PointerEdge::getNextEdge() { return this->nextEdge; }
float PointerEdge::getWeight() const { return this->weight; }

// Setters
void PointerEdge::setNextEdge(PointerEdge *edge) { this->nextEdge = edge; }
void PointerEdge::setWeight(float weight) { this->weight = weight; }
