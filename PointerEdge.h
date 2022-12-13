/**************************************************************************************************
 * Implementation of the TAD PointerEdge
 **************************************************************************************************/

#ifndef POINTEREDGE_H_INCLUDED
#define POINTEREDGE_H_INCLUDED

#include "Node.h"

using namespace std;

// Definição da classe PointerEdge (Aresta com ponteiro)
class PointerEdge
{

    // Atributos
private:
    Node *sourceNode;
    Node *targetNode;
    PointerEdge *nextEdge;
    float weight;

public:
    // Construtor
    PointerEdge(Node *sourceNode, Node *targetNode, float weight);

    // Destrutor
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