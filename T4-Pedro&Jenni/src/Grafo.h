#ifndef _H_GRAFO
#define _H_GRAFO

#include <stdbool.h>
#include "Quadra.h"
#include "ListaLinhas.h"
typedef void* GrafoV;
typedef void* Vertice;
typedef void* Aresta;

GrafoV criaGrafo(int nv);

void insereVertice(GrafoV grafo,char ID[40],double x,double y);

void insereAresta(Vertice v1,Vertice v2,Quadra quadEsq,Quadra quadDir, double vm, double cmp,char Rua[40],int vert);

//Getters:
char* getID_Vertice(Vertice v);     //retorna o id do vertice passado como parametro

double getX_Vertice(Vertice v);     //retorna a coordenada x do vertice passado como parametro

double getY_Vertice(Vertice v);     //retorna a coordenada y do vertice passado como parametro

double getCmp_Aresta(Aresta arest);     //retorna o comprimento da aresta passada como parametro

double getVm_Aresta(Aresta arest);      //retorna a velocidade média da aresta passada como parametro

char* getNome_Aresta(Aresta arest);     //retorna o nome da aresta passada como parametro

int getTamanho_Grafo(GrafoV grafo);     //retorna o tamanho do grafo informado

int getVisitado_Vertice(Vertice v);     //retorna o campo visitado do vertice passado como parametro

void setVisitado_Vertice(Vertice v, int i);     //atribui o valor i pro campo visitado do vertice passado como parametro

void setVelocidade_Aresta(Aresta arest, double f);   //guarda a velocidade nova da aresta recebida no parametro

Vertice getVertice_Grafo(GrafoV grafo,int i);       //retorna o endereço do vertice da posição i do grafo

Vertice getVertice_Aresta(Aresta arest,int type);       //retorna o vertice da aresta, de acordo com o tipo informado, se type = 1 retorna o primeiro vertice, se type = 2 retorna o segundo vertice

Quadra getQuadra_Aresta(Aresta arest,int type);     //retorna o ponteiro pra quadra da aresta informada, se type = 1 retorna ponteiro pra quadra direita, se type = 0 retorna ponteiro pra quadra esquerda

Aresta getListaArestas(Vertice v);     //retorna a o ponteiro para as arestas do vertice passado como parametro

Aresta getNextAresta(Aresta arest);     //retorna a proxima aresta da lista de arestas

//Funcoes Restantes:
void PrintSvgGrafo(GrafoV grafo, FILE* svg, int i);     //printa o vertice i e todas as arestas desse vertice no .svg

void PrintSvgAresta(Aresta aresta, FILE* svg);      //printa no .svg todas as arestas da lista de aresta de forma recursiva

Vertice procuraVertice(GrafoV grafo, char nome[40], int i,int* indice);     //percorre o grafo recursivamente procurando o vertice que possui o id igual ao nome informado, quando é encontrado é retornado, senao retorna NULL

Aresta procuraArestaLista(Vertice v2,Aresta arest);     //percorre a lista de arestas recursivamente, procurando qual aresta aponta pro vertice v2 informadoo, quando é encontrada é retornada, senao retorna NULL

void removeGrafo(GrafoV grafo);     //percorre todo o grafo liberando a lista de arestas de cada vertice, libera todos o vertices do grafo e por fim o grafo

void removeVertice(GrafoV grafo,int i,Vertice vert, FILE* txt);     //remove a lista de arestas do vertice passado como parametro, percorre os vertices buscando qual é o vertice informado

void percorreAresta_Vertice(GrafoV grafo,Vertice vertRemovido,int i,FILE* txt);     //percorre todo o grafo removendo as arestas que chegam no vertice removido informado como parametro

void removeArestaChegada(Vertice vert, Aresta arestas, Vertice vertRem, FILE* txt);     //percorre a lista de arestas removendo as arestas que chegam no vertice removido que é passado como parametro

void removeListaAresta(Aresta arestas, int dados, FILE* txt);       //remove toda a lista de arestas, caso dados = 1 reporta os dados da aresta no arquivo .txt

void setRegiao(Vertice vert,int reg); //seta regiao do vertice passado

int getRegiao(Vertice vert); //retorna regiao do vertice passado

void setArestachegam(Vertice v,int i); //seta a quantidade das arestas do vertice passado com valor de i

void zeraArestasVertices(GrafoV grafo); //zera a quantidade de arestas de chegadas de todos os vertices do grafo

void atualizaArestasVertices(GrafoV grafo); //atualiza a quantidade de arestas de chegadas de todos os vertices do grafo

void incrementaArestaChegada(Vertice v); //incrementa a quantidade de arestas de chegada do vertice passado

int getQtdChegam(Vertice v); //retorna a quantidade de arestas de chegada do vertice passado

void iniciaDijkstra(GrafoV g, double* distancia, int* pai, int noInicial); //inicia o dijkstra zerando os valores usados

void relaxaComprimento(GrafoV g, double* distancia, int* pai, int no1, int no2); //relaxa o comprimento de todo o grafo

void relaxaVelocidade(GrafoV g, double* distancia, int* pai, int no1, int no2); //relaxa a velocidade de todo o grafo

bool existeAberto(GrafoV g, int* aberto); //retorna true se o vetor encontrar uma posicao do vetor == true ou false se nao encontrar

int menorDistancia(GrafoV g, int* aberto, double* distancia); //calcula a menor distancia entre os vertices do grafo

int* dijkstra(ListaL listaLinhas,ListaL listaLinhasTrac,GrafoV g, int noInicial, int noFinal,FILE* svg,FILE* txt, char cor1[], char cor2[], int type,double x1,double y1,double x2,double y2); //algoritmo do dijkstra, retorna um vetor contendo as coordenadas dos caminhos encontrados

Aresta getInfoAresta(GrafoV g, int noInicial, int noFinal); //retorna a aresta que tem o campo i_vertice == noFinal

double distancia (double x1, double y1, double x2, double y2); //retorna a distancia entre o ponto 1 e 2 passado como argumento com suas coordenadas

int getI_VerticeProx(GrafoV grafo,double x,double y); //retorna o indice i do vertice mais proximo das coordenadas passadas como parametro

int getIndiceVertice(GrafoV g, char id[]); //retorna o indice do vertice que possuir o id igual ao id passado

#endif
