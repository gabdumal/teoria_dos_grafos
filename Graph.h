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
    void printList(Node **nodeList, int size);
    bool isSolved(Node **nodeList, bool *nodeCovered, int size);
    Node **copyNodePointersToArray(int *size, bool **coveredList);
    void sortNodesByDegreeAndWeight(Node **nodeList, int size);
    list<SimpleNode> dominatingSetWeighted(float *totalCost);
    list<SimpleNode> dominatingSetWeightedRandomized(float *totalCost, int numIterations, float alfa);
    list<SimpleNode> dominatingSetWeightedRandomizedReactive(float *totalCost, int numIterations, float *alfa, int m, int block);

    void initializeProbabilities(float probabilities[], float averages[], int m);
    void updateProbabilities(float probabilities[], float averages[], int bestCost, int m);
    void updateAverages(float vetAlfas[], float averages[], int m, int cost, float alfa);
    void sortArrays(float vetAlfas[], float probabilities[], float averages[], int m);

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
