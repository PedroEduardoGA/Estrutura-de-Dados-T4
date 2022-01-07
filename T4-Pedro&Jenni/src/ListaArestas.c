#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaArestas.h"
#include "Grafo.h"

typedef struct nodeA
{
    Aresta aresta;
    struct nodeA *ante, *prox;
} NodeA;

typedef struct listaAresta
{
    NodeA *primeiro;
    NodeA *ultimo;
} ListAresta;

ListaAr createListAresta()
{
    ListAresta *listA = (ListAresta *)malloc(sizeof(ListAresta));
    listA->primeiro = NULL;
    listA->ultimo = NULL;
    return listA;
}

NoAr getPreviousAresta(NoAr elemento)
{
    NodeA *no = (NodeA *)elemento;
    if (no != NULL)
        return no->ante;
    else
        return NULL;
}

NoAr getNextArestaList(NoAr elemento)
{
    NodeA *L = (NodeA *)elemento;
    if (L != NULL)
        return L->prox;
    else
        return NULL;
}

NoAr getFirstAresta(ListaAr listA)
{
    ListAresta *L = (ListAresta *)listA;
    return L->primeiro;
}

NoAr getLastAresta(ListaAr listA)
{
    ListAresta *L = (ListAresta *)listA;
    return L->ultimo;
}


Aresta getAresta(NoAr elemento)
{
    NodeA *no = (NodeA *)elemento;
    return no->aresta;
}


int contaArestasSaida(NoAr aresta,Vertice v1, int cont){
    NodeA* noAresta = (NodeA*)aresta;

    if(noAresta == NULL){
        return cont;
    }

    if(getVertice_Aresta(getAresta(noAresta),1) == v1){
        cont++;

    }

    return contaArestasSaida(noAresta->prox,v1,cont);
}

int contaArestasEntrada(NoAr aresta,Vertice v1, int cont){
    NodeA* noAresta = (NodeA*)aresta;

    if(noAresta == NULL)
        return cont;

    if(getVertice_Aresta(getAresta(noAresta),0) == v1){
        cont++;
    }

    return contaArestasEntrada(noAresta->prox,v1,cont);
}

int verificaArestasEntrada_Saida(NoAr aresta,Vertice v1,double y){
    NodeA* noAresta = (NodeA*)aresta;

    if(noAresta == NULL)
        return 0;

    if(getVertice_Aresta(getAresta(noAresta),0) == v1)
        if(getY_Vertice(getVertice_Aresta(getAresta(noAresta),1)) == y)
            return 1;

    return verificaArestasEntrada_Saida(noAresta->prox,v1,y);
}

void InsertAresta(ListaAr pont, Aresta aresta,NoAr arest,NoAr auxiliar,int cmc){
    ListAresta *L = (ListAresta *)pont;
    NodeA *novo = (NodeA *)arest;
    NodeA *aux = (NodeA *)auxiliar;

    if(novo == NULL){
        novo = (NodeA *)malloc(sizeof(NodeA));
        novo->aresta = aresta;
    }

    if (L->primeiro == NULL)
    {
        novo->ante = NULL;
        L->primeiro = novo;
        L->ultimo = novo;
        novo->prox = NULL;
        return;
    }
    else{
        if(cmc == 1){
            if(getCmp_Aresta(aux->aresta) >= getCmp_Aresta(novo->aresta)){
                if(L->primeiro == aux){
                    L->primeiro = novo;
                    novo->ante = NULL;
                }
                else{
                    aux->ante->prox=novo;
                    novo->ante=aux->ante;
                }

                novo->prox = aux;
                aux->ante = novo;

                return;
            }else if(aux->prox == NULL){
                L->ultimo = novo;
                aux->prox = novo;
                novo->ante = aux;
                novo->prox = NULL;
                return;
            }
        }else if(cmc == 0){
            if(getVm_Aresta(aux->aresta) >= getVm_Aresta(novo->aresta)){
                if(L->primeiro == aux){
                    L->primeiro = novo;
                    novo->ante = NULL;

                }else{
                    aux->ante->prox=novo;
                    novo->ante=aux->ante;
                }

                novo->prox = aux;
                aux->ante = novo;

                return;
            }else if(aux->prox == NULL){
                L->ultimo = novo;
                aux->prox = novo;
                novo->ante = aux;
                novo->prox = NULL;
                return;
            }
        }
    }
    InsertAresta(pont,aresta,novo,aux->prox,cmc);

}

void ZerarVisitado(NoAr arest){
    NodeA *noA = (NodeA *)arest;

    if(noA == NULL)
        return;

    setVisitado_Vertice(getVertice_Aresta(getAresta(noA),1),0);
    setVisitado_Vertice(getVertice_Aresta(getAresta(noA),0),0);

    ZerarVisitado(noA->prox);
}

void buscaEmLargura(ListaAr listA,FILE* svg, FILE* txt, double f,ListaL listaLinha,ListaL listaLinhaRaizes){
    ListAresta *L = (ListAresta *)listA;
    NodeA *no1 = L->primeiro;
    NodeA *no2 = L->primeiro;
    Aresta arest;
    double fator = f;

    ZerarVisitado(getFirstAresta(listA));

    while(no1 != NULL){
        no2 = no1;

        while(no2 != NULL){
            if(getVisitado_Vertice(getVertice_Aresta(getAresta(no2),0)) == 0){
                if((getVertice_Aresta(getAresta(no1),1) == getVertice_Aresta(getAresta(no2),1)) || (getVertice_Aresta(getAresta(no1),1) == getVertice_Aresta(getAresta(no2),0))){
                    if(L->primeiro == no2){
                        InsertLine(listaLinhaRaizes,getX_Vertice(getVertice_Aresta(getAresta(no2),1)),getY_Vertice(getVertice_Aresta(getAresta(no2),1)),getX_Vertice(getVertice_Aresta(getAresta(no2),0)),getY_Vertice(getVertice_Aresta(getAresta(no2),0)),5,"#2AD4FF","0,0");

                    }else{
                        InsertLine(listaLinha,getX_Vertice(getVertice_Aresta(getAresta(no2),1)),getY_Vertice(getVertice_Aresta(getAresta(no2),1)),getX_Vertice(getVertice_Aresta(getAresta(no2),0)),getY_Vertice(getVertice_Aresta(getAresta(no2),0)),5,"#2AD4FF","0,0");

                    }
                    arest = getAresta(no2);
                    setVelocidade_Aresta(arest,fator);
                    fprintf(txt,"\nAresta - Nome: %s   Comprimento: %lf  Velocidade: %lf",getNome_Aresta(arest),getCmp_Aresta(arest),getVm_Aresta(arest));
                }
            }

            no2 = no2->prox;

        }
        fator = fator + f;
        setVisitado_Vertice(getVertice_Aresta(getAresta(no1),1),1);
        no1 = no1->prox;

    }


}

void removeListAresta(ListaAr listA)
{
    ListAresta *L = (ListAresta *)listA;
    NodeA *no = L->primeiro;
    NodeA *aux;
    while (no != NULL)
    {
        aux = no;
        no = no->prox;
        free(aux);
        aux = NULL;
    }

    free(L);
}

void Libera_NO_ListAresta(ListaAr listA, NoAr n)
{
    ListAresta *L = (ListAresta *)listA;
    NodeA *no = (NodeA *)n;

    if (no == NULL)
        return;

    if (L->primeiro == no)
    {
        L->primeiro = no->prox;
        if (no->prox != NULL)
            no->prox->ante = NULL;
    }
    else
    {
        no->ante->prox = no->prox;
        if (no->prox != NULL)
            no->prox->ante = no->ante;
    }
    free(no);
    no = NULL;
}
