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
    int sourceId;
    int sourceLabel;
    int targetId;
    int targetLabel;
    Edge *nextEdge;
    float weight;

public:
    // Constructor
    Edge(int sourceId, int sourceLabel, int targetId, int targetLabel);
    // Destructor
    ~Edge();
    // Getters
    int getSourceId();
    int getTargetId();
    int getTargetLabel();
    Edge *getNextEdge();
    float getWeight() const;
    // Setters
    void setNextEdge(Edge *edge);
    void setWeight(float weight);
};

typedef struct
{
    int sourceNodeId;
    int targetNodeId;
    float weight;
} SimpleEdge;

#endif // EDGE_H_INCLUDED