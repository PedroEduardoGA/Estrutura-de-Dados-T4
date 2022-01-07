#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaLinhas.h"

typedef struct nodeLinhas{
    double x1,y1,x2,y2,espessura;
    char cor[40],tracejado[40];
    struct nodeLinhas *prox,*ante;
}NodeLinha;

typedef struct listaLinhas{
    NodeLinha *primeiro;
    NodeLinha *ultimo;
}ListLinha;


ListaL createListLine(){
    ListLinha* lista = (ListLinha*) malloc(sizeof(ListLinha));
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    return lista;
}

NoL getFirstLine(ListaL lista){
    ListLinha* L = (ListLinha*) lista;
    return L->primeiro;
}

NoL getLastLine(ListaL lista){
    ListLinha* L = (ListLinha*) lista;
    return L->ultimo;
}

void InsertLine(ListaL pont, double x1,double y1,double x2,double y2,double espessura, char cor[],char tracejado[]){
    ListLinha* L = (ListLinha*)pont;
    NodeLinha* novo = (NodeLinha*) malloc(sizeof(NodeLinha));

    novo->x1 = x1;
    novo->y1 = y1;
    novo->x2 = x2;
    novo->y2 = y2;
    novo->espessura = espessura;
    strcpy(novo->cor,cor);
    strcpy(novo->tracejado,tracejado);

    if (L->primeiro == NULL){
        novo->ante = NULL;
        L->primeiro = novo;
    }else{
        L->ultimo->prox=novo;
        novo->ante = L->ultimo;
    }
    novo->prox = NULL;
    L->ultimo = novo;
}

void PrintSvgLine(NoL elemento, FILE* svg){
    NodeLinha *pont=(NodeLinha*)elemento;

    if(pont == NULL)
        return;

    fprintf(svg, "\t\t\t<line x1=\"%lf\"  y1=\"%lf\"   x2=\"%lf\"  y2=\"%lf\" stroke=\"%s\" stroke-width=\"%lf\"/>\n",pont->x1,pont->y1,pont->x2,pont->y2,pont->cor,pont->espessura);

    PrintSvgLine(pont->prox,svg);
}

void PrintSvgLineTracejado(NoL elemento, FILE* svg){
    NodeLinha *pont=(NodeLinha*)elemento;

    if(pont == NULL)
        return;

    fprintf(svg, "\t\t\t<line x1=\"%lf\"  y1=\"%lf\"   x2=\"%lf\"  y2=\"%lf\" stroke=\"%s\" stroke-width=\"4\" stroke-dasharray=\"%s\"/>\n",pont->x1,pont->y1,pont->x2,pont->y2,pont->cor,pont->tracejado);

    PrintSvgLineTracejado(pont->prox,svg);
}

void PrintSvgRect(NoL elemento, FILE* svg){
    NodeLinha *pont=(NodeLinha*)elemento;

    if(pont == NULL)
        return;

    fprintf(svg, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"#AB37C8\" fill-opacity=\"%lf\" stroke=\"%s\" stroke-width=\"5\"  stroke-dasharray=\"%s\" />\n",pont->x1,pont->y1,pont->x2,pont->y2,pont->espessura,pont->cor,pont->tracejado);


    PrintSvgRect(pont->prox,svg);
}

void removeListLine(ListaL lista){
    ListLinha* L = (ListLinha*) lista;
    NodeLinha* no = L->primeiro;
    NodeLinha* aux;
    while(no != NULL){
        aux = no;
        no = no->prox;
        free(aux);
        aux = NULL;
    }
    free(L);
}
