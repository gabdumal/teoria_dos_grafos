/**************************************************************************************************
 * Implementation of the TAD Node
 **************************************************************************************************/

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "Edge.h" // Include of the Edge class
#include <list>

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
    int getId() const;
    int getLabel();
    int getInDegree();
    int getOutDegree();
    float getWeight();
    Node *getNextNode();

    // Setters
    void setNextNode(Node *node);
    void setWeight(float weight);

    // Other methods
    void incrementOutDegree();
    void decrementOutDegree();
    void incrementInDegree();
    void decrementInDegree();

    // Auxiliar methods
    void insertEdge(int sourceId, int sourceLabel, int targetId, int targetLabel, float weight);
    int removeEdge(int id, bool directed, Node *targetNode);
    void removeAllEdges();
    Edge *getEdgeBetween(int targetId);
    bool hasEdgeBetween(int targetId);
    float distanceToOtherNode(int targetId);
    list<SimpleEdge> distanceToConnectedNodes();
};

#endif // NODE_H_INCLUDED
