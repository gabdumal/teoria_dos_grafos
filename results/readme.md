# Read me

## Esta pasta guarda os resultados finais da execução do programa de conclusão da disciplina DCC059 - Teoria dos Grafos.

### O software foi desenvolvido por:

1. Caio Henrique Vieira Costa
2. Celso Gabriel Dutra Almeida Malosto
3. Lucas Duarte Chaves
4. Lucas Paiva dos Santos
5. Rodrigo Soares de Assis

### Encontra-se neste diretório duas pastas:

- **raw** - Arquivos originais de resultado das soluções;
- **compiled** - Arquivos resumidos, compilando as execuções dos algoritmos guloso, randomizado e reativo para cada instância testada;
- **proof_100_500_3** - Comprovação de que o algoritmo reativo executado para a instância 100_500_3, que retornou custo total de 431, o qual é maior que o descrito pela literatura, de fato construiu uma solução válida.

#### Pasta **raw**

Apresenta 30 arquivos, quais sejam 3 para cada uma das 10 instâncias avaliadas, divididos pelo tipo de algoritmo usado.
O nome de um arquivo indica sua especificação da seguinte forma: `[tipo_do_algoritmo]_[nome_da_instancia].txt`.

##### Os arquivos para o algoritmo **guloso** apresentam:

1. nome da instância;
2. custo total obtido;
3. quantidade de vértices no conjunto solução;
4. tempo de processamento em segundos.

##### Os arquivos para o algoritmo guloso **randomizado** apresentam:

1. nome da instância;
2. alfa usado para dado bloco de execuções;
   2.1. número da execução para dado alfa;
   &nbsp;&nbsp;&nbsp;&nbsp;2.1.1. custo total obtido;
   &nbsp;&nbsp;&nbsp;&nbsp;2.1.2. quantidade de vértices no conjunto solução;
   &nbsp;&nbsp;&nbsp;&nbsp;2.1.3. tempo de processamento em segundos;
   &nbsp;&nbsp;&nbsp;&nbsp;2.1.4. semente de randomização utilizada.

##### Os arquivos para o algoritmo guloso randomizado **reativo** apresentam:

1. nome da instância;
2. número da execução;
   2.1. custo total obtido;
   2.2. quantidade de vértices no conjunto solução;
   2.3. tempo de processamento em segundos;
   2.4. semente de randomização utilizada;
   2.5. melhor dentre os alfas utilizados.

#### Pasta **compiled**

Apresenta 22 arquivos, quais sejam 10 para a compilação de resultados de custo das instâncias, outros 10 da mesma forma para o tempo decorrido, e 2 arquivos com tais informações resumidas de todas as instâncias, um para custo e outro para tempo.
O nome de um arquivo indica sua especificação da seguinte forma: `[custo_ou_tempo]_[nome_da_instancia].txt`.

##### Uma linha de um arquivo indica, em ordem, os resultados quanto a:

1. Algoritmo Guloso;
2. Algoritmo Randomizado, α = 0.15;
3. Algoritmo Randomizado, α = 0.30;
4. Algoritmo Randomizado, α = 0.50;
5. Algoritmo Reativo.

#### Pasta **proof_100_500_3**

Apresenta 1 arquivo TXT de output, 3 arquivos DOT de definição de grafo, e 4 arquivos PNG para representação de grafos. Estes arquivos permitem visualizar que a solução é válida.

##### Arquivos:

- **outpux.txt** - resultado da execução do algoritmo reativo ;
- **original.dot** - arquivo DOT que representa a instância 100_500_3;
- **solution_nodes.dot** - arquivo DOT que representa a instância 100_500_3, com os nós do conjunto solução marcados em laranja;
- **solution_incident_nodes.dot** - arquivo DOT que representa a instância 100_500_3, com os nós do conjunto solução marcados em laranja, e as arestas incidentes a estes marcadas em vermelho e destacadas;
- **original.png** - arquivo PNG que representa a instância 100_500_3;
- **solution_nodes.png** - arquivo PNG que representa a instância 100_500_3, com os nós do conjunto solução marcados em laranja;
- **solution_incident_nodes.png** - arquivo PNG que representa a instância 100_500_3, com os nós do conjunto solução marcados em laranja, e as arestas incidentes a estes marcadas em vermelho e destacadas;
- **covered_nodes.png** - arquivo PNG que representa a instância 100_500_3, com os nós do conjunto solução marcados em laranja, as arestas incidentes a estes marcadas em vermelho e destacadas, e os nós não pertencentes ao conjunto solução, mas que são adjacentes a esses, marcados em lilás.
