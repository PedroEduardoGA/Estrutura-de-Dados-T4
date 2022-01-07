#ifndef _H_CIDADE
#define _H_CIDADE
#include "ArvoreAVL.h"

/*Cidade.h tem funcoes para pegarmos as tabelas de espalhamento e a arvoreavl, funcao para criar a cidade e outra para liberar(desalocar) a cidade e os seus
elementos*/

typedef void* Cidade;

Cidade cria_Cidade(char nome[]);   //cria a cidade, criando ja a tabela de espalhamento de Pessoa, Moradores e Locacoes e tambem a arvore avl
ArvoreAvl getArvAvl(Cidade cid);          //retorna a arvore avl
void Libera_Cidade(Cidade cid);           //libera a cidade e os elementos dela
#endif
