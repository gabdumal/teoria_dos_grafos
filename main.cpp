#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Graph.h"
#include "Node.h"

using namespace std;

string exportGraphToDotFormat(Graph *graph)
{
    // Em grafos não-direcionados, uma aresta só pode ser impressa uma vez

    Node *nextNode = graph->getFirstNode();
    string dot = "", connector;
    bool weightedEdge = graph->getWeightedEdge();

    if (graph->getDirected())
    {
        connector = " -> ";
        dot += "di";
    }
    else
        connector = " -- ";

    dot += "graph grafo {\n";
    while (nextNode != nullptr)
    {
        dot += "  " + to_string(nextNode->getLabel()) +
               " [weight = " + to_string(nextNode->getWeight()) + "];\n";
        nextNode = nextNode->getNextNode();
    }
    nextNode = graph->getFirstNode();
    while (nextNode != nullptr)
    {
        Edge *nextEdge = nextNode->getFirstEdge();
        while (nextEdge != nullptr)
        {
            dot += "\n  " + to_string(nextNode->getLabel()) + connector +
                   to_string(graph->getNodeById(nextEdge->getTargetId())->getLabel());
            if (weightedEdge)
                dot += " [weight = " + to_string(nextEdge->getWeight()) + "];";
            nextEdge = nextEdge->getNextEdge();
        }
        nextNode = nextNode->getNextNode();
    }
    dot += "\n}\n";

    return dot;
}

Graph *leitura(ifstream &input_file, int directed, int weightedEdge, int weightedNode)
{
    // Variáveis para auxiliar na criação dos nós no Grafo
    int labelNodeSource;
    int labelNodeTarget;
    int order;

    // Pegando a ordem do grafo
    input_file >> order;

    // Criando objeto grafo
    Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);

    // Leitura de arquivo

    // Grafo SEM peso nos nós, e SEM peso nas arestas
    if (!graph->getWeightedEdge() && !graph->getWeightedNode())
    {
        while (input_file >> labelNodeSource >> labelNodeTarget)
        {
            graph->insertEdge(labelNodeSource, labelNodeTarget, 0);
        }
    }
    // Grafo SEM peso nos nós, mas COM peso nas arestas
    else if (graph->getWeightedEdge() && !graph->getWeightedNode())
    {
        float edgeWeight;

        while (input_file >> labelNodeSource >> labelNodeTarget >> edgeWeight)
        {
            graph->insertEdge(labelNodeSource, labelNodeTarget, edgeWeight);
        }
    }
    // Grafo COM peso nos nós, mas SEM peso nas arestas
    else if (graph->getWeightedNode() && !graph->getWeightedEdge())
    {
        float nodeSourceWeight, nodeTargetWeight;

        while (input_file >> labelNodeSource >> nodeSourceWeight >> labelNodeTarget >> nodeTargetWeight)
        {
            graph->insertEdge(labelNodeSource, labelNodeTarget, 0);
            graph->getNodeByLabel(labelNodeSource)->setWeight(nodeSourceWeight);
            graph->getNodeByLabel(labelNodeTarget)->setWeight(nodeTargetWeight);
        }
    }
    // Grafo COM peso nos nós, e COM peso nas arestas
    else if (graph->getWeightedNode() && graph->getWeightedEdge())
    {
        float nodeSourceWeight, nodeTargetWeight, edgeWeight;

        while (input_file >> labelNodeSource >> nodeSourceWeight >> labelNodeTarget >> nodeTargetWeight >> edgeWeight)
        {
            graph->insertEdge(labelNodeSource, labelNodeTarget, edgeWeight);
            graph->getNodeByLabel(labelNodeSource)->setWeight(nodeSourceWeight);
            graph->getNodeByLabel(labelNodeTarget)->setWeight(nodeTargetWeight);
        }
    }

    return graph;
}

bool showGraph(string dot)
{
    string response = "";

    cout << "GRAFO" << endl
         << "-----" << endl
         << dot << endl;
    while (response != "S" && response != "s" && response != "N" && response != "n")
    {
        cout << "Deseja exportar este grafo? Isso vai apagar o conteúdo atual do arquivo [S/n] ";
        cin >> response;
    }
    cout << endl
         << endl;
    return (response == "S" || response == "s");
}

int menu(string *errors)
{
    string selectedOption;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Complementar do grafo" << endl;
    cout << "[2] Imprimir caminhamento em largura" << endl;
    cout << "[3] Busca em profundidade" << endl;
    cout << "[4] Imprimir componentes conexas" << endl;
    cout << "[5] Imprimir componentes fortemente conexas" << endl;
    cout << "[6] Imprimir ordenacao topológica" << endl;
    cout << "[7] Árvore Geradora Mínima de Prim" << endl;
    cout << "[8] Caminho Mínimo Dijkstra" << endl;
    cout << "[9] Caminho Mínimo Floyd" << endl;
    cout << "[10] Algoritmos Gulosos (Abre um submenu)" << endl;
    cout << "[0] Sair" << endl;

    cin >> selectedOption;

    try
    {
        return stoi(selectedOption);
    }
    catch (const std::invalid_argument &)
    {
        *errors = "ERRO: Letras são inválidas. Digite um número inteiro entre 0 e 10!\n\n";
        return -1;
    }
    catch (const std::out_of_range &)
    {
        *errors == "ERRO: Fora dos limites. Digite um número inteiro entre 0 e 10!\n\n";
        return -1;
    }
}

string selectOption(int *selectedOption, Graph *graph, ofstream &output_file)
{
    string dot = "";
    int option = *selectedOption;
    switch (option)
    {
    case 0:
    {
        *selectedOption = 0;
    }
    // Complementar
    case 1:
    {
        dot = exportGraphToDotFormat(graph);
        break;
    }
    // BFS
    case 2:
    {

        break;
    }
    // DFS
    case 3:
    {

        break;
    }
    // Componentes Conexas
    case 4:
    {

        break;
    }
    // Componentes Fortementes Conexas
    case 5:
    {

        break;
    }
    // Ordenação Topológica
    case 6:
    {

        break;
    }
    case 7:
    {

        break;
    }
    // Algoritmo de Prim
    case 8:
    {

        break;
    }
    // Algoritmo de Dijkstra
    case 9:
    {

        break;
    }
    // Algoritmo de Floyd
    case 10:
    {

        break;
    }
    default:
    {
        *selectedOption = -1;
    }
    }
    return dot;
}

int mainMenu(ofstream &output_file, string outputFileName, Graph *graph)
{
    string dot = "", errors = "";
    int selectedOption = -1;
    bool shouldExport = false;

    while (selectedOption != 0)
    {
        system("clear");

        if (output_file.is_open())
        {
            if (selectedOption != -1)
            {
                shouldExport = showGraph(dot);
                if (shouldExport)
                {
                    output_file.close();
                    output_file.open(outputFileName, ios::out | ios::trunc);
                    output_file << dot;
                    shouldExport = false;
                }
            }
            cout << errors;
            errors = "";
            selectedOption = menu(&errors);
            dot = selectOption(&selectedOption, graph, output_file);
        }
        else
            cout << "Unable to open the output_file" << endl;
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    // Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6)
    {
        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
        return 1;
    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;

    // Abrindo arquivo de entrada
    ifstream input_file;
    ofstream output_file;
    input_file.open(argv[1], ios::in);
    output_file.open(argv[2], ios::out | ios::trunc);

    Graph *graph;

    if (input_file.is_open())
    {
        graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    }
    else
        cout << "Unable to open " << argv[1];

    mainMenu(output_file, argv[2], graph);

    // Fechando arquivo de entrada
    input_file.close();

    // Fechando arquivo de saída
    output_file.close();

    return 0;
}
