# Projeto T4 - Estrutura de Dados II
*Projeto desenvolvido em conjunto com [Jennifer do Prado](https://github.com/JenniferPrado7350), foi utilizado o sistema operacional Windows 7 e o Linux no desenvolvimento do projeto, para o funcionamento do mesmo, todos os arquivos.c e arquivos.h são compilados executando o comando make no terminal, então o makefile será executado realizando a compilação de todos os códigos e gerando um executável para o projeto: **t2**, t2 pois foi o segundo trabalho desenvolvido na disciplina de Estrutura de Dados II, para utilizar o projeto é necessário informar parâmetros de entrada via argumentos pela linha de comando no terminal, cmd ou PowerShell, exemplo:*

### ./t2 -e DiretórioEntrada -f nome_arquivo.geo -q SubDiretório/nome_arquivo.qry -v nome_arquivo.via -o DiretórioSaida
---
*Em resumo o projeto recebe um arquivo .geo que contém coordenadas para geração de retângulos(Quadras), um arquivo .via que contém dados de arestas(Ruas) e circulos(vértices) e um arquivo .qry que contém consultas para serem realizadas com estes dados informados no arquivo .geo e no arquivo .via, o projeto utiliza as seguintes estruturas de dados: **Arvore KD**, **Lista Dinâmica** e **Grafo**, o projeto gera no diretório de saída arquivos .svg e .txt para mostrar os resultados das consultas realizadas ao longo da execução. Alguns exemplos de consultas são remoções de retângulos, cálculo de menor caminho de um ponto a outro, geração de árvore geradora mínima e cálculo de regiões isoladas.*

*No arquivo.geo temos como argumentos:*
- **q** (Informa os parâmetros de um retângulo a ser inserido na Arvore KD)
- **cq** (Informa as cores de preenchimento e de borda a serem usadas nos retângulos e uma espressura)  
*Após a leitura do .geo os retângulos informados são inseridos na arvore KD e é gerado um arquivo .svg inicial que contém os retângulos desenhados.*

*No arquivo.via temos como argumentos:*
- **nv** (Informa um inteiro que é a estimativa da quantidade de vértices que serão inseridos no grafo. **OBS:** *Este deve sempre ser o primeiro parâmetro do arquivo.via*)
- **v** (Informa o id de um vértice e suas coordenadas x,y) 
- **e** (Cria uma nova aresta, informa os id's dos vértices que serão ligados a esta aresta, o(s) CEP(s) da(s) quadra(s) laterais(Esquerda/Direita), o comprimento da aresta, sua velocidade média e um nome da mesma) 

*No arquivo.qry temos 5 consultas:*
- **@o?** (Informa um endereço(CEP/Face/Número) e o programa vai buscar esse endereço e armazenar em um registrador sua posição geográfica)
- **catac** (Informa uma região(Coordenadas x,y e dimensões de largura e altura) e o programa vai remover todas as quadras, arestas e vértices que estiverem dentro dessa região informada)
- **rv** (Informa uma região(Coordenadas x,y e dimensões de largura e altura) e um fator(f) e o programa vai calcular a árvore geradora mínima de acordo com os vértices e arestas que estiverem dentro dessa região, gerando assim um subgrafo que não possui ciclos fechados, após isso será calculado a nova velocidade média de todas arestas que estiverem contidas nessa árvore geradora mínima de acordo com o fator(f) informado)
- **cx** (Informa um valor(double) de limite, que será utilizado pelo programa para calcular as regiões isoladas do gráfico, regiões que estiverem desconexas no grafo, arestas que possuirem a velocidade média inferior ao limite informado também serão consideradas regiões desconexas)
-  **p?** (Informa um endereço(CEP/Face/Número) e cores(cmc/cmr) que serão usadas para colorir o trajeto calculado e o programa vai buscar esse endereço e calcular o trajeto mais curto do ponto inicial(@o?) até esse ponto informado utilizando o algoritmo de djikstra e colorir o trajeto na cor(cmc) e também será calculado o trajeto mais rápido pelo djikstra sendo usado como peso da aresta sua velocidade média e este trajeto será colorido com a cor(cmr). **OBS:** *Note que para haver essa consulta, é OBRIGATÓRIO que tenha ocorrido uma consulta @o? anteriormente)* 

### Resumo dos Parâmetros do programa:
|  Argumento  | Opcional  |    Descrição   |
| :---         |     :---:      |          ---: |
| -e diretórioEntrada   | Sim     | Informa o caminho para o diretório de entrada(Caso exista) que contém os arquivos de entrada do programa    |
| -f nome_arquivo.geo    | Não      | Informa o nome do arquivo.geo que contém os dados iniciais para execução do programa      |
| -q Subdir/nome_arquivo.qry   | Sim    | Informa o subdiretório(Caso esteja em um) e o nome do arquivo.qry que contém os parâmetros de consulta para ser utilizado com um arquivo.geo informado posteriormente    |
| -via nome_arquivo.via    | Sim      | Informa o nome do arquivo.via que contém os dados dos vértices e das arestas para execução do programa     |
| -o diretórioSaída   | Não     | Informa o caminho para o diretório de saída que será usado para armazenas os arquivos gerados ao longo da execução do programa    |




 
