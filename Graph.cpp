#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "PointerEdge.h"
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
#include <algorithm>

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

void Graph::fixOrder()
{
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
Node *Graph::insertNode(int label, float weight)
{
    Node *newNode = this->insertNode(label);
    newNode->setWeight(weight);
    return newNode;
}

void Graph::insertEdge(int sourceLabel, int targetLabel, float weight, Node **sourceNode, Node **targetNode)
{
    if (sourceLabel == targetLabel)
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
        (*sourceNode)->insertEdge((*sourceNode)->getId(), sourceLabel, targetNodeId, targetLabel, weight);
        if (!directed)
        {
            (*targetNode)->insertEdge(targetNodeId, targetLabel, (*sourceNode)->getId(), sourceLabel, weight);
            // (*sourceNode)->incrementInDegree();
            // (*targetNode)->incrementOutDegree();
        }
    }

    (*sourceNode)->incrementOutDegree();
    (*targetNode)->incrementInDegree();
    numberEdges++;
}

void Graph::insertEdge(Node *sourceNode, Node *targetNode, float weight)
{
    if (sourceNode != nullptr && targetNode != nullptr)
    {
        int sourceNodeId = sourceNode->getId();
        int targetNodeId = targetNode->getId();
        int sourceNodeLabel = sourceNode->getLabel();
        int targetNodelabel = targetNode->getLabel();
        sourceNode->insertEdge(sourceNodeId, sourceNodeLabel, targetNodeId, targetNodelabel, weight);
        if (!directed)
        {
            targetNode->insertEdge(sourceNodeId, sourceNodeLabel, targetNodeId, targetNodelabel, weight);
            // sourceNode->incrementInDegree();
            // targetNode->incrementOutDegree();
        }
    }

    sourceNode->incrementInDegree();
    targetNode->incrementOutDegree();
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

bool Graph::existEdge(int firstNodeLabel, int secondNodeLabel)
{
    Node *firstNode = this->getNodeByLabel(firstNodeLabel);
    if (firstNode == nullptr)
    {
        return false;
    }
    Edge *auxEdge = firstNode->getFirstEdge();
    while (auxEdge != nullptr)
    {
        if (auxEdge->getTargetLabel() == secondNodeLabel)
        {
            return true;
        }
        auxEdge = auxEdge->getNextEdge();
    }
    return false;
}

// Verifica se há um caminho entre dois nós
bool Graph::depthFirstSearch(int initialId, int targetId)
{
    bool *visitedList = new bool[this->nodeIdCounter];
    for (int i = 0; i < this->nodeIdCounter; i++)
        visitedList[i] = false;
    return depthFirstSearchAux(this->getNodeById(initialId), targetId, visitedList);
}
bool Graph::depthFirstSearchAux(Node *currentNode, int targetId, bool visitedList[])
{
    int currentNodeId = currentNode->getId();
    if (currentNodeId == targetId)
        return true;
    if (visitedList[currentNodeId])
        return false;
    visitedList[currentNodeId] = true;

    for (Edge *e = currentNode->getFirstEdge(); e != nullptr; e = e->getNextEdge())
    {
        Node *nextNode = this->getNodeById(e->getTargetId());
        bool found = this->depthFirstSearchAux(nextNode, targetId, visitedList);
        if (found)
            return true;
    }
    return false;
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

Graph *Graph::kruskal()
{
    Graph *solutionGraph = new Graph(order, directed, weightedEdge, weightedNode);

    if (this->directed)
    {
        cout << "ERRO: Algoritmo de Kruskal não funciona para grafos direcionados!";
        return solutionGraph;
    }

    list<PointerEdge> allEdges;

    for (Node *n = firstNode; n != nullptr && n->getLabel() > 0; n = n->getNextNode())
        solutionGraph->insertNode(n->getLabel(), n->getWeight());

    // Cria lista de arestas
    for (Node *n = firstNode; n != nullptr && n->getLabel() > 0; n = n->getNextNode())
        for (Edge *e = n->getFirstEdge(); e != nullptr; e = e->getNextEdge())
            allEdges.emplace_back(solutionGraph->getNodeById(n->getId()),
                                  solutionGraph->getNodeById(e->getTargetId()), e->getWeight());

    allEdges.sort([](PointerEdge const &edge1, PointerEdge const &edge2)
                  { return edge1.getWeight() < edge2.getWeight(); });

    // Constrói árvore geradora mínima
    int i = 0;
    while (i < nodeIdCounter - 1 && !allEdges.empty())
    {
        PointerEdge currentEdge = allEdges.front();
        allEdges.pop_front();

        if (!solutionGraph->depthFirstSearch(currentEdge.getSourceNode()->getId(), currentEdge.getTargetNode()->getId()))
        {
            solutionGraph->insertEdge(currentEdge.getSourceNode(), currentEdge.getTargetNode(), currentEdge.getWeight());
            i++;
        }
    }

    return solutionGraph;
}
