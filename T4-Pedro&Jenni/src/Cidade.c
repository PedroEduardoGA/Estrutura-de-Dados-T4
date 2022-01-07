#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cidade.h"
#include "ArvoreAVL.h"

typedef struct cid{
    ArvoreAvl* ArvAvl;
    char nome[20];
}cidade;

Cidade cria_Cidade(char nome[]){
    cidade* City = (cidade*) malloc(sizeof(cidade));

    strcpy(City->nome,nome);
    City->ArvAvl = cria_ArvAVL();
    return City;
}

ArvoreAvl getArvAvl(Cidade cid){
    cidade* City = (cidade*) cid;
    return City->ArvAvl;
}

void Libera_Cidade(Cidade cid){
    cidade* City = (cidade*) cid;
    libera_ArvAVL(City->ArvAvl);
    free(City);
}
