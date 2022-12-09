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
    int targetId;
    Edge *nextEdge;
    float weight;

public:
    // Constructor
    Edge(int sourceId, int targetId);
    // Destructor
    ~Edge();
    // Getters
    int getSourceId();
    int getTargetId();
    Edge *getNextEdge();
    float getWeight() const;
    // Setters
    void setNextEdge(Edge *edge);
    void setWeight(float weight);
};

#endif // EDGE_H_INCLUDED