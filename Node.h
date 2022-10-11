/**************************************************************************************************
 * Implementation of the TAD Node
 **************************************************************************************************/

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "Edge.h" // Include of the Edge class

using namespace std;

// Definition of the Node class
class Node
{

    // Attributes
private:
    Edge *firstEdge;
    Edge *lastEdge;
    int id;
    int label;
    unsigned int inDegree;
    unsigned int outDegree;
    float weight;
    Node *nextNode;

public:
    // Constructor
    Node(int id, int label);
    // Destructor
    ~Node();
    // Getters
    Edge *getFirstEdge();
    Edge *getLastEdge();
    int getId();
    int getLabel();
    int getInDegree();
    int getOutDegree();
    float getWeight();
    Node *getNextNode();
    // Setters
    void setNextNode(Node *node);
    void setWeight(float weight);
    // Other methods
    bool searchEdge(int targetId);
    void insertEdge(int targetLabel, float weight);
    void removeAllEdges();
    int removeEdge(int id, bool directed, Node *targetNode);
    void incrementOutDegree();
    void decrementOutDegree();
    void incrementInDegree();
    void decrementInDegree();
    Edge *hasEdgeBetween(int targetId);
    // Auxiliar methods
};

#endif // NODE_H_INCLUDED
