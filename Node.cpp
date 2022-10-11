#include "Node.h"
#include "Edge.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the Node's methods
 **************************************************************************************************/

// Constructor
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

// Destructor
Node::~Node()
{
    Edge *nextEdge = this->firstEdge;

    while (nextEdge != nullptr)
    {
        Edge *auxEdge = nextEdge->getNextEdge();
        delete nextEdge;
        nextEdge = auxEdge;
    }
};

// Getters
Edge *Node::getFirstEdge() { return this->firstEdge; }
Edge *Node::getLastEdge() { return this->lastEdge; }
int Node::getId() { return this->id; }
int Node::getLabel() { return this->label; }
int Node::getInDegree() { return this->inDegree; }
int Node::getOutDegree() { return this->outDegree; }
float Node::getWeight() { return this->weight; }
Node *Node::getNextNode() { return this->nextNode; }

// Setters
void Node::setNextNode(Node *nextNode) { this->nextNode = nextNode; }
void Node::setWeight(float weight) { this->weight = weight; }

// Other methods
void Node::insertEdge(int targetId, float weight)
{
    // Verifies whether there are at least one edge in the node
    if (this->firstEdge != nullptr)
    {
        // Allocating the new edge and keeping the integrity of the edge list
        Edge *edge = new Edge(targetId);
        edge->setWeight(weight);
        this->lastEdge->setNextEdge(edge);
        this->lastEdge = edge;
    }
    else
    {
        // Allocating the new edge and keeping the integrity of the edge list
        this->firstEdge = new Edge(targetId);
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
    if (this->searchEdge(id))
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

bool Node::searchEdge(int targetId)
{
    // Verifies whether there are at least one edge in the node
    if (this->firstEdge != nullptr)
    {
        // Searching for a specific edge of target id equal to target id
        for (Edge *aux = this->firstEdge; aux != nullptr; aux = aux->getNextEdge())
            if (aux->getTargetId() == targetId)
                return true;
    }

    return false;
}

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

Edge *Node::hasEdgeBetween(int targetId)
{

    for (Edge *auxEdge = this->firstEdge; auxEdge != nullptr; auxEdge = auxEdge->getNextEdge())
    {
        if (auxEdge->getTargetId() == targetId)
            return auxEdge;
    }
    return nullptr;
}
