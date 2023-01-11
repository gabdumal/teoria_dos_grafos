#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <cfloat>
#include <climits>
using namespace std;

/**************************************************************************************************
 * Defining the Node's methods
 **************************************************************************************************/

// Construtor
Node::Node(int id, int label)
{
    this->id = id;
    this->label = label;
    this->inDegree = 0;
    this->outDegree = 0;
    this->weight = 0;
    this->firstEdge = nullptr;
    this->lastEdge = nullptr;
    this->nextNode = nullptr;
};

// Destrutor
Node::~Node()
{
    Edge *nextEdge = this->firstEdge;

    while (nextEdge != nullptr)
    {
        Edge *auxEdge = nextEdge->getNextEdge();
        delete nextEdge;
        nextEdge = auxEdge;
    }

    this->id = -1;
    this->label = INT_MIN;
    this->inDegree = 0;
    this->outDegree = 0;
    this->weight = 0;
    this->firstEdge = nullptr;
    this->lastEdge = nullptr;
    this->nextNode = nullptr;
};

// Getters
Edge *Node::getFirstEdge()
{
    return this->firstEdge;
}
Edge *Node::getLastEdge()
{
    return this->lastEdge;
}
int Node::getId() const
{
    return this->id;
}
int Node::getLabel()
{
    return this->label;
}
int Node::getInDegree()
{
    return this->inDegree;
}
int Node::getOutDegree()
{
    return this->outDegree;
}
float Node::getWeight()
{
    return this->weight;
}
Node *Node::getNextNode()
{
    return this->nextNode;
}
// SimpleNode Node::getSimpleNode(){
//     SimpleNode s;
//     s.id = this->id;
//     s.label = this->label;
//     s.degree = this->getInDegree();
//     s.weight = this->weight;
// }
// Setters
void Node::setNextNode(Node *nextNode)
{
    this->nextNode = nextNode;
}
void Node::setWeight(float weight)
{
    this->weight = weight;
}

// Métodos de manipulação
//

/****************
* Funcao    : void insertEdge(int sourceId, int sourceLabel, int targetId, int targetLabel, float weight)       *
* Descricao : Inserir uma nova aresta entre dois vértices.                                                           *
* Parametros: sourceId - id do vértice de que está chamando a função                                            *
               sourceLabel - label do vértice que está chamando a função                                        *
               targetId - id do vértice alvo                                                                    *
               targetLabel - label do vértice alvo                                                              *
               weight - peso da aresta                                                                          *   
* Retorno   : Sem retorno.                                                                                      *
 ***************/
void Node::insertEdge(int sourceId, int sourceLabel, int targetId, int targetLabel, float weight)
{
    // Verifies whether there are at least one edge in the node
    if (this->firstEdge != nullptr)
    {
        // Allocating the new edge and keeping the integrity of the edge list
        Edge *edge = new Edge(sourceId, sourceLabel, targetId, targetLabel);
        edge->setWeight(weight);
        this->lastEdge->setNextEdge(edge);
        this->lastEdge = edge;
    }
    else
    {
        // Allocating the new edge and keeping the integrity of the edge list
        this->firstEdge = new Edge(sourceId, sourceLabel, targetId, targetLabel);
        this->firstEdge->setWeight(weight);
        this->lastEdge = this->firstEdge;
    }
}

/****************
 * Funcao    : void removeAllEdges()                                        *
 * Descricao : Remover todas as arestas referentes a um vertice.            *
 * Parametros: Sem parâmetros.                                              *
 * Retorno   : Sem retorno.                                                 *
 ***************/
void Node::removeAllEdges()
{
    // Verifies whether there are at least one edge in the node
    if (this->firstEdge != nullptr)
    {
        Edge *next = nullptr;
        Edge *aux = this->firstEdge;
        // Removing all edges of the node
        while (aux != nullptr)
        {
            next = aux->getNextEdge();
            delete aux;
        }
    }
    this->firstEdge = this->lastEdge = nullptr;
}

/****************
 * Funcao    : int removeEdge(int id, bool directed, Node *targetNode)                              *
 * Descricao : A partir de um vertice, tenta remover a aresta dele com um vertice alvo              *
 * Parametros: id - id do vértice alvo que a aresta deve ser removida                                    *
               directed - booleano que informa se a aresta em questão é direcionada ou não          * 
               targetNode - ponteiro para o vértice alvo                                                 *
 * Retorno   : Retorna 1 se a aresta existe e foi removida, e 0 se ela não existir.                 *
 ***************/
int Node::removeEdge(int id, bool directed, Node *targetNode)
{
    // Verifies whether the edge to remove is in the node
    if (this->hasEdgeBetween(id))
    {
        Edge *aux = this->firstEdge;
        Edge *previous = nullptr;

        // Searching for the edge to be removed
        while (aux->getTargetId() != id)
        {
            previous = aux;
            aux = aux->getNextEdge();
        }

        // Keeping the integrity of the edge list
        if (previous != nullptr)
            previous->setNextEdge(aux->getNextEdge());
        else
            this->firstEdge = aux->getNextEdge();

        if (aux == this->lastEdge)
            this->lastEdge = previous;

        if (aux->getNextEdge() == this->lastEdge)
            this->lastEdge = aux->getNextEdge();

        delete aux;

        // Verifies whether the graph is directed
        if (directed)
            this->decrementOutDegree();
        else
        {
            this->decrementInDegree();
            targetNode->decrementInDegree();
        }

        return 1;
    }
    return 0;
}

// Outros métodos
//

/****************
 * Funcao    : void incrementInDegree()                     *
 * Descricao : Incrementar o grau de entrada do vértice.    *
 * Parametros: Sem parâmetros.                              *
 * Retorno   : Sem retorno.                                 *
 ***************/
void Node::incrementInDegree()
{
    this->inDegree++;
}

/****************
 * Funcao    : void incrementInDegree()                     *
 * Descricao : Incrementar o grau de saida do vértice.      *
 * Parametros: Sem parâmetros.                              *
 * Retorno   : Sem retorno.                                 *
 ***************/
void Node::incrementOutDegree()
{
    this->outDegree++;
}

/****************
 * Funcao    : void incrementInDegree()                     *
 * Descricao : Decrementar o grau de entrada do vértice.    *
 * Parametros: Sem parâmetros.                              *
 * Retorno   : Sem retorno.                                 *
 ***************/
void Node::decrementInDegree()
{
    this->inDegree--;
}

/****************
 * Funcao    : void incrementInDegree()                     *
 * Descricao : Decrementar o grau de saida do vértice.      *
 * Parametros: Sem parâmetros.                              *
 * Retorno   : Sem retorno.                                 *
 ***************/
void Node::decrementOutDegree()
{
    this->outDegree--;
}

// Métodos auxiliares
//

/****************
 * Funcao    : Edge getEdgeBetween(int targetId)                                                             *
 * Descricao : A partir de um vértice, avalia se existe aresta ligando a outro vértice alvo por meio do id   *
 * Parametros: targeId - id do vértice alvo.                                                                 *
 * Retorno   : Retorna a aresta existente entre os vértices, caso exista                                     *
 ***************/
Edge *Node::getEdgeBetween(int targetId)
{
    if (this == nullptr)
        return nullptr;
    else
        for (Edge *auxEdge = this->firstEdge; auxEdge != nullptr; auxEdge = auxEdge->getNextEdge())
        {
            if (auxEdge->getTargetId() == targetId)
                return auxEdge;
        }
    return nullptr;
}

/****************
 * Funcao    : Edge getEdgeBetween(int targetLabel)                                                              *
 * Descricao : A partir de um vértice, avalia se existe aresta ligando a outro vértice alvo por meio do label    *
 * Parametros: targeLabel - label do vértice alvo.                                                               *
 * Retorno   : Retorna a aresta existente entre os vértices, caso exista                                         *
 ***************/
Edge *Node::getEdgeBetweenLabel(int targetLabel)
{
    if (this == nullptr)
        return nullptr;
    else
        for (Edge *auxEdge = this->firstEdge; auxEdge != nullptr; auxEdge = auxEdge->getNextEdge())
        {
            if (auxEdge->getTargetLabel() == targetLabel)
                return auxEdge;
        }
    return nullptr;
}

/****************
 * Funcao    : bool hasEdgeBetween(int targetId)                                                               *
 * Descricao : A partir de um vértice, avalia se existe aresta ligando a outro vértice alvo por meio do id     *
 * Parametros: targeId - id do vértice alvo.                                                                   *
 * Retorno   : Retorna true caso a aresta exista                                                               *
 ***************/
bool Node::hasEdgeBetween(int targetId)
{
    if (this == nullptr)
        return false;
    else
        return this->getEdgeBetween(targetId) != nullptr;
}

/****************
 * Funcao    : bool hasEdgeBetween(int targetLabel)                                                              *
 * Descricao : A partir de um vértice, avalia se existe aresta ligando a outro vértice alvo por meio do label    *
 * Parametros: targetLabel - label do vértice alvo.                                                              *
 * Retorno   : Retorna true caso a aresta exista                                                                 *
 ***************/
bool Node::hasEdgeBetweenLabel(int targetLabel)
{
    if (this == nullptr)
        return false;
    else
        return this->getEdgeBetweenLabel(targetLabel) != nullptr;
}

/****************
 * Funcao    : float distanceToOtherNode(int targetId)                                                *
 * Descricao : A partir de um vértice, captura o valor da distancia(aresta) até um vértice alvo       *
 * Parametros: targeId - id do vértice alvo.                                                          *
 * Retorno   : Retorna um float da distância (aresta) entre os dois vértic                            *
 ***************/
float Node::distanceToOtherNode(int targetId)
{
    if (this->id == targetId)
        return 0;
    Edge *edgeBetween = this->getEdgeBetween(targetId);
    if (edgeBetween != nullptr)
        return edgeBetween->getWeight();
    else
        return FLT_MAX;
}

/****************
 * Funcao    : list<SimpleEdge> distanceToConnectedNodes()                                                  *
 * Descricao : A partir de um vértice, captura todas as informações das arestas conectadas a esse vértice   *
 * Parametros: Sem parâmetros.                                                                              *
 * Retorno   : Retorna uma lista de SimpleEdge                                                              *
 ***************/
list<SimpleEdge> Node::distanceToConnectedNodes()
{
    list<SimpleEdge> connectedEdges;
    for (Edge *auxEdge = this->firstEdge; auxEdge != nullptr; auxEdge = auxEdge->getNextEdge())
    {
        SimpleEdge simpleEdge;
        simpleEdge.sourceNodeId = this->id;
        simpleEdge.targetNodeId = auxEdge->getTargetId();
        simpleEdge.weight = auxEdge->getWeight();
        connectedEdges.emplace_back(simpleEdge);
    }
    return connectedEdges;
}