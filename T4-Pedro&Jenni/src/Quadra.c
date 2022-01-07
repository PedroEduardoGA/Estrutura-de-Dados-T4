#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Quadra.h"

typedef struct Q{
    double x,y,w,h;
    char cep[40],corBorda[40],corPreen[40],espessura[10];
}quadra;

Quadra Cria_Quadra(double x, double y, double w, double h, char cep[], char espessura[], char corPreen[], char corBorda[]){
    quadra* Q = (quadra*) malloc(sizeof(quadra));

    Q->x = x;
    Q->y = y;
    Q->w = w;
    Q->h = h;
    strcpy(Q->cep,cep);
    strcpy(Q->espessura,espessura);
    strcpy(Q->corPreen,corPreen);
    strcpy(Q->corBorda,corBorda);

    return Q;
}

char *getCFILL(Quadra Quad){
    quadra* Q = (quadra*)Quad;
    return Q->corPreen;
}

char *getCSTRK(Quadra Quad){
    quadra* Q = (quadra*)Quad;
    return Q->corBorda;
}

char *getSW(Quadra Quad){
    quadra* Q = (quadra*)Quad;
    return Q->espessura;
}

char* getCEP(Quadra Quad){
    quadra* Q = (quadra*) Quad;
    return Q->cep;
}

double getXQuad(Quadra Quad){
    quadra* Q = (quadra*) Quad;
    return Q->x;
}

double getYQuad(Quadra Quad){
    quadra* Q = (quadra*) Quad;
    return Q->y;
}

double getWQuad(Quadra Quad){
    quadra* Q = (quadra*) Quad;
    return Q->w;
}

double getHQuad(Quadra Quad){
    quadra* Q = (quadra*) Quad;
    return Q->h;
}

void libera_QUADRA(Quadra Quad){
    quadra* Q = (quadra*) Quad;
    free(Q);
    Q = NULL;
}
