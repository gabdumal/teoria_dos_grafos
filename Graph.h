/**************************************************************************************************
 * Implementation of the TAD Graph
 **************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <fstream>
#include <stack>
#include <list>

using namespace std;

class Graph
{

    // Atributes
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
    // Constructor
    Graph(int order, bool directed, bool weightedEdge, bool weightedNode);

    // Destructor
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

    // Other methods
    Node *insertNode(int label);
    Node *insertNode(int label, float weight);
    void insertEdge(int sourceLabel, int targetLabel, float weight, Node **sourceNode, Node **targetNode);
    void insertEdge(Node *sourceNode, Node *targetNode, float weight);
    void removeNode(int id);
    bool searchNode(int id);
    Node *getNodeById(int id);
    Node *getNodeByLabel(int label);
    bool depthFirstSearch(int initialId, int targetId);
    void breadthFirstSearch(ofstream &output_file);
    Graph *getComplement();
    Graph *getSubjacent();
    bool hasCircuit();
    bool connectedGraph();

    // Algoritmos predefinidos
    float **floydMarshall();
    float *dijkstra(int id);
    Graph *kruskal();

private:
    // Métodos auxiliares
    bool depthFirstSearchAux(Node *currentNode, int targetId, bool visitedList[]);
};

#endif // GRAPH_H_INCLUDED
