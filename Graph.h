/**************************************************************************************************
 * Implementation of the TAD Graph
 **************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <iostream>

using namespace std;

class Graph
{
    // Atributos
private:
    int order;
    int numberEdges;
    bool directed;
    bool weightedEdge;
    bool weightedNode;
    Node *firstNode;
    Node *lastNode;
    int nodeIdCounter;

public:
    // Construtor
    Graph(int order, bool directed, bool weightedEdge, bool weightedNode);

    // Destrutor
    ~Graph();

    // Getters
    int getOrder();
    int getNodeIdCounter();
    int getNumberEdges();
    bool getDirected();
    bool getWeightedEdge();
    bool getWeightedNode();
    Node *getFirstNode();
    Node *getLastNode();

    // Métodos de manipulação
    Node *insertNode(int label);
    Node *insertNode(int label, float weight);
    void fixOrder();
    void insertEdge(int sourceLabel, int targetLabel, float weight);
    void insertEdge(int sourceLabel, int targetLabel, float weight, Node **sourceNode, Node **targetNode);
    void insertEdge(Node *sourceNode, Node *targetNode, float weight);
    void removeNode(int id);

    // Métodos auxiliares
    bool searchNode(int id);
    Node *getNodeById(int id);
    Node *getNodeByLabel(int label);
    int getLabelById(int id);
    bool depthFirstSearch(int initialId, int targetId);
    bool isConnected();
    bool thereIsEdgeBetweenLabel(int sourceLabel, int targetLabel);
    float getWeightBetweenNodes(int sourceId, int targetId);

    // Conjunto dominante
    Node **copyNodePointersToArray(int *size, int **degreeList, bool **coveredList);
    void sortNodesByDegree(Node **nodeList, int size, int *degreeList);
    void sortNodesByDegreeAndWeight(Node **nodeList, int size, int *degreeList);
    list<SimpleNode> dominatingSet(float *totalCost);
    list<SimpleNode> dominatingSetWeighted(float *totalCost);

    // Algoritmos predefinidos
    float **floydMarshall();
    float *dijkstra(int startId);
    Graph *kruskal();
    Graph *prim();

private:
    // Métodos auxiliares
    bool depthFirstSearchAux(Node *currentNode, int targetId, bool visitedList[]);
};

#endif // GRAPH_H_INCLUDED
