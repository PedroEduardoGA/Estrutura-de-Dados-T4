#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Grafo.h"
#include "ConsultaQry.h"//FuncaoCx

#define true 1
#define false 0
#define infinito 5000000.0

typedef struct ARESTAS{
    int I_vertice;
    char Nome[40];
    Quadra quadraEsq,quadraDir;
    Vertice v1,v2;
    double vm,cmp;
    struct ARESTAS *prox,*ante;
}Arestas;

typedef struct VERTICES{
    char id[40];
    int visitado,regiao,qtdChegam;//regiao,qtdChegam novidade-FuncaoCx
    bool ativo;
    double x,y;
    Arestas *arestaVert,*ultimo;
}Vertices;


typedef struct GRAFO {
    int totalVertices;
    Vertices *grafoVertices;
}Grafo;

GrafoV criaGrafo(int nv){
    Grafo *g=(Grafo*) malloc(sizeof(Grafo));
    g->totalVertices=nv;
    g->grafoVertices= (Vertices*) calloc(nv,(sizeof(Vertices)));

    for(int x=0; x<nv; x++)
        g->grafoVertices[x].arestaVert=NULL;

    return g;
}

void insereVertice(GrafoV grafo,char ID[40],double x,double y){
    Grafo* g = (Grafo*) grafo;

    for(int cont=0; cont<g->totalVertices; cont++){
        if(g->grafoVertices[cont].id[0]==0){//caso a primeira posicao da string id seja 0 aquele id nao foi atribuido
            strcpy(g->grafoVertices[cont].id,ID);
            g->grafoVertices[cont].x=x;
            g->grafoVertices[cont].y=y;
            g->grafoVertices[cont].visitado=0;
            g->grafoVertices[cont].ativo = true;

            g->grafoVertices[cont].qtdChegam=0;//FuncaoCx
            g->grafoVertices[cont].regiao=0;//FuncaoCx

            break;
        }
    }
}

void insereAresta(Vertice v1,Vertice v2,Quadra quadEsq,Quadra quadDir, double vm, double cmp,char Rua[40],int vert){
    Vertices* V1= (Vertices*) v1;

    Arestas *novaAresta = (Arestas*) malloc(sizeof(Arestas));

    strcpy(novaAresta->Nome,Rua);
    novaAresta->vm = vm;
    novaAresta->cmp = cmp;
    novaAresta->quadraDir = quadDir;
    novaAresta->quadraEsq = quadEsq;
    novaAresta->v1 = v1;
    novaAresta->v2 = v2;
    novaAresta->I_vertice=vert;

    if(V1->arestaVert == NULL){
        V1->arestaVert = novaAresta;
        novaAresta->ante = NULL;
    }else{
        novaAresta->ante = V1->ultimo;
        V1->ultimo->prox = novaAresta;
    }

    novaAresta->prox = NULL;
    V1->ultimo = novaAresta;
}

char* getID_Vertice(Vertice v){
    Vertices* V = (Vertices*) v;
    return V->id;
}

double getX_Vertice(Vertice v){
    Vertices* V = (Vertices*) v;
    return V->x;
}

double getY_Vertice(Vertice v){
    Vertices* V = (Vertices*) v;
    return V->y;
}

double getCmp_Aresta(Aresta arest){
    Arestas* aresta = (Arestas*) arest;
    return aresta->cmp;
}

double getVm_Aresta(Aresta arest){
    Arestas* aresta = (Arestas*) arest;
    return aresta->vm;
}

char* getNome_Aresta(Aresta arest){
    Arestas* aresta = (Arestas*) arest;
    return aresta->Nome;
}

int getTamanho_Grafo(GrafoV grafo){
    Grafo* g = (Grafo*) grafo;
    return g->totalVertices;
}

int getVisitado_Vertice(Vertice v){
    Vertices* V = (Vertices*) v;
    return V->visitado;
}

void setVisitado_Vertice(Vertice v, int i){
    Vertices* V = (Vertices*) v;
    V->visitado = i;
}

void setVelocidade_Aresta(Aresta arest, double f){
    Arestas* aresta = (Arestas*) arest;
    aresta->vm = aresta->vm - ((aresta->vm)*f);
}

Vertice getVertice_Grafo(GrafoV grafo,int i){
    Grafo* g = (Grafo*) grafo;
    return &(g->grafoVertices[i]);
}

Vertice getVertice_Aresta(Aresta arest,int type){//se type==1 retorna o v1, se type==0 retorna v2
    Arestas* aresta = (Arestas*) arest;
    if(type == 1)
        return aresta->v1;
    else
        return aresta->v2;
}

Quadra getQuadra_Aresta(Aresta arest,int type){//se type==0 retorna o quadra esquerda, se type==1 retorna quadra direita
    Arestas* aresta = (Arestas*) arest;
    if(type)
        return aresta->quadraDir;
    else
        return aresta->quadraEsq;
}

Aresta getListaArestas(Vertice v){
    Vertices* V= (Vertices*) v;

    if(V == NULL || V->arestaVert == NULL)//vertice passado nao existe ou nao possui arestas
        return NULL;

    return V->arestaVert;//retorna lista das arestas daquele vertice
}

Aresta getNextAresta(Aresta arest){
    Arestas* aresta = (Arestas*) arest;

    return aresta->prox;
}

void PrintSvgGrafo(GrafoV grafo, FILE* svg, int i){
    Grafo* g = (Grafo*) grafo;
    char* cor;//FuncaoCx

    if(g == NULL)
        return;


    if(g->grafoVertices[i].id[0] != 0){
        cor = CorRegiao(getRegiao(&(g->grafoVertices[i])));//atribuo pra cor a cor da regiao de acordo com o inteiro daquele vertice, novidade-FuncaoCx
        if(g->grafoVertices[i].regiao > 0)//FuncaoCx
            fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" fill=\"%s\" stroke=\"%s\" r=\"18\" />\n",g->grafoVertices[i].x,g->grafoVertices[i].y,cor,cor);//FuncaoCx

        fprintf(svg, "\t<circle cx=\"%lf\" cy=\"%lf\" fill=\"red\" stroke=\"red\" r=\"5\" />\n",g->grafoVertices[i].x,g->grafoVertices[i].y);
        PrintSvgAresta(g->grafoVertices[i].arestaVert,svg);
    }

    if(i < g->totalVertices-1)
        PrintSvgGrafo(g,svg,++i);
}

void PrintSvgAresta(Aresta aresta, FILE* svg){
    Arestas* A = (Arestas*) aresta;

    if(A == NULL)
        return;

    fprintf(svg, "\t\t\t<line x1=\"%lf\"  y1=\"%lf\"   x2=\"%lf\"  y2=\"%lf\" stroke=\"red\"/>\n",getX_Vertice(A->v1),getY_Vertice(A->v1),getX_Vertice(A->v2),getY_Vertice(A->v2));
    if(getX_Vertice(A->v1) == getX_Vertice(A->v2)){//aresta vertical
        fprintf(svg, "\t\t\t<line x1=\"%lf\"  y1=\"%lf\"   x2=\"%lf\"  y2=\"%lf\" stroke=\"red\"/>\n",getX_Vertice(A->v2),getY_Vertice(A->v2),getX_Vertice(A->v2)-10,getY_Vertice(A->v2)-10);
        fprintf(svg, "\t\t\t<line x1=\"%lf\"  y1=\"%lf\"   x2=\"%lf\"  y2=\"%lf\" stroke=\"red\"/>\n",getX_Vertice(A->v2),getY_Vertice(A->v2),getX_Vertice(A->v2)+10,getY_Vertice(A->v2)-10);
    }

    if(getY_Vertice(A->v1) == getY_Vertice(A->v2)){//aresta horizontal
        fprintf(svg, "\t\t\t<line x1=\"%lf\"  y1=\"%lf\"   x2=\"%lf\"  y2=\"%lf\" stroke=\"red\"/>\n",getX_Vertice(A->v2),getY_Vertice(A->v2),getX_Vertice(A->v2)-10,getY_Vertice(A->v2)-10);
        fprintf(svg, "\t\t\t<line x1=\"%lf\"  y1=\"%lf\"   x2=\"%lf\"  y2=\"%lf\" stroke=\"red\"/>\n",getX_Vertice(A->v2),getY_Vertice(A->v2),getX_Vertice(A->v2)-10,getY_Vertice(A->v2)+10);
    }

    PrintSvgAresta(A->prox,svg);
}

Vertice procuraVertice(GrafoV grafo, char nome[40], int i,int* indice){
    Grafo* g = (Grafo*) grafo;
    Vertices *aux = NULL;

    if(i == g->totalVertices)
        return NULL;

    if(strcmp(g->grafoVertices[i].id,nome) == 0){//caso a primeira posicao da string id seja 0 aquele id nao foi atribuido
        aux = &(g->grafoVertices[i]);
        *indice=i;
        return aux;
    }

    aux = procuraVertice(grafo,nome,++i,indice);

    return aux;
}

Aresta procuraArestaLista(Vertice v2,Aresta arest){
    Vertices* V2= (Vertices*) v2;
    Arestas* aresta = (Arestas*) arest;

    if(aresta == NULL)
        return NULL;

    if(aresta->v2 == V2)
        return aresta;

    return procuraArestaLista(V2,aresta->prox);
}

void removeGrafo(GrafoV grafo){
    Grafo* g = (Grafo*) grafo;
    int i = 0;

    while(i != g->totalVertices){
        if(g->grafoVertices[i].id[0] != 0){
            removeListaAresta(g->grafoVertices[i].arestaVert,0,NULL);
        }
        i++;
    }
    free(g->grafoVertices);
    free(g);
}

void removeVertice(GrafoV grafo,int i,Vertice vert, FILE* txt){
    Grafo* G = (Grafo*) grafo;
    Vertices* v = (Vertices*) vert;

    if(&(G->grafoVertices[i]) == v){
        strcpy(G->grafoVertices[i].id,"");
        G->grafoVertices[i].x = 0;
        G->grafoVertices[i].y = 0;
        G->grafoVertices[i].regiao = -1;
        removeListaAresta(G->grafoVertices[i].arestaVert,1,txt);
        G->grafoVertices[i].arestaVert = NULL;
        G->grafoVertices[i].ultimo = NULL;
        percorreAresta_Vertice(grafo,vert,0,txt);
        return;
    }

    if(i < G->totalVertices -1){
        removeVertice(grafo,++i,vert,txt);
    }
}

void percorreAresta_Vertice(GrafoV grafo,Vertice vertRemovido,int i,FILE* txt){
    Grafo* g = (Grafo*) grafo;

        removeArestaChegada(&(g->grafoVertices[i]),g->grafoVertices[i].arestaVert,vertRemovido,txt);

    if(i < g->totalVertices-1)
        percorreAresta_Vertice(grafo,vertRemovido,++i,txt);
}

void removeArestaChegada(Vertice vert, Aresta arestas, Vertice vertRem, FILE* txt){
    Vertices* V = (Vertices*) vert;
    Vertices* vRem = (Vertices*) vertRem;
    Arestas* A = (Arestas*) arestas;
    Arestas* Aux;//novidade

    if(A == NULL)
        return;

    if(vRem == NULL){//pode remover
        return;
    }

    Aux=A->prox;//novidade
    if(A->v2 == vRem){
        if(A->prox != NULL){//novidade
            if(V->arestaVert == A){
                V->arestaVert = A->prox;
                A->prox->ante = NULL;
            }else{
                    A->prox->ante = A->ante;
                    A->ante->prox = A->prox;
                }
        }else
            V->arestaVert=NULL;//novidade se n tem prox, é só atribuir nulo pra aquela aresta

        fprintf(txt,"\nAresta Removida - Rua: %s  Velocidade: %lf  Comprimento: %lf",A->Nome,A->vm,A->cmp);

        free(A);
    }

    removeArestaChegada(V,Aux,vRem,txt);//novidade troquei o A->prox por aux

}

void removeListaAresta(Aresta arestas, int dados, FILE* txt){
    Arestas* aux1 = (Arestas*) arestas;
    Arestas* aux2;

    if(aux1 == NULL)
        return;

    while(aux1 != NULL){
        if(dados){
            fprintf(txt,"\nAresta Removida  -  Rua: %s  Velocidade: %lf  Comprimento: %lf",aux1->Nome,aux1->vm,aux1->cmp);
        }
        aux2 = aux1->prox;
        free(aux1);
        aux1 = aux2;
    }
}

void setRegiao(Vertice vert,int reg){//FuncaoCx
    Vertices* V = (Vertices*) vert;
    V->regiao=reg;
}

int getRegiao(Vertice vert){//FuncaoCx
    Vertices* V = (Vertices*) vert;
    return V->regiao;
}

void setArestachegam(Vertice v,int i){//FuncaoCx
    Vertices* V= (Vertices*) v;
    V->qtdChegam=i;
}

void zeraArestasVertices(GrafoV grafo){//FuncaoCx
    Grafo* g = (Grafo*) grafo;

    for(int cont=0; cont<g->totalVertices; cont++)
        g->grafoVertices[cont].qtdChegam=0;
}

void atualizaArestasVertices(GrafoV grafo){//FuncaoCx
    Grafo* g = (Grafo*) grafo;
    Arestas* arest;
    int i;

    for(int cont=0; cont<g->totalVertices; cont++){
        arest=g->grafoVertices[cont].arestaVert;
        i=0;
        while(arest!=NULL){
            i++;

            incrementaArestaChegada(arest->v2);
            arest=arest->prox;
        }
    }
}

void incrementaArestaChegada(Vertice v){//FuncaoCx
    Vertices* V= (Vertices*) v;
    V->qtdChegam+=1;
}

int getQtdChegam(Vertice v){//FuncaoCx
    Vertices* V= (Vertices*) v;
    return V->qtdChegam;
}

void iniciaDijkstra(GrafoV g, double* distancia, int* pai, int noInicial) {
    Grafo* grafo = (Grafo*) g;
    for(int i = 0; i < grafo->totalVertices; i++) {
        distancia[i] = infinito;
        pai[i] = -1;
    }
    distancia[noInicial] = 0.0;
}

void relaxaComprimento(GrafoV g, double* distancia, int* pai, int no1, int no2) {
    Grafo* grafo = (Grafo*) g;
    if(grafo->grafoVertices[no2].ativo == false)
        return;
    Arestas* aresta = grafo->grafoVertices[no1].arestaVert;

    while(aresta && aresta->I_vertice != no2){
        aresta = aresta->prox;
    }

    if(aresta) {
        if(distancia[no2] > distancia[no1] + aresta->cmp) {
            distancia[no2] = distancia[no1] + aresta->cmp;
            pai[no2] = no1;
        }
    }
}

void relaxaVelocidade(GrafoV g, double* distancia, int* pai, int no1, int no2) {
    Grafo* grafo = (Grafo*) g;
    if(grafo->grafoVertices[no2].ativo == false)
        return;

    Arestas* aresta = grafo->grafoVertices[no1].arestaVert;

    while(aresta && aresta->I_vertice != no2)
        aresta = aresta->prox;

    if(aresta) {
        if(distancia[no2] > distancia[no1] + (aresta->vm)) {
            distancia[no2] = distancia[no1] + (aresta->vm);
            pai[no2] = no1;
        }
    }
}

bool existeAberto(GrafoV g, int* aberto) {
    Grafo* grafo = (Grafo*) g;
    for(int i = 0; i < grafo->totalVertices; i++) {
        if(aberto[i])
            return true;
    }
    return false;
}

int menorDistancia(GrafoV g, int* aberto, double* distancia) {
    Grafo* grafo = (Grafo*) g;
    int i = 0, menor;

    while(i < grafo->totalVertices) {
        if(aberto[i])
            break;
        i++;
    }

    if(i == grafo->totalVertices)
        return -1;

    menor = i;

    for(i = i+1; i < grafo->totalVertices; i++) {
        if(aberto[i] && distancia[menor] > distancia[i])
            menor = i;
    }
    return menor;
}

int* dijkstra(ListaL listaLinhas,ListaL listaLinhasTrac,GrafoV g, int noInicial, int noFinal,FILE* svg,FILE* txt, char cor1[], char cor2[], int type,double x1,double y1,double x2,double y2){
    if(noInicial == -1 || noFinal == -1) {
        return NULL;
    }

    Grafo* grafo = (Grafo*) g;
    double* distancia = (double*) malloc(grafo->totalVertices*sizeof(double));
    int* caminho = (int*) malloc(grafo->totalVertices*sizeof(int));
    int pai[grafo->totalVertices];
    int menor, aux, i;
    char* direcao, *direcaoAnterior;
    int aberto[grafo->totalVertices];
    Arestas* aresta;

    iniciaDijkstra(grafo, distancia, pai, noInicial);

    for(i = 0; i < grafo->totalVertices; i++){
        aberto[i] = true;
    }

        while (existeAberto(grafo, aberto))
        {
            menor = menorDistancia(grafo, aberto, distancia);
            aberto[menor] = false;

            aresta = grafo->grafoVertices[menor].arestaVert;
            while(aresta) {
                if(type == 2)
                    relaxaVelocidade(grafo, distancia, pai, menor, aresta->I_vertice);
                else
                    relaxaComprimento(grafo, distancia, pai, menor, aresta->I_vertice);

                aresta = aresta->prox;
            }
        }
        aux = noFinal;

        for(i = 0; i < grafo->totalVertices; i++)
            caminho[i] = -1;

        i = grafo->totalVertices-1;
        while(aux != -1 && i >= 0) {
            caminho[i] = aux;
            i--;
            aux = pai[aux];

        }
//
        //desenhar ponto de inicio no svg
        for(i = 0; i < grafo->totalVertices - 1; i++) {
            if(caminho[i] == -1)
                continue;
            if(type == 1){
                InsertLine(listaLinhas,grafo->grafoVertices[caminho[i]].x,grafo->grafoVertices[caminho[i]].y,grafo->grafoVertices[caminho[i+1]].x,grafo->grafoVertices[caminho[i+1]].y,4,cor1,"0,0");
                fprintf(svg, "\t<path d=\"M%lf,%lf %lf,%lf\" style=\"stroke: #000000; stroke-width:4; stroke-dasharray:2,2\"/> <circle cx=\"0\" cy=\"0\" r=\"5\" stroke=\"red\" fill=\"red\"> <animateMotion path =\"M%lf,%lf %lf,%lf\" begin=\"0s\" dur=\"3s\" repeatCount=\"indefinite\" /> </circle>\n",grafo->grafoVertices[caminho[i]].x,grafo->grafoVertices[caminho[i]].y,grafo->grafoVertices[caminho[i+1]].x,grafo->grafoVertices[caminho[i+1]].y,grafo->grafoVertices[caminho[i]].x,grafo->grafoVertices[caminho[i]].y,grafo->grafoVertices[caminho[i+1]].x,grafo->grafoVertices[caminho[i+1]].y);

            }else{
                InsertLine(listaLinhas,grafo->grafoVertices[caminho[i]].x-4,grafo->grafoVertices[caminho[i]].y-4,grafo->grafoVertices[caminho[i+1]].x-4,grafo->grafoVertices[caminho[i+1]].y-4,4,cor2,"0,0");
                fprintf(svg, "\t<path d=\"M%lf,%lf %lf,%lf\" style=\"stroke: #000000; stroke-width:4; stroke-dasharray:2,2\"/> <circle cx=\"0\" cy=\"0\" r=\"5\" stroke=\"red\" fill=\"red\"> <animateMotion path =\"M%lf,%lf %lf,%lf\" begin=\"0s\" dur=\"3s\" repeatCount=\"indefinite\" /> </circle>\n",grafo->grafoVertices[caminho[i]].x-4,grafo->grafoVertices[caminho[i]].y-4,grafo->grafoVertices[caminho[i+1]].x-4,grafo->grafoVertices[caminho[i+1]].y-4,grafo->grafoVertices[caminho[i]].x-4,grafo->grafoVertices[caminho[i]].y-4,grafo->grafoVertices[caminho[i+1]].x-4,grafo->grafoVertices[caminho[i+1]].y-4);
            }
        }

        if(type == 1)
            fprintf(txt, "\nCaminho mais curto:");
        else
            fprintf(txt, "\nCaminho mais rapido:");

        direcaoAnterior = "direcaoAnterior";

        for(i = 0; i < grafo->totalVertices - 1; i++) {
            if(caminho[i] == -1){
                continue;
            }
            aresta = getInfoAresta(grafo, caminho[i], caminho[i+1]);
            if(grafo->grafoVertices[caminho[i]].x < grafo->grafoVertices[caminho[i+1]].x)
                direcao = "Oeste";
            else if(grafo->grafoVertices[caminho[i]].x > grafo->grafoVertices[caminho[i+1]].x)
                direcao = "Leste";
            else if(grafo->grafoVertices[caminho[i]].y < grafo->grafoVertices[caminho[i+1]].y)
                direcao = "Norte";
            else if(grafo->grafoVertices[caminho[i]].y > grafo->grafoVertices[caminho[i+1]].y)
                direcao = "Sul";

            if(strcmp(direcaoAnterior,"direcaoAnterior") == 0) {
                fprintf(txt, "\nSiga na direcao %s na Rua %s ", direcao, aresta->Nome);
            }else if(direcao != direcaoAnterior) {
                fprintf(txt, "ate o cruzamento com a Rua %s. ", aresta->Nome);
                fprintf(txt, "Siga na direcao %s na Rua %s ", direcao, aresta->Nome);
            }

            direcaoAnterior = direcao;
        }

        if(strcmp(direcaoAnterior, "direcaoAnterior") == 0){
            fprintf(txt, "\nNao ha caminho entre esses dois pontos.\n");
            InsertLine(listaLinhasTrac,x1,y1,x2,y2,4,"red","4,3");
            fprintf(svg, "\t<path d=\"M%lf,%lf %lf,%lf\" style=\"stroke: #000000; stroke-width:1; stroke-dasharray:2,2\"/> <circle cx=\"0\" cy=\"0\" r=\"5\" stroke=\"red\" fill=\"red\"> <animateMotion path =\"M%lf,%lf %lf,%lf\" begin=\"0s\" dur=\"6s\" repeatCount=\"indefinite\" /> </circle>\n",x1,y1,x2,y2,x1,y1,x2,y2);

        } else {
            fprintf(txt, ". Chegou em seu destino.\n");
        }

        free(distancia);
        free(caminho);

        return NULL;
}

Aresta getInfoAresta(GrafoV g, int noInicial, int noFinal) {
    Grafo* grafo = (Grafo*) g;
    Arestas *aresta = grafo->grafoVertices[noInicial].arestaVert;
        while(aresta) {
            if(aresta->I_vertice == noFinal){
              return aresta;
            }
            aresta = aresta->prox;
        }
        printf("Aresta nao encontrada\n");//[remover]
        return NULL;
}

double distancia (double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;

    return sqrt((dx * dx) + (dy * dy));
}

int getI_VerticeProx(GrafoV grafo,double x,double y){

    double menor_distancia=999999999,dist;
    Grafo* g = (Grafo*) grafo;
    int menor=-1;

    for(int i = 0; i < g->totalVertices - 1; i++){
        dist = distancia(x,y,g->grafoVertices[i].x,g->grafoVertices[i].y);
        if(dist < menor_distancia){
            menor_distancia=dist;
            menor=i;
        }
    }

    return menor;
}

int getIndiceVertice(GrafoV g, char id[]) {
    Grafo* grafo = (Grafo*) g;

    for(int i = 0; i < grafo->totalVertices; i++) {

        if(strcmp(grafo->grafoVertices[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}



