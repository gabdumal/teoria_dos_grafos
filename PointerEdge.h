/**************************************************************************************************
 * Implementation of the TAD PointerEdge
 **************************************************************************************************/

#ifndef POINTEREDGE_H_INCLUDED
#define POINTEREDGE_H_INCLUDED

#include "Node.h"

using namespace std;

// Definition of the PointerEdge class
class PointerEdge
{

    // Attributes
private:
    Node *sourceNode;
    Node *targetNode;
    PointerEdge *nextEdge;
    float weight;

public:
    // Constructor
    PointerEdge(Node *sourceNode, Node *targetNode, float weight);
    // Destructor
    ~PointerEdge();
    // Getters
    Node *getSourceNode();
    Node *getTargetNode();
    PointerEdge *getNextEdge();
    float getWeight() const;
    // Setters
    void setNextEdge(PointerEdge *edge);
    void setWeight(float weight);
};

#endif // POINTEREDGE_H_INCLUDED