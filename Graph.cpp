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
#include <cfloat>
#include <iomanip>
#include <algorithm>
#include <climits>

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
            (*sourceNode)->incrementInDegree();
            (*targetNode)->incrementOutDegree();
        }
    }

    (*sourceNode)->incrementOutDegree();
    (*targetNode)->incrementInDegree();
    numberEdges++;
}

void Graph::insertEdge(int sourceLabel, int targetLabel, float weight)
{
    Node *sourceNode = nullptr;
    Node *targetNode = nullptr;
    this->insertEdge(sourceLabel, targetLabel, weight, &sourceNode, &targetNode);
}

void Graph::insertEdge(Node *sourceNode, Node *targetNode, float weight)
{
    if (sourceNode != nullptr && targetNode != nullptr)
    {
        int sourceNodeId = sourceNode->getId();
        int targetNodeId = targetNode->getId();
        int sourceNodeLabel = sourceNode->getLabel();
        int targetNodeLabel = targetNode->getLabel();
        sourceNode->insertEdge(sourceNodeId, sourceNodeLabel, targetNodeId, targetNodeLabel, weight);
        if (!directed)
        {
            targetNode->insertEdge(targetNodeId, targetNodeLabel, sourceNodeId, sourceNodeLabel, weight);
            sourceNode->incrementInDegree();
            targetNode->incrementOutDegree();
        }
    }

    sourceNode->incrementOutDegree();
    targetNode->incrementInDegree();
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

// Verifica se existe aresta entre dois nós
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

bool Graph::isConnected()
{
    // TO DO
    return true;
}

Graph *Graph::kruskal()
{
    if (this->directed)
    {
        cout << "ERRO: Algoritmo de Kruskal nao funciona para grafos direcionados!";
        return nullptr;
    }
    if (!this->isConnected())
    {
        cout << "ERRO: Algoritmo de Kruskal nao funciona para grafos nao conexos!";
        return nullptr;
    }

    // Copia nós do grafo
    Graph *solutionGraph = new Graph(INT_MAX, directed, weightedEdge, weightedNode);
    for (Node *n = firstNode; n != nullptr; n = n->getNextNode())
        solutionGraph->insertNode(n->getLabel(), n->getWeight());
    solutionGraph->fixOrder();

    // Cria lista de arestas
    list<PointerEdge> allEdges;
    for (Node *n = firstNode; n != nullptr; n = n->getNextNode())
        for (Edge *e = n->getFirstEdge(); e != nullptr; e = e->getNextEdge())
            allEdges.emplace_back(solutionGraph->getNodeById(n->getId()),
                                  solutionGraph->getNodeById(e->getTargetId()), e->getWeight());
    allEdges.sort([](PointerEdge const &edge1, PointerEdge const &edge2)
                  { return edge1.getWeight() < edge2.getWeight(); });

    // Constrói árvore geradora mínima
    int i = 0;
    while (i < order - 1 && !allEdges.empty())
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

Graph *Graph::prim()
{
    if (this->directed)
    {
        cout << "ERRO: Algoritmo de Prim nao funciona para grafos direcionados!";
        return nullptr;
    }
    if (!this->isConnected())
    {
        cout << "ERRO: Algoritmo de Prim nao funciona para grafos nao conexos!";
        return nullptr;
    }

    // Cria lista de arestas
    list<SimpleEdge> allEdges;
    list<SimpleEdge> solutionEdges;
    for (Node *n = this->firstNode; n != nullptr; n = n->getNextNode())
        for (Edge *e = n->getFirstEdge(); e != nullptr; e = e->getNextEdge())
        {
            SimpleEdge simpleEdge;
            simpleEdge.sourceNodeId = e->getSourceId();
            simpleEdge.targetNodeId = e->getTargetId();
            simpleEdge.weight = e->getWeight();
            allEdges.emplace_back(simpleEdge);
        }
    SimpleEdge shortestEdge = allEdges.front();
    for (auto &&e : allEdges)
    {
        if (e.weight < shortestEdge.weight)
            shortestEdge = e;
    }

    // Cria listas auxiliares de distância
    int *nearestNodeList = new int[this->order];
    float *auxNodeList = new float[this->order];

    // Adiciona primeira aresta
    solutionEdges.emplace_back(shortestEdge);
    int sourceNodeId = shortestEdge.sourceNodeId;
    int targetNodeId = shortestEdge.targetNodeId;
    int k = 0;
    for (Node *n = this->firstNode; n != nullptr && k < this->order; n = n->getNextNode())
    {
        float distanceCurrentToSource = n->distanceToOtherNode(sourceNodeId);
        float distanceCurrentToTarget = n->distanceToOtherNode(targetNodeId);
        if (distanceCurrentToSource < distanceCurrentToTarget)
        {
            nearestNodeList[k] = sourceNodeId;
            auxNodeList[k] = distanceCurrentToSource;
        }
        else
        {
            nearestNodeList[k] = targetNodeId;
            auxNodeList[k] = distanceCurrentToTarget;
        }
        k++;
    }
    int static alreadyInSolution = -1;
    nearestNodeList[sourceNodeId] = alreadyInSolution;
    nearestNodeList[targetNodeId] = alreadyInSolution;

    // Seleção das arestas
    for (int i = 0; i < this->order - 2; i++)
    {
        int minDistanceSourceId;
        int m;
        for (m = 0; m < this->order; m++)
        {
            if (nearestNodeList[m] > alreadyInSolution)
            {
                minDistanceSourceId = m;
                break;
            }
        }
        float distanceNodes = 0;
        for (int n = m + 1; n < this->order; n++)
        {
            distanceNodes = auxNodeList[n];
            if (nearestNodeList[n] > alreadyInSolution && distanceNodes < auxNodeList[minDistanceSourceId])
                minDistanceSourceId = n;
        }

        SimpleEdge shortestAvailableEdge;
        shortestAvailableEdge.sourceNodeId = minDistanceSourceId;
        shortestAvailableEdge.targetNodeId = nearestNodeList[minDistanceSourceId];
        shortestAvailableEdge.weight = auxNodeList[minDistanceSourceId];
        solutionEdges.emplace_back(shortestAvailableEdge);

        nearestNodeList[minDistanceSourceId] = alreadyInSolution;
        auxNodeList[minDistanceSourceId] = 0;
        Node *currentNode = this->getNodeById(minDistanceSourceId);

        for (int m = 0; m < this->order; m++)
        {
            if (nearestNodeList[m] > alreadyInSolution)
            {
                float distanceCurrentToM = currentNode->distanceToOtherNode(m);
                if (auxNodeList[m] > distanceCurrentToM)
                {
                    nearestNodeList[m] = minDistanceSourceId;
                    auxNodeList[m] = distanceCurrentToM;
                }
            }
        }

        //     cout << "J = " << currentNode->getLabel() << endl;
        //     for (int i = 0; i < this->order; i++)
        //         cout << "| " << this->getNodeById(i)->getLabel() << " ";
        //     cout << endl;
        //     for (int i = 0; i < this->order; i++)
        //         if (nearestNodeList[i] == -1)
        //             cout << "| A ";
        //         else
        //             cout << "| " << this->getNodeById(nearestNodeList[i])->getLabel() << " ";
        //     cout << endl;
        //     for (int i = 0; i < this->order; i++)
        //     {
        //         float distance = auxNodeList[i];
        //         if (distance == FLT_MAX)
        //             cout << "| $ ";
        //         else
        //             cout << "| " << distance << " ";
        //     }
        //     cout << endl
        //          << endl;
    }

    // Constrói grafo resultado
    Graph *solutionGraph = new Graph(order, directed, weightedEdge, weightedNode);
    for (auto &&e : solutionEdges)
    {
        Node *sourceNode = this->getNodeById(e.sourceNodeId);
        Node *targetNode = this->getNodeById(e.targetNodeId);
        solutionGraph->insertEdge(sourceNode->getLabel(), targetNode->getLabel(), e.weight);
    }
    solutionGraph->fixOrder();

    return solutionGraph;
}
