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
    void fixOrder();
    Node *insertNode(int id);
    void insertEdge(int sourceLabel, int targetLabel, float weight, Node **sourceNode, Node **targetNode);
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
    bool existEdge(int label1, int labe2);
    float **floydMarshall();
    float *dijkstra(int id);

private:
    // Auxiliar methods
};

#endif // GRAPH_H_INCLUDED
