/**************************************************************************************************
 * Implementation of the TAD Graph
 **************************************************************************************************/

#ifndef GRAPHHINCLUDED
#define GRAPHHINCLUDED
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

public:
    // Constructor
    Graph(int order, bool directed, bool weightedEdge, bool weightedNode);
    // Destructor
    ~Graph();
    // Getters
    int getOrder();
    int getNumberEdges();
    bool getDirected();
    bool getWeightedEdge();
    bool getWeightedNode();
    Node *getFirstNode();
    Node *getLastNode();
    // Other methods
    void insertNode(int id);
    void insertEdge(int id, int targetId, float weight);
    void removeNode(int id);
    bool searchNode(int id);
    Node *getNode(int id);
    bool depthFirstSearch(int initialId, int targetId);
    void breadthFirstSearch(ofstream &output_file);
    Graph *getComplement();
    Graph *getSubjacent();
    bool hasCircuit();
    bool connectedGraph();
    float **floydMarshall();
    float *dijkstra(int id);

private:
    // Auxiliar methods
};

#endif // GRAPHHINCLUDED
