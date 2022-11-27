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
        Node *auxNode = nextNode->getNextNode();
        delete nextNode;
        nextNode = auxNode;
    }

    this->order = 0;
    this->numberEdges = 0;
    this->nodeIdCounter = 0;
    this->firstNode = nullptr;
    this->lastNode = nullptr;
}

// Getters
int Graph::getOrder()
{
    return this->order;
}
int Graph::getNodeIdCounter()
{
    return this->nodeIdCounter;
}
int Graph::getNumberEdges()
{
    return this->numberEdges;
}
bool Graph::getDirected()
{
    return this->directed;
}
bool Graph::getWeightedEdge()
{
    return this->weightedEdge;
}
bool Graph::getWeightedNode()
{
    return this->weightedNode;
}
Node *Graph::getFirstNode()
{
    return this->firstNode;
}
Node *Graph::getLastNode()
{
    return this->lastNode;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/

void Graph::fixOrder(){
    this->order = nodeIdCounter;
}

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

void Graph::insertEdge(int sourceLabel, int targetLabel, float weight, Node **sourceNode, Node **targetNode)
{
    if(sourceLabel == targetLabel)
        return;
    
    *sourceNode = getNodeByLabel(sourceLabel);
    if (*sourceNode == nullptr)
        if (nodeIdCounter < order)
            *sourceNode = insertNode(sourceLabel);
        else
            return;

    *targetNode = getNodeByLabel(targetLabel);
    if (*targetNode == nullptr)
        if (nodeIdCounter < order)
            *targetNode = insertNode(targetLabel);
        else
            return;
    int targetNodeId = (*targetNode)->getId();

    Edge *nextEdge = (*sourceNode)->getFirstEdge();
    bool alreadyExists = false;
    while (nextEdge != nullptr)
    {
        if (nextEdge->getTargetId() == targetNodeId)
            alreadyExists = true;
        nextEdge = nextEdge->getNextEdge();
    }
    if (!alreadyExists)
    {
        (*sourceNode)->insertEdge(targetNodeId, targetLabel ,weight);
        if (!directed)
        {
            (*targetNode)->insertEdge((*sourceNode)->getId(), targetLabel , weight);
            (*sourceNode)->incrementInDegree();
            (*targetNode)->incrementOutDegree();
        }
    }

    (*sourceNode)->incrementOutDegree();
    (*targetNode)->incrementInDegree();
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

bool Graph::existEdge(int labe1, int label2){
    Node *firstNode = this->getNodeByLabel(labe1);
    if(firstNode == NULL){
        return false;
    }
    Edge *auxEdge = firstNode->getFirstEdge();
    while(auxEdge != NULL){
        if(auxEdge->getTargetLabel() == label2)
        {
            return true;
        }
        auxEdge = auxEdge->getNextEdge();
    }
    return false;
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
