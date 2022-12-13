/**************************************************************************************************
 * Implementation of the TAD Node
 **************************************************************************************************/

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "Edge.h"
#include <list>

using namespace std;

// Definição da classe Node (Nó)
class Node
{
    // Atributos
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
    // Construtor
    Node(int id, int label);

    // Destrutor
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

    // Outros métodos
    void incrementOutDegree();
    void decrementOutDegree();
    void incrementInDegree();
    void decrementInDegree();

    // Métodos de manipulação
    void insertEdge(int sourceId, int sourceLabel, int targetId, int targetLabel, float weight);
    int removeEdge(int id, bool directed, Node *targetNode);
    void removeAllEdges();

    // Métodos auxiliares
    Edge *getEdgeBetween(int targetId);
    Edge *getEdgeBetweenLabel(int targetLabel);
    bool hasEdgeBetween(int targetId);
    bool hasEdgeBetweenLabel(int targetLabel);
    float distanceToOtherNode(int targetId);
    list<SimpleEdge> distanceToConnectedNodes();
};

#endif // NODE_H_INCLUDED
