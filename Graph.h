/**************************************************************************************************
 * Implementation of the TAD Graph
 **************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include "random/random.h"
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
    void insertEdge(int sourceLabel, int targetLabel, float weight, Node **sourceNode, Node **targetNode, bool isPERT);
    void insertEdge(Node *sourceNode, Node *targetNode, float weight);
    void removeNode(int id);

    // Métodos auxiliares
    bool searchNode(int id);
    Node *getNodeById(int id);
    Node *getNodeByLabel(int label);
    int getLabelById(int id);
    bool depthFirstSearch(int initialId, int targetId);
    bool thereIsEdgeBetweenLabel(int sourceLabel, int targetLabel);
    float getWeightBetweenNodes(int sourceId, int targetId);
    bool isConnected();
    void marksNodeComponent(int idNode, int component, int **NodeComponentList);
    void createAuxNodeComponentArray(int *size, int **componentList);

    // Conjunto dominante
    void printList(Node **nodeList, int size);
    bool isSolved(Node **nodeList, bool *nodeCovered, int size);
    Node **copyNodePointersToArray(int *size, bool **coveredList);

    void sortNodesByDegreeAndWeight(Node **nodeList, int size);
    list<SimpleNode> dominatingSetWeighted(float *totalCost);
    list<SimpleNode> dominatingSetWeightedRandomized(float *totalCost, CARDINAL seed, int numIterations, float alfa);
    list<SimpleNode> dominatingSetWeightedRandomizedReactive(float *totalCost, CARDINAL seed, int numIterations, float *vetAlfas, int tam, int block, float *bestAlfa);

    void initializeProbabilities(int **iterEachAlfa, float **probabilities, int **numIterPerAlfa, float **averages, int tam);
    void updateProbabilities(float probabilities[], float averages[], float bestCost, int tam);
    void updateAverages(float vetAlfas[], float averages[], int iterEachAlfa[], int tam, float cost, int auxChooseAlfa);

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
