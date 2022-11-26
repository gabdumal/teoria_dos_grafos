/**************************************************************************************************
 * Implementation of the TAD Edge
 **************************************************************************************************/

#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

using namespace std;

// Definition of the Edge class
class Edge
{

    // Attributes
private:
    int targetId;
    int targetLabel;
    Edge *nextEdge;
    float weight;

public:
    // Constructor
    Edge(int targetId, int targetLabel);
    // Destructor
    ~Edge();
    // Getters
    int getTargetId();
    int getTargetLabel();
    Edge *getNextEdge();
    float getWeight();
    // Setters
    void setNextEdge(Edge *edge);
    void setWeight(float weight);
};

#endif // EDGE_H_INCLUDED