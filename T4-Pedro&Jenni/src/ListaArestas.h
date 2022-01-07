#ifndef _H_LISTAARESTAS
#define _H_LISTAARESTAS
#include "Grafo.h"
#include "ListaLinhas.h"

/*ListaArestas.h é um arquivo que contém todas funções necessárias para a manipulação das listas dinamicas duplamente encadeadas, utilizadas para armazenar as
arestas, funcoes para inserir arestas, funcoes de getters, remover uma determinada aresta de um no da lista, e por fim, remove a lista*/

typedef void* ListaAr;
typedef void* NoAr;

ListaAr createListAresta();                                  //cria a lista Dinâmica duplamente encadeada para as arestas e a retorna

NoAr getPreviousAresta(NoAr elemento);                         //retorna o nó anterior ao nó recebido nos parametros

NoAr getNextArestaList(NoAr elemento);                             //retorna o proximo nó do nó "elemento" recebido no parametro

NoAr getFirstAresta(ListaAr lista);                            //retorna o primeiro nó da lista

NoAr getLastAresta(ListaAr lista);                             //retorna o ultimo nó da lista

Aresta getAresta(NoAr elemento);                            //retorna a aresta do nó "elemento" recebido como parametro

int contaArestasSaida(NoAr aresta,Vertice v1, int cont);                    // retorna a quantidade de arestas que saem de v1

int contaArestasEntrada(NoAr aresta,Vertice v1, int cont);                  // retorna a quantidade de arestas que entram em v1

int verificaArestasEntrada_Saida(NoAr aresta,Vertice v2,double y);          //Verifica se pelo menos um vertice que aponta pra v1 tem x igual ao vertice v2, que é o vertice que v1 aponta, retorna  1 se possuir, e 0 caso náo exista

void InsertAresta(ListaAr pont, Aresta aresta,NoAr arest,NoAr auxiliar,int cmc);                //Insere um novo nó no(aresta) no final da lista dinamica com os valores recebidos no parâmetro

void ZerarVisitado(NoAr arest);                                             //atribui 0 ao atributo "visitado" de todos os vertices da arvore geradora mínima

void buscaEmLargura(ListaAr listA,FILE* svg, FILE* txt, double f,ListaL listaLinha,ListaL listaLinhaRaizes);  //realiza a busca em largura do subgrafo que estiver na lista

void removeListAresta(ListaAr lista);                        //remove(libera) a lista dinamica de arestas

void Libera_NO_ListAresta(ListaAr lista, NoAr n);                 //libera um no(aresta) da lista dinamica de arestas

#endif
