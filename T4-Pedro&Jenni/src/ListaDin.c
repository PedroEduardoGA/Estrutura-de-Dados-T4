#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDin.h"
#include "Quadra.h"

typedef struct nodeL{
    Quadra quadra;
    struct nodeL *ante,*prox;
}Node;

typedef struct lista{
    Node *primeiro;
    Node *ultimo;
}ListDin;

Lista createListDin(){
    ListDin* lista = (ListDin*) malloc(sizeof(ListDin));
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    return lista;
}
No getPreviousDin(No elemento){
    Node* no = (Node*) elemento;
    if(no != NULL)
        return no->ante;
    else
        return NULL;
}

No getNextDin(No elemento){
    Node* L = (Node*)elemento;
    if(L != NULL)
        return L->prox;
    else
        return NULL;
}

No getFirstDin(Lista lista){
    ListDin* L = (ListDin*) lista;
    return L->primeiro;
}

No getLastDin(Lista lista){
    ListDin* L = (ListDin*) lista;
    return L->ultimo;
}

Quadra getQuadraList(No elemento){
    Node *pont=(Node*)elemento;
    if(pont == NULL)
        return NULL;
    return pont->quadra;
}

void proximoNoList(Lista pont){
    ListDin* L=(ListDin*)pont;
    Node* no = L->primeiro;

    L->primeiro = no->prox;
    if(L->primeiro != NULL)
        no->prox->ante = NULL;
    free(no);
}

double ProcuraMaxList(No no, double maxAtual,double maxDir,double maxEsq){
    Node* NoL = (Node*) no;

    if(NoL == NULL){
        if(maxDir > maxAtual && maxDir > maxEsq)
            return maxDir;
        if(maxEsq > maxAtual && maxEsq > maxDir)
            return maxEsq;

        return maxAtual;
    }

    if(getXQuad(NoL->quadra) + getWQuad(NoL->quadra) > maxAtual){
        if(maxDir > getXQuad(NoL->quadra) + getWQuad(NoL->quadra) && maxDir > maxEsq)
            return maxDir;
        if(maxEsq > getXQuad(NoL->quadra) + getWQuad(NoL->quadra) && maxEsq > maxDir)
            return maxEsq;

        return getXQuad(NoL->quadra) + getWQuad(NoL->quadra);
    }

    return ProcuraMaxList(NoL->prox,maxAtual,maxDir,maxEsq);
}

No ProcuraQuadCEPList(No no,char cep[]){
    Node* NoL = (Node*) no;

    if(NoL == NULL)
        return NULL;

    if((strcmp(getCEP(NoL->quadra),cep)) == 0)
        return NoL;

    return ProcuraQuadCEPList(NoL->prox,cep);
}

void ProcuraQuadPodandoList(No no, Lista L, double x, double y, double w, double h){
    Node* NoL = (Node*) no;

    if(NoL == NULL)
        return;

    if(getXQuad(NoL->quadra) >= x  &&  getYQuad(NoL->quadra) >= y  &&  getXQuad(NoL->quadra) + getWQuad(NoL->quadra) <= x+w  &&  getYQuad(NoL->quadra) + getHQuad(NoL->quadra) <= y+h)
        InsertDin(L, NoL->quadra);

    ProcuraQuadPodandoList(NoL->prox,L,x,y,w,h);
}

void InsertDin(Lista pont, Quadra quad){
    ListDin* L=(ListDin*)pont;
    Node* novo = (Node*) malloc(sizeof(Node));

    novo->quadra = quad;

    if (L->primeiro == NULL){
        novo->ante=NULL;
        L->primeiro=novo;
    }else{
        L->ultimo->prox=novo;
        novo->ante=L->ultimo;
    }
    novo->prox = NULL;
    L->ultimo = novo;
}
void PrintSvgLista(No elemento, FILE* svg){
    Node *pont=(Node*)elemento;
    if(pont == NULL)
        return;

    fprintf(svg, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\"/>\n",getXQuad(pont->quadra),getYQuad(pont->quadra),getWQuad(pont->quadra),getHQuad(pont->quadra),getCFILL(pont->quadra),getCSTRK(pont->quadra),getSW(pont->quadra));
    fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\" style=\"stroke:#000000; fill: #000000; font-family:Arial; font-size: 15px;\" >%s</text>\n",getXQuad(pont->quadra),getYQuad(pont->quadra)+15,getCEP(pont->quadra));
    PrintSvgLista(pont->prox,svg);
}

void removeListDinConsultas(Lista lista){
    ListDin* L = (ListDin*) lista;
    Node* no = L->primeiro;
    Node* aux;
    while(no != NULL){
        aux = no;
        no = no->prox;
        free(aux);
        aux = NULL;
    }
    free(L);
}

void removeListDin(Lista lista){
    ListDin* L = (ListDin*) lista;
    Node* no = L->primeiro;
    Node* aux;
    while(no != NULL){
        libera_QUADRA(no->quadra);
        aux = no;
        no = no->prox;
        free(aux);
        aux = NULL;
    }
    free(L);
}

void Libera_NO_List(Lista lista, No n){
    ListDin* L = (ListDin*) lista;
    Node* no = (Node*) n;

    if(no == NULL)
        return;

    if(L->primeiro == no){
        L->primeiro = no->prox;
        if(no->prox != NULL)
            no->prox->ante = NULL;
    }else{
        no->ante->prox = no->prox;
        if(no->prox != NULL)
            no->prox->ante = no->ante;
    }
    libera_QUADRA(no->quadra);
    free(no);
    no = NULL;
}
