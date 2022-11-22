 <p>O repositório destina-se à implementação do trabalho da disciplina DCC059 - Teoria dos Grafos desenvolvido pelo
        grupo de nº 11 no período letivo 2022-3, em mérito da avaliação do Professor Stênio Sã Rosário Furtado Soares,
        Universidade Federal de Juiz de fora.</br> Este, é integrado por: CAIO HENRIQUE VIEIRA COSTA, CELSO GABRIEL
        DUTRA ALMEIDA MALOSTO, LUCAS DUARTE CHAVES, LUCAS PAIVA DOS SANTOS e RODRIGO SOARES DE ASSIS.
    <p>
    <p><b>Seguem instruções e informações para o uso adequado do repositório com suas classes e demais definições.</b>
    </p>
    <p>Dentre o grupo convencionou-se o uso da IDE Visual Studio code, com isso, a pasta de nome ".vscode" contém o
        código necessário para montagem do projeto sem que haja necessidade de arquivo makefile ou semelhante.</p>
    <p>Após aceitar o convite para o repositório, clone-o para sua máquina porém, antes de enviar alguma alteração, crie
        novo branch com seu código e relate ao grupo, afim de evitar conflitos de merge bem como possíveis bugs.</p>
    <p>Para executar o projeto rapidamente use a seguinte linha: <b>g++ -g *.cpp -o execGrupo11 && ./execGrupo11
            <i>input.txt output.dot</i> 0 0 0</b></p>
    <p><b>Sobre esta linha</b></p>
    <ul>
        <li>Perceba que <i>-g</i> é dispensável para criação e execução do projeto, porém, é necessário para depuraração
            do código</li>
        <li>Os arquivos enviados para a avaliação serão somente código fonte, mas, o padrão utilizado pelo Professor é
            nomear os executáveis a partir dos números dos grupos, em paralelo, usa-se aqui <i>execGrupo11</i></li>
        <li>As operações de criar e executar o arquivo poderiam ser feitas em duas linhas separadas, contudo, é
            conveniente a contração em somente uma usando <i>&& ./execGrupo11</i></li>
        <li><i>input.txt</i> é o arquivo texto com a instância do grafo que será tratado, <a
                href="https://classroom.google.com/u/0/c/NDg5MDk3MTI5NTc4/m/NTU1NzU2NDI4Njk2/details">clicando aqui</a>
            encontram-se as instâncias sugeridas pelo Professor.</li>
        <li><i>output.dot</i> é o arquivo em linguagem dot que pode ser exportado a partir do projeto</li>
        <li>Após cada execução o programa questiona ao usuário se deseja exportar o grafo, responder afirmativamente
            cria o arquivo <i>output.dot</i> preenchido com as informações recebidas na entrada
        </li>
        <li>A primeira linha do arquivo texto corresponde ao grau do grafo, as demais correspondem às relações inerentes
            ao grafo e seus devidos pesos
        </li>
        <li>Ao final da linha existem três booleanos -na linha citada <i>0 0 0</i>- cuja natureza deve ser informada
            antes da execução do programa, cada um deles corresponde a, respectivamente: se o grafo é direcionado; se o
            grafo é ponderado nas arestas; se o grafo é ponderado nos vértices
        </li>
            <ul>
