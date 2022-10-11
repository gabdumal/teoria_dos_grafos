#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
 **************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weightedEdge, bool weightedNode)
{
    this->order = order;
    this->directed = directed;
    this->weightedEdge = weightedEdge;
    this->weightedNode = weightedNode;
    this->firstNode = this->lastNode = nullptr;
    this->numberEdges = 0;
    this->nodeIdCounter = 0;
}

// Destructor
Graph::~Graph()
{
    Node *nextNode = this->firstNode;

    while (nextNode != nullptr)
    {
        nextNode->removeAllEdges();
        Node *auxNode = nextNode->getNextNode();
        delete nextNode;
        nextNode = auxNode;
    }
}

// Getters
int Graph::getOrder() { return this->order; }
int Graph::getNumberEdges() { return this->numberEdges; }
bool Graph::getDirected() { return this->directed; }
bool Graph::getWeightedEdge() { return this->weightedEdge; }
bool Graph::getWeightedNode() { return this->weightedNode; }
Node *Graph::getFirstNode() { return this->firstNode; }
Node *Graph::getLastNode() { return this->lastNode; }

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/
Node *Graph::insertNode(int label)
{
    Node *newNode = new Node(nodeIdCounter++, label);
    if (lastNode == nullptr)
    {
        firstNode = newNode;
        lastNode = newNode;
    }
    else
    {
        lastNode->setNextNode(newNode);
        lastNode = newNode;
    }
    return newNode;
}

void Graph::insertEdge(int sourceLabel, int targetLabel, float weight)
{
    // Até então, insere apenas arestas direcionadas
    // Verificar se aresta já existe, para impedir duplicidade
    // Incrementar in and out degrees

    Node *sourceNode = getNodeByLabel(sourceLabel);
    if (sourceNode == nullptr)
        sourceNode = insertNode(sourceLabel);

    Node *targetNode = getNodeByLabel(targetLabel);
    if (targetNode == nullptr)
        targetNode = insertNode(targetLabel);

    sourceNode->insertEdge(targetNode->getId(), weight);
    numberEdges++;
}

void Graph::removeNode(int id)
{
}

bool Graph::searchNode(int id)
{
    Node *nextNode = this->firstNode;
    while (nextNode != nullptr)
    {
        if (nextNode->getId() == id)
            return true;
        nextNode = nextNode->getNextNode();
    }
    return false;
}

Node *Graph::getNodeById(int id)
{
    Node *nextNode = this->firstNode;
    while (nextNode != nullptr)
    {
        if (nextNode->getId() == id)
            return nextNode;

        nextNode = nextNode->getNextNode();
    }
    return nullptr;
}

Node *Graph::getNodeByLabel(int label)
{
    Node *nextNode = this->firstNode;
    while (nextNode != nullptr)
    {
        if (nextNode->getLabel() == label)
            return nextNode;

        nextNode = nextNode->getNextNode();
    }
    return nullptr;
}

// Function that verifies if there is a path between two nodes
bool Graph::depthFirstSearch(int initialId, int targetId)
{
}

void Graph::breadthFirstSearch(ofstream &output_file)
{
}

Graph *Graph::getComplement()
{
}

// A function that returns a subjacent of a directed graph, which is a graph which the arcs have opposite directions to the original graph
Graph *Graph::getSubjacent()
{
}

bool Graph::connectedGraph()
{
}

bool Graph::hasCircuit()
{
}

float **Graph::floydMarshall()
{
}

float *Graph::dijkstra(int id)
{
}
