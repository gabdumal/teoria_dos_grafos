Este repositório destina-se à implementação do trabalho da disciplina **DCC059 - Teoria dos Grafos** desenvolvido pelo grupo de nº 11 no período letivo 2022-3, em mérito da avaliação do Professor Stênio Sã Rosário Furtado Soares, Universidade Federal de Juiz de fora.<br/>
O grupo é integrado por:
* CAIO HENRIQUE VIEIRA COSTA, 
* CELSO GABRIEL DUTRA ALMEIDA MALOSTO,
* LUCAS DUARTE CHAVES,
* LUCAS PAIVA DOS SANTOS,
* RODRIGO SOARES DE ASSIS.

#### Instruções e informações para compilação e execução

##### Compilação
Para compilar o projeto, entre no diretório `dcc059`, em que estão os arquivos deste repositório, e utilize o seguinte comando: <br/>
`g++ -fdiagnostics-color=always -g ./*.cpp ./random/*.cpp ./time/*.cpp -o ./execGrupo11` <br/>
Perceba que `-g` é dispensável para criação e execução do projeto, porém, é necessário para depuraração do código

##### Execução
Para executar o projeto rapidamente, utilize alguma das seguintes instruções:
###### Parte 1
`./execGrupo11 [input_file] [output_file] [directed] [weighted_edge] [weighted_node]`
###### Parte 2 - Interface com o usuário
`./execGrupo11 [input_file] [output_file]`
###### Parte 2 - Guloso
`./execGrupo11 [input_file] [output_file] 1`
###### Parte 2 - Guloso Randomizado
`./execGrupo11 [input_file] [output_file] 2 [iterations] [alpha]`
###### Parte 2 - Guloso Randomizado Reativo
`./execGrupo11 [input_file] [output_file] 3 [iterations] [block] [number_alphas] [...alphas]`

#### Estrutura de arquivos e pastas
* `.vscode/` - Arquivos auxiliares para compilação e execução pela IDE
* `random/` - Módulo auxiliar para geração de números aleatórios
* `results/` - Resultados da experimentação realizada sobre o programa
* `scripts/` - Scripts de Bash para auxiliar na experimentação
* `src/` - Instâncias originais de descrição dos grafos utilizados para a **parte 2** do trabalho
* `time/` - Módulo auxiliar para contagem de tempo de execução
* `.gitignore` - Arquivo auxiliar do Git
* `Edge.cpp` - Arquivo de implementação das funções referentes às arestas
* `Edge.h` - Arquivo de declaração das funções referentes às arestas
* `execGrupo11` - Arquivo executável do programa desenvolvido
* `Graph.cpp` - Arquivo de implementação das funções referentes aos grafos
* `Graph.h` - Arquivo de declaração das funções referentes aos grafos
* `main.cpp` - Arquivo principal do programa
* `Node.cpp` - Arquivo de implementação das funções referentes aos vértices
* `Node.h` - Arquivo de declaração das funções referentes aos vértices
* `README.md` - Arquivo de descrição da estrutura e utilização do repositório

#### Comentários
* Para a execução com interface, a cada operação, o programa questiona ao usuário se deseja exportar o resultado, no que responder afirmativamente preenche o arquivo de saída preenchido com as informações recebidas na entrada.
* As saídas de grafos da parte 1 são exportadas na linguagem .DOT
* As saídas de conjuntos de vértices da parte 2 são explicadas no arquivo `readme.md` dentro da pasta `results`.
