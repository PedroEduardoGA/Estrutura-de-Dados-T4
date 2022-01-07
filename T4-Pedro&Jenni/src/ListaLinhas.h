#ifndef _H_LISTALINHAS
#define _H_LISTALINHAS

/*ListaLinhas.h possui funcoes da lista dinamica para manipulacao e insercao de linhas e retangulos que serão impressos no fim da leitura do arquivo qry */

typedef void* NoL;
typedef void* ListaL;

ListaL createListLine();                        //cria a lista dinamica de linhas e retangulos

NoL getFirstLine(ListaL lista);                 //retorna o primeiro nó da lista dinamica de linhas e retangulos

NoL getLastLine(ListaL lista);                  //retorna o ultimo nó da lista dinamica de linhas e retangulos

void InsertLine(ListaL pont, double x1,double y1,double x2,double y2,double espessura, char cor[],char tracejado[]);  //insere um nó na lista dinamica de linhas e retangulos com as informacoes passadas nos parametros

void PrintSvgLine(NoL elemento, FILE* svg);     //imprime a linha do argumento no arquivo svg

void PrintSvgLineTracejado(NoL elemento, FILE* svg); //imprime a linha do argumento no arquivo svg com tracejado

void PrintSvgRect(NoL elemento, FILE* svg);     //imprime o retangulo do argumento no arquivo svg

void removeListLine(ListaL lista);              //remove(libera) a lista dinamica de linhas e retangulos

#endif

