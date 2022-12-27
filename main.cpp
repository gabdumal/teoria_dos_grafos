#include "Graph.h"
#include "Node.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <sstream>
#include <climits>
#include <cfloat>

using namespace std;

// Constantes
static const int OPTION_INVALID = -1;
static const int OPTION_EXIT = 0;
static const int OPTION_EXPORT = 1;

// Variáveis globais
bool directed = false, weightedEdge = false, weightedNode = false;

string formatFloat(float value, int precision, int totalLength)
{
    string returnString = "";
    if (value == FLT_MAX)
        returnString = "&";
    else
    {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(precision) << value;
        returnString = stream.str();
    }
    int missingSpaces = totalLength - returnString.length();
    if (missingSpaces > 0)
        returnString.insert(0, missingSpaces, ' ');
    return returnString;
}

string formatInt(int value, int totalLength)
{
    string returnString = "";
    if (value == INT_MAX)
        returnString = "&";
    else
        returnString = to_string(value);
    int missingSpaces = totalLength - returnString.length();
    if (missingSpaces > 0)
        returnString.insert(0, missingSpaces, ' ');
    return returnString;
}

/*  Names a graph according it's kind, either directed or not
 *   writes .dot file after the .txt input
 */
string exportGraphToDotFormat(Graph *graph)
{ // dot -Tpng output.dot -o graph1.png
    if (graph == nullptr)
        return "";

    Node *nextNode = graph->getFirstNode();
    string dot = "", connector;
    bool weightedNode = graph->getWeightedNode();
    bool weightedEdge = graph->getWeightedEdge();

    dot += "strict ";
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
               " [weight = " + formatFloat(nextNode->getWeight(), 2, 5) + "]";
        // if (weightedNode)
        //     dot += " [xlabel = " + formatFloat(nextNode->getWeight(), 0, 5) + "]";
        dot += ";\n";
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
            {
                dot += " [weight = " + formatFloat(nextEdge->getWeight(), 2, 5) +
                       "] [label = " + formatFloat(nextEdge->getWeight(), 2, 5) + "];";
            }
            nextEdge = nextEdge->getNextEdge();
        }
        nextNode = nextNode->getNextNode();
    }
    dot += "\n}\n";

    return dot;
}

Graph *readFileSecondPart(ifstream &input_file)
{
    // Preenchimento das variáveis globais
    ::directed = false;
    ::weightedEdge = false;
    ::weightedNode = true;

    // Variáveis para auxiliar na criação dos nós no Grafo
    int labelNodeSource;
    int labelNodeTarget;
    int order;
    float weight;
    int existEdge;

    // Obtém a ordem do grafo
    string line;
    input_file >> line;
    input_file >> order;

    // Cria objeto grafo
    Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);

    // Leitura de arquivo
    if (!graph->getWeightedEdge() && !graph->getWeightedNode())
    {
        while (input_file >> labelNodeSource >> labelNodeTarget)
        {
            Node *sourceNode = nullptr;
            Node *targetNode = nullptr;
            graph->insertEdge(abs(labelNodeSource), abs(labelNodeTarget), 1, &sourceNode, &targetNode);
        }
    }
    // Posições
    for (int i = 0; i < order + 3; i++)
        getline(input_file, line);
    // Pesos dos nós
    for (int i = 0; i < order; i++)
    {
        input_file >> weight;
        graph->insertNode(i + 1, weight);
    }
    input_file >> line;
    // Arestas
    for (int i = 0; i < order - 1; i++)
    {
        for (int j = 0; j < order; j++)
        {
            input_file >> existEdge;
            if (j > i && existEdge == 1)
                graph->insertEdge(i + 1, j + 1, 1);
        }
    }

    return graph;
}

/*  Reads from .txt file
    it also evaluetas three possible natures of the graph, if it is: directed, weighted on edges, weighted on nodes
*/
Graph *readFileFirstPart(ifstream &input_file, int directed, int weightedEdge, int weightedNode)
{
    // Preenchimento das variáveis globais
    ::directed = directed;
    ::weightedEdge = weightedEdge;
    ::weightedNode = weightedNode;

    // Variáveis para auxiliar na criação dos nós no Grafo
    int labelNodeSource;
    int labelNodeTarget;
    int order;

    // Obtém a ordem do grafo
    input_file >> order;

    // Cria objeto grafo
    Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);

    // Leitura de arquivo
    //
    // Grafo SEM peso nos nós, e SEM peso nas arestas
    if (!graph->getWeightedEdge() && !graph->getWeightedNode())
    {
        while (input_file >> labelNodeSource >> labelNodeTarget)
        {
            Node *sourceNode = nullptr;
            Node *targetNode = nullptr;
            graph->insertEdge(abs(labelNodeSource), abs(labelNodeTarget), 1, &sourceNode, &targetNode);
        }
    }
    // Grafo SEM peso nos nós, mas COM peso nas arestas
    else if (graph->getWeightedEdge() && !graph->getWeightedNode())
    {
        float edgeWeight;

        while (input_file >> labelNodeSource >> labelNodeTarget >> edgeWeight)
        {
            Node *sourceNode = nullptr;
            Node *targetNode = nullptr;
            graph->insertEdge(abs(labelNodeSource), abs(labelNodeTarget), edgeWeight, &sourceNode, &targetNode);
        }
    }
    // Grafo COM peso nos nós, mas SEM peso nas arestas
    else if (graph->getWeightedNode() && !graph->getWeightedEdge())
    {
        float nodeSourceWeight, nodeTargetWeight;

        while (input_file >> labelNodeSource >> nodeSourceWeight >> labelNodeTarget >> nodeTargetWeight)
        {
            Node *sourceNode = nullptr;
            Node *targetNode = nullptr;
            graph->insertEdge(abs(labelNodeSource), abs(labelNodeTarget), 1, &sourceNode, &targetNode);
            if (sourceNode != nullptr)
                sourceNode->setWeight(nodeSourceWeight);
            if (targetNode != nullptr)
                targetNode->setWeight(nodeTargetWeight);
        }
    }
    // Grafo COM peso nos nós, e COM peso nas arestas
    else if (graph->getWeightedNode() && graph->getWeightedEdge())
    {
        float nodeSourceWeight, nodeTargetWeight, edgeWeight;

        while (input_file >> labelNodeSource >> nodeSourceWeight >> labelNodeTarget >> nodeTargetWeight >> edgeWeight)
        {
            Node *sourceNode = nullptr;
            Node *targetNode = nullptr;
            graph->insertEdge(abs(labelNodeSource), abs(labelNodeTarget), edgeWeight, &sourceNode, &targetNode);
            if (sourceNode != nullptr)
                sourceNode->setWeight(nodeSourceWeight);
            if (targetNode != nullptr)
                targetNode->setWeight(nodeTargetWeight);
        }
    }

    int i = -1;
    while (order > graph->getNodeIdCounter())
    {
        graph->insertNode(i);
        i--;
    }

    return graph;
}

Graph *createAuxiliaryGraphFromFile(ifstream &input_file, string input_file_name, int *selectedOption, string *errors)
{
    if (input_file.is_open())
        return readFileFirstPart(input_file, ::directed, ::weightedEdge, ::weightedNode);
    else
    {
        *errors += "ERRO: Não foi possível abrir o arquivo de entrada " + input_file_name + "!\n";
        *selectedOption = OPTION_INVALID;
        return nullptr;
    }
}

Graph *readAuxiliaryGraph(int *selectedOption, string *errors)
{
    cout << "Digite o caminho do arquivo de entrada do grafo auxiliar:" << endl;
    string auxiliary_input_file_name;
    cin >> auxiliary_input_file_name;

    ifstream auxiliary_input_file;
    auxiliary_input_file.open(auxiliary_input_file_name, ios::in);

    Graph *auxiliaryGraph = createAuxiliaryGraphFromFile(auxiliary_input_file, auxiliary_input_file_name, selectedOption, errors);

    auxiliary_input_file.close();
    return auxiliaryGraph;
}

Graph *createUnionGraph(Graph *firstGraph, Graph *secondGraph)
{
    Graph *thirdGraph;
    string dot = "";
    // COPIA GRAFO1 PARA GRAFO 3
    thirdGraph = new Graph(INT_MAX, firstGraph->getDirected(), false, false);

    // aux
    Node *finalNode = firstGraph->getFirstNode();
    Edge *nextEdge;

    while (finalNode != nullptr)
    {
        nextEdge = finalNode->getFirstEdge();

        while (nextEdge != nullptr)
        {
            Node *sourceNode = nullptr;
            Node *targetNode = nullptr;
            thirdGraph->insertEdge(finalNode->getLabel(), nextEdge->getTargetLabel(), 0, &sourceNode, &targetNode);
            nextEdge = nextEdge->getNextEdge();
        }
        finalNode = finalNode->getNextNode();
    }

    // VERIFICA QUAIS RELAÇÕES ESTÃO NO SEGUNDO GRAFO E NAO ESTÃO NO TERCEIRO

    finalNode = secondGraph->getFirstNode();
    while (finalNode != nullptr)
    {
        nextEdge = finalNode->getFirstEdge();
        while (nextEdge != nullptr)
        {
            if (!thirdGraph->thereIsEdgeBetweenLabel(finalNode->getLabel(), nextEdge->getTargetLabel()))
            {
                Node *sourceNode = nullptr;
                Node *targetNode = nullptr;
                thirdGraph->insertEdge(finalNode->getLabel(), nextEdge->getTargetLabel(), 0, &sourceNode, &targetNode);
            }
            nextEdge = nextEdge->getNextEdge();
        }
        finalNode = finalNode->getNextNode();
    }

    // CORRIGE ORDEM DO GRAFO
    thirdGraph->fixOrder();
    return thirdGraph;
}

Graph *graphDifference(Graph *originalGraph, Graph *toSubtractGraph)
{
    // Instancia grafo resultado com características do grafo original
    Graph *resultedGraph;
    resultedGraph = new Graph(INT_MAX, originalGraph->getDirected(), false, false);

    // Variáveis auxiliares
    Node *auxNodeOriginalGraph = originalGraph->getFirstNode();     // Nó auxiliar recebe o primeiro nó do grafo original
    Node *auxNodeToSubtractGraph = toSubtractGraph->getFirstNode(); // Nó auxiliar recebe o primeiro nó do grafo a subtrair
    Edge *auxEdgeOriginalGraph;
    Edge *auxEdgeToSubtractGraph;
    int sourceLabel;
    int targetLabel;

    while (auxNodeOriginalGraph != nullptr)
    {
        auxEdgeOriginalGraph = auxNodeOriginalGraph->getFirstEdge(); // Aresta auxiliar recebe primeira aresta do primeiro nó do grafo original
        auxEdgeToSubtractGraph = auxNodeToSubtractGraph->getFirstEdge();
        // Enquanto há arestas em um nó...
        while (auxEdgeOriginalGraph != nullptr)
        {
            sourceLabel = auxNodeOriginalGraph->getLabel();
            targetLabel = auxEdgeOriginalGraph->getTargetLabel();
            // Se há aresta no grafo original, e não há no secundário, adiciona ao resultado
            if (!toSubtractGraph->thereIsEdgeBetweenLabel(sourceLabel, targetLabel))
                resultedGraph->insertEdge(sourceLabel, targetLabel, 0);
            auxEdgeOriginalGraph = auxEdgeOriginalGraph->getNextEdge();
        }
        // Avança para o próximo nó
        auxNodeOriginalGraph = auxNodeOriginalGraph->getNextNode();
    }
    resultedGraph->fixOrder();
    return resultedGraph;
}

/*  Prints the graph on terminal window
 *   at the end returns a boolean which is used either to export the graph or not
 */
bool showResponse(string dot, bool isResultSet)
{
    string response = "";

    if (isResultSet)
        cout << "CONJUNTO";
    else
        cout << "GRAFO";
    cout << endl
         << "-----" << endl
         << dot << endl;
    while (response != "S" && response != "s" && response != "N" && response != "n")
    {
        cout << "Deseja exportar este ";
        if (isResultSet)
            cout << "conjunto";
        else
            cout << "grafo";
        cout << "? Isso vai apagar o conteúdo atual do arquivo[S / n] ";
        cin >>
            response;
    }
    cout << endl
         << endl;
    return (response == "S" || response == "s");
}

/*  Shows a menu on terminal windows with 10 options
 *   only two of them works: number one wich prints the graph -on terminal- and number zero wich ends the program
 *   note that the other ones are not suitable for this project
 *   it also shows an error message in case of an incorrect input such letters or numbers others than 0-10
 */
int menu(string *errors, bool isSecondPart)
{
    string selectedOption;

    cout << "MENU" << endl;
    cout << "----" << endl;
    if (isSecondPart)
    {
        cout << "Selecione o algoritmo de processamento" << endl;
        cout << "[1] Guloso" << endl;
        cout << "[2] Guloso randomizado" << endl;
        cout << "[3] Guloso randomizado reativo" << endl;
        cout << "[9] Imprimir grafo" << endl;
    }
    else
    {
        cout << "[1] Imprimir Grafo de Entrada" << endl;
        cout << "[2] Gerar Grafo Interseção" << endl;
        cout << "[3] Gerar Grafo União" << endl;
        cout << "[4] Gerar Grafo Diferença" << endl;
        cout << "[5] Gerar Rede PERT" << endl;
        cout << "[9] Imprimir Grafo Qualquer" << endl;
    }
    cout << "[0] Sair" << endl;

    cin >> selectedOption;

    try
    {
        return stoi(selectedOption);
    }
    catch (const std::invalid_argument &)
    {
        *errors = "ERRO: Letras são inválidas. Digite um número inteiro entre 0 e 10!\n\n";
        return OPTION_INVALID;
    }
    catch (const std::out_of_range &)
    {
        *errors == "ERRO: Fora dos limites. Digite um número inteiro entre 0 e 10!\n\n";
        return OPTION_INVALID;
    }
}

/*  Calls a function according with the entrance option given by user
 *   like the menu, only one and zero matters
 */
string selectOptionFirstPart(int *selectedOption, string *errors, Graph *firstGraph)
{
    string dot = "";
    int option = *selectedOption;
    switch (option)
    {
    case 0:
    {
        *selectedOption = OPTION_EXIT;
        break;
    }
    // Imprimir grafo de entrada
    case 1:
    {
        dot = exportGraphToDotFormat(firstGraph);
        break;
    }
    // Grafo interseção
    case 2:
    {
        break;
    }
    // Grafo união
    case 3:
    {
        Graph *secondGraph = readAuxiliaryGraph(selectedOption, errors);
        Graph *thirdGraph = createUnionGraph(firstGraph, secondGraph);

        dot = exportGraphToDotFormat(thirdGraph);
        delete secondGraph;
        secondGraph = nullptr;
        delete thirdGraph;
        thirdGraph = nullptr;
        break;
    }
    // Grafo diferença
    case 4:
    {
        Graph *secondGraph = readAuxiliaryGraph(selectedOption, errors);
        Graph *thirdGraph = graphDifference(firstGraph, secondGraph);

        dot = exportGraphToDotFormat(thirdGraph);
        delete secondGraph;
        secondGraph = nullptr;
        delete thirdGraph;
        thirdGraph = nullptr;
        break;
    }
    // Rede Pert
    case 5:
    {

        break;
    }
    // Teste
    case 6:
    {
        Graph *secondGraph = firstGraph->kruskal();
        dot = exportGraphToDotFormat(secondGraph);
        delete secondGraph;
        secondGraph = nullptr;
        break;
    }
    // Impressão qualquer
    case 9:
    {
        Graph *secondGraph = readAuxiliaryGraph(selectedOption, errors);
        dot = exportGraphToDotFormat(secondGraph);
        delete secondGraph;
        secondGraph = nullptr;
        break;
    }
    default:
    {
        *selectedOption = OPTION_INVALID;
    }
    }
    return dot;
}
string selectOptionSecondPart(int *selectedOption, string *errors, Graph *graph)
{
    string returnText = "";
    int option = *selectedOption;
    switch (option)
    {
    case 0:
    {
        *selectedOption = OPTION_EXIT;
        break;
    }
    // Guloso
    case 1:
    {
        float totalCost = 0;
        list<SimpleNode> resultSet = graph->dominatingSetWeighted(&totalCost);
        returnText += "Custo: " + formatFloat(totalCost, 4, 7) + "\n";
        for (auto &&node : resultSet)
            returnText += "(" + formatInt(node.label, 4) + ") " + formatInt(node.degree, 4) + "\n";
        break;
    }
    // Guloso randomizado
    case 2:
    {
        break;
    }
    // Guloso randomizado reativo
    case 3:
    {
        break;
    }
    // Impressão
    case 9:
    {
        returnText = exportGraphToDotFormat(graph);
        break;
    }
    default:
    {
        *selectedOption = OPTION_INVALID;
    }
    }
    return returnText;
}

/*  cleans terminal windows
 *   evaluates if the graph will be exported or not based on value of "shouldExport"
 *   also prints on terminal an error message in case of failure opening output file
 */
int mainMenu(string outputFileName, Graph *graph, bool isSecondPart)
{
    string dot = "", errors = "";
    int selectedOption = OPTION_INVALID;

    // Loop de interface
    while (selectedOption != OPTION_EXIT)
    {
        // Impressão do grafo resultante, caso opção não seja inválida
        if (selectedOption != OPTION_INVALID)
        {
            bool shouldExport = showResponse(dot, isSecondPart && selectedOption != 9);
            if (shouldExport)
            {
                ofstream output_file;
                output_file.open(outputFileName, ios::out | ios::trunc);
                output_file << dot;
                output_file.close();
            }
        }

        system("clear");

        // Imprime erros
        cout << errors;
        errors = "";

        // Imprime menu de opções
        selectedOption = menu(&errors, isSecondPart);
        cout << endl;
        if (isSecondPart)
            dot = selectOptionSecondPart(&selectedOption, &errors, graph);
        else
            dot = selectOptionFirstPart(&selectedOption, &errors, graph);
    }
    return 0;
}

/*  Verifies each parameter of the command line,
 *   if it is set properly calls menu function
 *   else it shows the expected model just beforing ending the program
 */
int main(int argc, char const *argv[])
{
    // Verifica se todos os argumentos foram fornecidos
    if (argc == 3 || argc == 6)
    {
        int endingCode = 0;

        // Captura argumentos
        string program_name(argv[0]);
        string input_file_name(argv[1]);
        string output_file_name(argv[2]);

        // Abre arquivos de entrada e saída
        ifstream input_file;
        ofstream output_file;
        input_file.open(input_file_name, ios::in);

        Graph *graph;

        if (input_file.is_open())
        {
            // Executa versão adequada do programa
            if (argc == 6)
            {
                graph = readFileFirstPart(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
                endingCode = mainMenu(output_file_name, graph, false);
            }
            else
            {
                graph = readFileSecondPart(input_file);
                endingCode = mainMenu(output_file_name, graph, true);
            }
        }
        else
        {
            cout << "ERRO: Não foi possível abrir o arquivo de entrada " << input_file_name << "!" << endl;
            return 1;
        }

        // Fecha arquivo de entrada
        input_file.close();
        // Fecha arquivo de saída
        output_file.close();

        return endingCode;
    }
    else
    {
        cout << "ERRO: Espera-se: ./<program_name> <input_file> [<output_file> <directed> <weighted_edge> <weighted_node>]" << endl;
        return 1;
    }
}