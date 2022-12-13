/**************************************************************************************************
 * Implementation of the TAD Edge
 **************************************************************************************************/

#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

using namespace std;

// Definição da classe Edge (Aresta)
class Edge
{
    // Atributos
private:
    int sourceId;
    int sourceLabel;
    int targetId;
    int targetLabel;
    Edge *nextEdge;
    float weight;

public:
    // Construtor
    Edge(int sourceId, int sourceLabel, int targetId, int targetLabel);

    // Destrutor
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

// Structs para representação simplificada
typedef struct
{
    int sourceNodeId;
    int targetNodeId;
    float weight;
} SimpleEdge;

#endif // EDGE_H_INCLUDED