#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <math.h>
#include <cstdlib>
#include <algorithm>
#include <climits>
#include <cfloat>
#include <fstream>
#include <list>
using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
 **************************************************************************************************/

// Construtor
Graph::Graph(int order, bool directed, bool weightedEdge, bool weightedNode)
{
    this->order = order;
    this->directed = directed;
    this->weightedEdge = weightedEdge;
    this->weightedNode = weightedNode;
    this->firstNode = this->lastNode = nullptr;
    this->numberEdges = 0;
    this->nodeIdCounter = 0;
}

// Destrutor
Graph::~Graph()
{
    Node *nextNode = this->firstNode;

    while (nextNode != nullptr)
    {
        Node *auxNode = nextNode->getNextNode();
        delete nextNode;
        nextNode = auxNode;
    }

    this->order = 0;
    this->numberEdges = 0;
    this->nodeIdCounter = 0;
    this->firstNode = nullptr;
    this->lastNode = nullptr;
}

// Getters
int Graph::getOrder()
{
    return this->order;
}
int Graph::getNodeIdCounter()
{
    return this->nodeIdCounter;
}
int Graph::getNumberEdges()
{
    return this->numberEdges;
}
bool Graph::getDirected()
{
    return this->directed;
}
bool Graph::getWeightedEdge()
{
    return this->weightedEdge;
}
bool Graph::getWeightedNode()
{
    return this->weightedNode;
}
Node *Graph::getFirstNode()
{
    return this->firstNode;
}
Node *Graph::getLastNode()
{
    return this->lastNode;
}

// Métodos de manipulação
//
void Graph::fixOrder()
{
    this->order = nodeIdCounter;
}

Node *Graph::insertNode(int label)
{
    Node *newNode = new Node(nodeIdCounter++, label);
    if (lastNode == nullptr)
    {
        firstNode = newNode;
        lastNode = newNode;
    }
    else
    {
        lastNode->setNextNode(newNode);
        lastNode = newNode;
    }
    return newNode;
}
Node *Graph::insertNode(int label, float weight)
{
    Node *newNode = this->insertNode(label);
    newNode->setWeight(weight);
    return newNode;
}

void Graph::insertEdge(int sourceLabel, int targetLabel, float weight, Node **sourceNode, Node **targetNode)
{
    if (sourceLabel == targetLabel)
        return;

    *sourceNode = getNodeByLabel(sourceLabel);
    if (*sourceNode == nullptr)
        if (nodeIdCounter < order)
            *sourceNode = insertNode(sourceLabel);
        else
            return;

    *targetNode = getNodeByLabel(targetLabel);
    if (*targetNode == nullptr)
        if (nodeIdCounter < order)
            *targetNode = insertNode(targetLabel);
        else
            return;
    int targetNodeId = (*targetNode)->getId();

    Edge *nextEdge = (*sourceNode)->getFirstEdge();
    bool alreadyExists = false;
    while (nextEdge != nullptr)
    {
        if (nextEdge->getTargetId() == targetNodeId)
            alreadyExists = true;
        nextEdge = nextEdge->getNextEdge();
    }
    if (!alreadyExists)
    {
        (*sourceNode)->insertEdge((*sourceNode)->getId(), sourceLabel, targetNodeId, targetLabel, weight);
        if (!directed)
        {
            (*targetNode)->insertEdge(targetNodeId, targetLabel, (*sourceNode)->getId(), sourceLabel, weight);
            (*sourceNode)->incrementInDegree();
            (*targetNode)->incrementOutDegree();
        }
    }

    (*sourceNode)->incrementOutDegree();
    (*targetNode)->incrementInDegree();
    numberEdges++;
}
void Graph::insertEdge(int sourceLabel, int targetLabel, float weight)
{
    Node *sourceNode = nullptr;
    Node *targetNode = nullptr;
    this->insertEdge(sourceLabel, targetLabel, weight, &sourceNode, &targetNode);
}
void Graph::insertEdge(Node *sourceNode, Node *targetNode, float weight)
{
    if (sourceNode != nullptr && targetNode != nullptr)
    {
        int sourceNodeId = sourceNode->getId();
        int targetNodeId = targetNode->getId();
        int sourceNodeLabel = sourceNode->getLabel();
        int targetNodeLabel = targetNode->getLabel();
        sourceNode->insertEdge(sourceNodeId, sourceNodeLabel, targetNodeId, targetNodeLabel, weight);
        if (!directed)
        {
            targetNode->insertEdge(targetNodeId, targetNodeLabel, sourceNodeId, sourceNodeLabel, weight);
            sourceNode->incrementInDegree();
            targetNode->incrementOutDegree();
        }
    }

    sourceNode->incrementOutDegree();
    targetNode->incrementInDegree();
    numberEdges++;
}

void Graph::removeNode(int id)
{
}

// Métodos auxiliares
//
bool Graph::searchNode(int id)
{
    return this->getNodeById(id) != nullptr;
}

Node *Graph::getNodeById(int id)
{
    Node *nextNode = this->firstNode;
    while (nextNode != nullptr)
    {
        if (nextNode->getId() == id)
            return nextNode;

        nextNode = nextNode->getNextNode();
    }
    return nullptr;
}

Node *Graph::getNodeByLabel(int label)
{
    Node *nextNode = this->firstNode;
    while (nextNode != nullptr)
    {
        if (nextNode->getLabel() == label)
            return nextNode;

        nextNode = nextNode->getNextNode();
    }
    return nullptr;
}

int Graph::getLabelById(int id)
{
    Node *node = this->getNodeById(id);
    if (node != nullptr)
        return node->getLabel();
    else
        return INT_MAX;
}

// Verifica se existe aresta entre dois nós
bool Graph::thereIsEdgeBetweenLabel(int sourceLabel, int targetLabel)
{
    Node *sourceNode = this->getNodeByLabel(sourceLabel);
    return sourceNode->hasEdgeBetweenLabel(targetLabel);
}

// Verifica se há um caminho entre dois nós
bool Graph::depthFirstSearch(int initialId, int targetId)
{
    bool *visitedList = new bool[this->nodeIdCounter];
    for (int i = 0; i < this->nodeIdCounter; i++)
        visitedList[i] = false;
    return depthFirstSearchAux(this->getNodeById(initialId), targetId, visitedList);
}
bool Graph::depthFirstSearchAux(Node *currentNode, int targetId, bool visitedList[])
{
    int currentNodeId = currentNode->getId();
    if (currentNodeId == targetId)
        return true;
    if (visitedList[currentNodeId])
        return false;
    visitedList[currentNodeId] = true;

    for (Edge *e = currentNode->getFirstEdge(); e != nullptr; e = e->getNextEdge())
    {
        Node *nextNode = this->getNodeById(e->getTargetId());
        bool found = this->depthFirstSearchAux(nextNode, targetId, visitedList);
        if (found)
            return true;
    }
    return false;
}

bool Graph::isConnected()
{
    // TO DO
    return true;
}

float Graph::getWeightBetweenNodes(int sourceId, int targetId)
{
    return this->getNodeById(sourceId)->distanceToOtherNode(targetId);
}

// Algoritmos predefinidos
//
float **Graph::floydMarshall()
{
    float **minPathCurrent = new float *[this->order];
    float minPathPrevious[this->order][this->order];

    // Calcula distâncias entre todos os nós sem intermediários
    for (int i = 0; i < this->order; i++)
    {
        for (int j = 0; j < this->order; j++)
        {
            minPathCurrent[i] = new float[this->order];
            minPathPrevious[i][j] = this->getWeightBetweenNodes(i, j);
        }
    }

    for (int k = 0; k < this->order; k++)
    {
        for (int i = 0; i < this->order; i++)
        {
            for (int j = 0; j < this->order; j++)
            {
                // Verifica se é melhor usar o nó K como intermediário
                float previousPath = minPathPrevious[i][j];
                float pathUsingK = minPathPrevious[i][k] + minPathPrevious[k][j];
                minPathCurrent[i][j] = min(previousPath, pathUsingK);
            }
        }

        // Copia a matriz atual para a anterior
        for (int i = 0; i < this->order; i++)
            for (int j = 0; j < this->order; j++)
                minPathPrevious[i][j] = minPathCurrent[i][j];

        // // Impressão de cada iteração
        // for (int i = 0; i < this->getOrder(); i++)
        // {
        //     for (int j = 0; j < this->getOrder(); j++)
        //     {
        //         float path = minPathCurrent[i][j];
        //         string formatedFloat = "";
        //         if (path == FLT_MAX)
        //             formatedFloat += "   &";
        //         else
        //         {
        //             if (path < 10)
        //                 formatedFloat += "0";
        //             std::stringstream stream;
        //             stream << std::fixed << std::setprecision(1) << path;
        //             formatedFloat += stream.str();
        //         }
        //         cout << formatedFloat << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }

    return minPathCurrent;
}

float *Graph::dijkstra(int startId)
{
    bool *solution = new bool[this->order];
    int solutionQuantity = 1;
    float *minPath = new float[this->order];
    list<Node *> nodeList;
    list<SimpleEdge> incidentEdges = this->firstNode->distanceToConnectedNodes();

    for (Node *n = this->firstNode; n != nullptr; n = n->getNextNode())
        nodeList.emplace_back(n);
    nodeList.sort([](Node *const &node1, Node *const &node2)
                  { return node1->getId() < node2->getId(); });

    solution[0] = true;
    minPath[0] = 0;
    for (int auxNodeId = 1; auxNodeId < this->order; auxNodeId++)
    {
        solution[auxNodeId] = false;
        minPath[auxNodeId] = FLT_MAX;
        for (auto &&e : incidentEdges)
        {
            if (e.targetNodeId == auxNodeId)
                minPath[auxNodeId] = e.weight;
        }
    }

    // string printPartialResult = "[";
    // for (int i = 0; i < this->getOrder(); i++)
    // {
    //     int label = this->getNodeById(i)->getLabel();
    //     printPartialResult += "    " + to_string(label) + ", ";
    // }
    // printPartialResult.pop_back();
    // printPartialResult.pop_back();
    // printPartialResult += "]\n";
    // cout << printPartialResult;

    // printPartialResult = "[";
    // for (int i = 0; i < this->getOrder(); i++)
    // {
    //     float path = minPath[i];
    //     string formatedFloat = "";
    //     if (path == FLT_MAX)
    //         formatedFloat += "    &";
    //     else
    //     {
    //         if (path < 10)
    //             formatedFloat += "0";
    //         std::stringstream stream;
    //         stream << std::fixed << std::setprecision(2) << path;
    //         formatedFloat += stream.str();
    //     }
    //     printPartialResult += formatedFloat + ", ";
    // }
    // printPartialResult.pop_back();
    // printPartialResult.pop_back();
    // printPartialResult += "]\n";
    // cout << printPartialResult;

    while (solutionQuantity < this->order)
    {
        // Seleciona o nó com menor caminho
        int minPathNodeId;
        int m;
        for (m = 1; m < this->order; m++)
        {
            if (!solution[m])
            {
                minPathNodeId = m;
                break;
            }
        }
        float pathValue = 0;
        for (int n = m + 1; n < this->order; n++)
        {
            pathValue = minPath[n];
            if (!solution[n] && pathValue < minPath[minPathNodeId])
                minPathNodeId = n;
        }

        // Adiciona o nó com menor caminho à solução
        solution[minPathNodeId] = true;
        solutionQuantity++;
        Node *minPathNode = this->getNodeById(minPathNodeId);
        incidentEdges = minPathNode->distanceToConnectedNodes();

        // Recalcula caminho para nós adjacentes
        for (auto &&e : incidentEdges)
        {
            int targetNodeId = e.targetNodeId;
            float newPath = minPath[minPathNodeId] + e.weight;
            if (newPath < minPath[targetNodeId])
            {
                solution[targetNodeId] = false;
                solutionQuantity--;
                minPath[targetNodeId] = newPath;
            }
        }

        // printPartialResult = "[";
        // for (int i = 0; i < this->getOrder(); i++)
        // {
        //     float path = minPath[i];
        //     string formatedFloat = "";
        //     if (path == FLT_MAX)
        //         formatedFloat += "    &";
        //     else
        //     {
        //         if (path < 10)
        //             formatedFloat += "0";
        //         std::stringstream stream;
        //         stream << std::fixed << std::setprecision(2) << path;
        //         formatedFloat += stream.str();
        //     }
        //     printPartialResult += formatedFloat + ", ";
        // }
        // printPartialResult.pop_back();
        // printPartialResult.pop_back();
        // printPartialResult += "]\n";
        // cout << printPartialResult;
    }

    delete solution;
    return minPath;
}

Graph *Graph::kruskal()
{
    if (this->directed)
    {
        cout << "ERRO: Algoritmo de Kruskal nao funciona para grafos direcionados!";
        return nullptr;
    }
    if (!this->isConnected())
    {
        cout << "ERRO: Algoritmo de Kruskal nao funciona para grafos nao conexos!";
        return nullptr;
    }

    // Copia nós do grafo
    Graph *solutionGraph = new Graph(INT_MAX, directed, weightedEdge, weightedNode);
    for (Node *n = firstNode; n != nullptr; n = n->getNextNode())
        solutionGraph->insertNode(n->getLabel(), n->getWeight());
    solutionGraph->fixOrder();
    int *components = new int[this->order];
    for (int i = 0; i < this->order; i++)
        components[i] = i;

    // Cria lista de arestas
    list<SimpleEdge> allEdges;
    for (Node *n = this->firstNode; n != nullptr; n = n->getNextNode())
        for (Edge *e = n->getFirstEdge(); e != nullptr; e = e->getNextEdge())
        {
            SimpleEdge simpleEdge;
            simpleEdge.sourceNodeId = e->getSourceId();
            simpleEdge.targetNodeId = e->getTargetId();
            simpleEdge.sourceNodeLabel = e->getSourceLabel();
            simpleEdge.targetNodeLabel = e->getTargetLabel();
            simpleEdge.weight = e->getWeight();
            allEdges.emplace_back(simpleEdge);
        }
    allEdges.sort([](SimpleEdge const &edge1, SimpleEdge const &edge2)
                  { return edge1.weight < edge2.weight; });

    // Constrói árvore geradora mínima
    int i = 0;
    while (i < order - 1 && !allEdges.empty())
    {
        SimpleEdge currentEdge = allEdges.front();
        allEdges.pop_front();

        if (components[currentEdge.sourceNodeId] != components[currentEdge.targetNodeId])
        {
            solutionGraph->insertEdge(currentEdge.sourceNodeLabel, currentEdge.targetNodeLabel, currentEdge.weight);
            if (components[currentEdge.sourceNodeId] > components[currentEdge.targetNodeId])
            {
                int oldComponent = components[currentEdge.sourceNodeId];
                for (int j = 0; j < this->order; j++)
                    if (components[j] == oldComponent)
                        components[j] = components[currentEdge.targetNodeId];
            }
            else
            {
                int oldComponent = components[currentEdge.targetNodeId];
                for (int j = 0; j < this->order; j++)
                    if (components[j] == oldComponent)
                        components[j] = components[currentEdge.sourceNodeId];
            }
            i++;
        }

        for (int j = 0; j < this->order; j++)
            cout << components[j] << " ";
        cout << endl;
    }

    delete components;
    return solutionGraph;
}

Graph *Graph::prim()
{
    if (this->directed)
    {
        cout << "ERRO: Algoritmo de Prim nao funciona para grafos direcionados!";
        return nullptr;
    }
    if (!this->isConnected())
    {
        cout << "ERRO: Algoritmo de Prim nao funciona para grafos nao conexos!";
        return nullptr;
    }

    // Cria lista de arestas
    list<SimpleEdge> allEdges;
    list<SimpleEdge> solutionEdges;
    for (Node *n = this->firstNode; n != nullptr; n = n->getNextNode())
        for (Edge *e = n->getFirstEdge(); e != nullptr; e = e->getNextEdge())
        {
            SimpleEdge simpleEdge;
            simpleEdge.sourceNodeId = e->getSourceId();
            simpleEdge.targetNodeId = e->getTargetId();
            simpleEdge.weight = e->getWeight();
            allEdges.emplace_back(simpleEdge);
        }
    SimpleEdge shortestEdge = allEdges.front();
    for (auto &&e : allEdges)
    {
        if (e.weight < shortestEdge.weight)
            shortestEdge = e;
    }

    // Cria listas auxiliares de distância
    int *nearestNodeList = new int[this->order];
    float *auxNodeList = new float[this->order];

    // Adiciona primeira aresta
    solutionEdges.emplace_back(shortestEdge);
    int sourceNodeId = shortestEdge.sourceNodeId;
    int targetNodeId = shortestEdge.targetNodeId;
    int k = 0;
    // Preenche distâncias para nós conectados aos presentes na menor aresta
    for (Node *n = this->firstNode; n != nullptr && k < this->order; n = n->getNextNode())
    {
        float distanceCurrentToSource = n->distanceToOtherNode(sourceNodeId);
        float distanceCurrentToTarget = n->distanceToOtherNode(targetNodeId);
        if (distanceCurrentToSource < distanceCurrentToTarget)
        {
            nearestNodeList[k] = sourceNodeId;
            auxNodeList[k] = distanceCurrentToSource;
        }
        else
        {
            nearestNodeList[k] = targetNodeId;
            auxNodeList[k] = distanceCurrentToTarget;
        }
        k++;
    }
    int static alreadyInSolution = -1;
    nearestNodeList[sourceNodeId] = alreadyInSolution;
    nearestNodeList[targetNodeId] = alreadyInSolution;

    // Seleção das arestas
    for (int i = 0; i < this->order - 2; i++)
    {
        // Seleciona id do nó de menor distância
        int minDistanceSourceId;
        int m;
        for (m = 0; m < this->order; m++)
        {
            if (nearestNodeList[m] > alreadyInSolution)
            {
                minDistanceSourceId = m;
                break;
            }
        }
        float distanceNodes = 0;
        for (int n = m + 1; n < this->order; n++)
        {
            distanceNodes = auxNodeList[n];
            if (nearestNodeList[n] > alreadyInSolution && distanceNodes < auxNodeList[minDistanceSourceId])
                minDistanceSourceId = n;
        }

        // Adiciona aresta de menor custo à solução
        SimpleEdge shortestAvailableEdge;
        shortestAvailableEdge.sourceNodeId = minDistanceSourceId;
        shortestAvailableEdge.targetNodeId = nearestNodeList[minDistanceSourceId];
        shortestAvailableEdge.weight = auxNodeList[minDistanceSourceId];
        solutionEdges.emplace_back(shortestAvailableEdge);

        // Atualiza listas de próximos nós e distâncias
        nearestNodeList[minDistanceSourceId] = alreadyInSolution;
        auxNodeList[minDistanceSourceId] = 0;
        Node *currentNode = this->getNodeById(minDistanceSourceId);
        for (int m = 0; m < this->order; m++)
        {
            if (nearestNodeList[m] > alreadyInSolution)
            {
                float distanceCurrentToM = currentNode->distanceToOtherNode(m);
                if (auxNodeList[m] > distanceCurrentToM)
                {
                    nearestNodeList[m] = minDistanceSourceId;
                    auxNodeList[m] = distanceCurrentToM;
                }
            }
        }

        // Impressão passo-a-passo
        //     cout << "J = " << currentNode->getLabel() << endl;
        //     for (int i = 0; i < this->order; i++)
        //         cout << "| " << this->getNodeById(i)->getLabel() << " ";
        //     cout << endl;
        //     for (int i = 0; i < this->order; i++)
        //         if (nearestNodeList[i] == -1)
        //             cout << "| A ";
        //         else
        //             cout << "| " << this->getNodeById(nearestNodeList[i])->getLabel() << " ";
        //     cout << endl;
        //     for (int i = 0; i < this->order; i++)
        //     {
        //         float distance = auxNodeList[i];
        //         if (distance == FLT_MAX)
        //             cout << "| $ ";
        //         else
        //             cout << "| " << distance << " ";
        //     }
        //     cout << endl
        //          << endl;
    }

    // Constrói grafo resultado
    Graph *solutionGraph = new Graph(order, directed, weightedEdge, weightedNode);
    for (auto &&e : solutionEdges)
    {
        Node *sourceNode = this->getNodeById(e.sourceNodeId);
        Node *targetNode = this->getNodeById(e.targetNodeId);
        solutionGraph->insertEdge(sourceNode->getLabel(), targetNode->getLabel(), e.weight);
    }
    solutionGraph->fixOrder();

    delete nearestNodeList;
    delete auxNodeList;
    return solutionGraph;
}
