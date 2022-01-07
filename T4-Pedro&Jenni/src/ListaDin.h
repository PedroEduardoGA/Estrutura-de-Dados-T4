#ifndef _H_LISTADIN
#define _H_LISTADIN
#include "Quadra.h"

/*ListaDin.h é um arquivo que contém todas funções necessárias para a manipulação das listas dinamicas duplamente encadeadas, utilizadas para armazenar as
quadras que possuem mesma coordenada X que o nó da arvore avl em que essa lista estará ligada, portanto, ela vai fazer a ligacao dessas quadras com o X em
comum, funcoes para procurar o maior X das quadras que estão armazenadas nos nós da lista dinamica, realizar procura de uma quadra pelo cep e por uma regiao,
inserir novas quadras, printar informacoes no arquivo svg, remover uma determinada quadra de um no da lista, e por fim, remove a lista*/

typedef void* Lista;
typedef void* No;

Lista createListDin();                                  //cria a lista Dinâmica duplamente encadeada e a retorna

No getPreviousDin(No elemento);                         //retorna o nó anterior ao nó recebido nos parametros

No getNextDin(No elemento);                             //retorna o proximo nó do nó "elemento" recebido no parametro

No getFirstDin(Lista lista);                            //retorna o primeiro nó da lista

No getLastDin(Lista lista);                             //retorna o ultimo nó da lista

Quadra getQuadraList(No elemento);                      //retorna a quadra armazenada no nó "elemento" do parametro

void proximoNoList(Lista pont);                         //libera o primeiro no da lista

double ProcuraMaxList(No no, double maxAtual,double maxDir,double maxEsq);              //procura a quadra de um no que possue o maior X da lista

No ProcuraQuadCEPList(No no,char cep[]);                //procura uma quadra pelo cep

void ProcuraQuadPodandoList(No no, Lista L, double x, double y, double w, double h);   //funcao que continua a procura nas listas dos nós da arvore avl de uma quadra em uma regiao x,y,w,h

void InsertDin(Lista pont, Quadra quad);                //Insere um novo nó no(quadra) final da lista dinamica com os valores recebidos no parâmetro

void PrintSvgLista(No elemento, FILE* svg);             //printa no arquivo svg a quadra do nó do parametro

void removeListDinConsultas(Lista lista);               //remove(libera) a lista dinamica auxiliar, usada em ConsultaQry.C para guardar as Quadras que foram encontradas em busca com poda

void removeListDin(Lista lista);                        //remove(libera) a lista dinamica de quadras

void Libera_NO_List(Lista lista, No n);                 //libera um no(quadra) da lista dinamica de quadras

#endif
