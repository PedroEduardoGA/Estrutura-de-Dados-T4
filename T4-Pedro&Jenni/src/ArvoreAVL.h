#ifndef _H_ARVOREAVL
#define _H_ARVOREAVL
#include "Quadra.h"
#include "ListaDin.h"

/*ArvoreAVL.h possui todas as funcpes de manipulacao da arvore avl, inserir quadras, verificar altura e fator de balanceamento de cada no da arvore, rotacoes
 para balancear a arvore avl, funcoes de imprimir as quadras guardadas nos nós da arvore, funcoes que desenham a arvore em arquivo .dot, funcoes que procura
 uma quadra de um determinado nó podando se tivermos uma regiao determinada ou procurando apenas pelo cep se tivermos somente essa informacao, e por fim,
 temos funcoes que removem nós da arvore e funcoes que liberam(desalocam) os nós e as arvores*/

typedef void* NOAVL;
typedef void* ArvoreAvl;

ArvoreAvl cria_ArvAVL();                                        //cria a arvore avl
NOAVL getFirstAvl(ArvoreAvl arv);                               //retorna a raiz da arvore avl
int getAltura(NOAVL A);                                         //retorna a altura de um nó
int getFb(NOAVL A);                                             //retorna o fator de balanceamento
int altura_NO(NOAVL A);                                         //verifica se é folha e retorna a altura do no
int fatorBalanceamento_NO(NOAVL A);                             //calcula o fator de balanceamento
int maior(int x, int y);                                        //verifica qual das alturas (x ou y) é maior
void RotacaoLL(ArvoreAvl arv, NOAVL no);                        //Rotacao Left-Left
void RotacaoRR(ArvoreAvl arv, NOAVL no);                        //Rotacao Right-Right
void RotacaoLR(ArvoreAvl arv, NOAVL no);                        //Rotacao Left-Right
void RotacaoRL(ArvoreAvl arv, NOAVL no);                        //Rotacao Right-Left
NOAVL insere_ArvAVL(ArvoreAvl arv, NOAVL NoR, Quadra Quad);     //Insere a quadra do parâmetro na arvore avl
void PrintSvgArv(NOAVL NoR, FILE* svg);                         //Printa as quadras no arquivo svg
void IniciaDot(NOAVL NoR, FILE* dot);                           //Inicia o arquivo .dot que irá desenhar a arvore
void ImprimeArvore(NOAVL NoR, FILE* dot);                       //Imprime a arvore avl no arquivo .dot
char* AnalizaCEP_NULL(No elemento);                             //analiza se o cep é nulo, para não causar falha de segmentação
NOAVL procuraMenor(NOAVL no);                                   //procura o nó que tem o menor x dos nós que estão a esquerda do nó do parametro
Quadra procuraQuadra(NOAVL no, char cep[]);                     //procura a quadra pelo cep caso a unica informação seja o cep
void ProcuraQuadPodando(NOAVL no,Lista L, double x, double y, double w, double h);      //procura a quadra podando, quando tem uma regiao definida por x,y,w,h
NOAVL Troca_No(ArvoreAvl arv,NOAVL antigo,NOAVL novo);                                  //troca o nó que será removido pelo menor nó da subarvore direita, para ser removido logo depois da troca
int remove_ArvAVL(ArvoreAvl arv, NOAVL NoR, Quadra Quad);                               //remove um nó da arvore avl
void libera_NO(NOAVL A);                                                                //libera os nós da arvore avl no fim da execucao do programa
void libera_ArvAVL(ArvoreAvl arv);                                                      //libera a arvore avl no fim da execucao do programa

#endif
