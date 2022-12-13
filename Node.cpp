#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <cfloat>
#include <climits>
using namespace std;

/**************************************************************************************************
 * Defining the Node's methods
 **************************************************************************************************/

// Construtor
Node::Node(int id, int label)
{
    this->id = id;
    this->label = label;
    this->inDegree = 0;
    this->outDegree = 0;
    this->weight = 0;
    this->firstEdge = nullptr;
    this->lastEdge = nullptr;
    this->nextNode = nullptr;
};

// Destrutor
Node::~Node()
{
    Edge *nextEdge = this->firstEdge;

    while (nextEdge != nullptr)
    {
        Edge *auxEdge = nextEdge->getNextEdge();
        delete nextEdge;
        nextEdge = auxEdge;
    }

    this->id = -1;
    this->label = INT_MIN;
    this->inDegree = 0;
    this->outDegree = 0;
    this->weight = 0;
    this->firstEdge = nullptr;
    this->lastEdge = nullptr;
    this->nextNode = nullptr;
};

// Getters
Edge *Node::getFirstEdge()
{
    return this->firstEdge;
}
Edge *Node::getLastEdge()
{
    return this->lastEdge;
}
int Node::getId() const
{
    return this->id;
}
int Node::getLabel()
{
    return this->label;
}
int Node::getInDegree()
{
    return this->inDegree;
}
int Node::getOutDegree()
{
    return this->outDegree;
}
float Node::getWeight()
{
    return this->weight;
}
Node *Node::getNextNode()
{
    return this->nextNode;
}

// Setters
void Node::setNextNode(Node *nextNode)
{
    this->nextNode = nextNode;
}
void Node::setWeight(float weight)
{
    this->weight = weight;
}

// Métodos de manipulação
//
void Node::insertEdge(int sourceId, int sourceLabel, int targetId, int targetLabel, float weight)
{
    // Verifies whether there are at least one edge in the node
    if (this->firstEdge != nullptr)
    {
        // Allocating the new edge and keeping the integrity of the edge list
        Edge *edge = new Edge(sourceId, sourceLabel, targetId, targetLabel);
        edge->setWeight(weight);
        this->lastEdge->setNextEdge(edge);
        this->lastEdge = edge;
    }
    else
    {
        // Allocating the new edge and keeping the integrity of the edge list
        this->firstEdge = new Edge(sourceId, sourceLabel, targetId, targetLabel);
        this->firstEdge->setWeight(weight);
        this->lastEdge = this->firstEdge;
    }
}

void Node::removeAllEdges()
{
    // Verifies whether there are at least one edge in the node
    if (this->firstEdge != nullptr)
    {
        Edge *next = nullptr;
        Edge *aux = this->firstEdge;
        // Removing all edges of the node
        while (aux != nullptr)
        {
            next = aux->getNextEdge();
            delete aux;
        }
    }
    this->firstEdge = this->lastEdge = nullptr;
}

int Node::removeEdge(int id, bool directed, Node *targetNode)
{
    // Verifies whether the edge to remove is in the node
    if (this->hasEdgeBetween(id))
    {
        Edge *aux = this->firstEdge;
        Edge *previous = nullptr;

        // Searching for the edge to be removed
        while (aux->getTargetId() != id)
        {
            previous = aux;
            aux = aux->getNextEdge();
        }

        // Keeping the integrity of the edge list
        if (previous != nullptr)
            previous->setNextEdge(aux->getNextEdge());
        else
            this->firstEdge = aux->getNextEdge();

        if (aux == this->lastEdge)
            this->lastEdge = previous;

        if (aux->getNextEdge() == this->lastEdge)
            this->lastEdge = aux->getNextEdge();

        delete aux;

        // Verifies whether the graph is directed
        if (directed)
            this->decrementOutDegree();
        else
        {
            this->decrementInDegree();
            targetNode->decrementInDegree();
        }

        return 1;
    }
    return 0;
}

// Outros métodos
//
void Node::incrementInDegree()
{
    this->inDegree++;
}
void Node::incrementOutDegree()
{
    this->outDegree++;
}
void Node::decrementInDegree()
{
    this->inDegree--;
}
void Node::decrementOutDegree()
{
    this->outDegree--;
}

// Métodos auxiliares
//
/*a partir de um vértice, avalia se existe aresta ligando a outro vértice alvo
 *em caso verdadeiro retorna a aresta
 *em caso falso retorna ponteiro nulo
 */
Edge *Node::getEdgeBetween(int targetId)
{
    if (this == nullptr)
        return nullptr;
    else
        for (Edge *auxEdge = this->firstEdge; auxEdge != nullptr; auxEdge = auxEdge->getNextEdge())
        {
            if (auxEdge->getTargetId() == targetId)
                return auxEdge;
        }
    return nullptr;
}
Edge *Node::getEdgeBetweenLabel(int targetLabel)
{
    if (this == nullptr)
        return nullptr;
    else
        for (Edge *auxEdge = this->firstEdge; auxEdge != nullptr; auxEdge = auxEdge->getNextEdge())
        {
            if (auxEdge->getTargetLabel() == targetLabel)
                return auxEdge;
        }
    return nullptr;
}

bool Node::hasEdgeBetween(int targetId)
{
    if (this == nullptr)
        return false;
    else
        return this->getEdgeBetween(targetId) != nullptr;
}
bool Node::hasEdgeBetweenLabel(int targetLabel)
{
    if (this == nullptr)
        return false;
    else
        return this->getEdgeBetweenLabel(targetLabel) != nullptr;
}

float Node::distanceToOtherNode(int targetId)
{
    if (this->id == targetId)
        return 0;
    Edge *edgeBetween = this->getEdgeBetween(targetId);
    if (edgeBetween != nullptr)
        return edgeBetween->getWeight();
    else
        return FLT_MAX;
}

list<SimpleEdge> Node::distanceToConnectedNodes()
{
    list<SimpleEdge> connectedEdges;
    for (Edge *auxEdge = this->firstEdge; auxEdge != nullptr; auxEdge = auxEdge->getNextEdge())
    {
        SimpleEdge simpleEdge;
        simpleEdge.sourceNodeId = this->id;
        simpleEdge.targetNodeId = auxEdge->getTargetId();
        simpleEdge.weight = auxEdge->getWeight();
        connectedEdges.emplace_back(simpleEdge);
    }
    return connectedEdges;
}