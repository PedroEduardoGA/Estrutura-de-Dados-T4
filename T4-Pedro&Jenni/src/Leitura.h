#ifndef _H_LEITURA
#define _H_LEITURA
#include "Cidade.h"
#include "Quadra.h"
#include "Grafo.h"

/*Leitura.h lê os arquivos geo, via e qry, recebendo suas informações e processando cada etapa chamando funções provenientes de arquivos.h externos para realizar
os processos mais aprofundados, criando as saídas svg e txt, específicas de acordo com cada informação de entrada dos arquivos geo, via e qry*/

void Leitura_Geo(char EntryPathGeo[], char SvgGeo[],char EntryPathQry[],char qryNoExtention[],char EntryPathV[]);  //Lê os valores de entrada do arquivo geo, e as informacoes de quadras na arvore avl, caso nao seja possivel abrir o arquivo .geo o programa é finalizdo!
void Leitura_Via(Cidade city, char EntryPathV[], char EntryPathQry[], char qryNoExtention[], char SvgGeo[]); //Lê os valores de entrada do arquivo via, insere no grafo os vertices e as arestas informadas, caso tenha sido informado um arquivo .qry chama a funcao leituraQRY, caso nao seja possivel abrir o arquivo .via o programa é finalizdo!
void Leitura_Qry(Cidade city, char EntryPathQry[], char qryNoExtention[], GrafoV grafo);  //Lê os valores de entrada do arquivo qry e executa os comandos especificados com esses valores, criando os arquivos de saída svg, dot e txt das consultas qry, caso nao seja possivel abrir o arquivo .qry o programa é finalizdo!
#endif
