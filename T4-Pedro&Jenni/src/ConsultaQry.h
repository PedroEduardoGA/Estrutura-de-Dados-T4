#ifndef _H_CONSULTAQRY
#define _H_CONSULTAQRY
#include "ArvoreAVL.h"
#include "Cidade.h"
#include "ListaLinhas.h"
#include "ListaArestas.h"

/*ConsultaQry.h contém todas as funções que irão realizar as análises aprofundadas das consultas do arquivo qry, são essas as funções que o arquivo Leitura.h
chama para auxiliar a geração dos arquivos txt e svg de saída, fazendo consultas, removendo e criando novos elementos*/

typedef void* R;

R o_consulta(Cidade city, FILE* svg, char cep[40], char face[40], int num);     //cria e retorna um registrador contendo as coordenadas do endereço passado como parametro, printa uma linha e os dados do endereco no arquivo .svg de saida

void LocalizacaoEndereco(R register_O, Quadra quad, char face[40], int num);    //insere as coordenadas no registrador de acordo com os parametros informados

void catac(Cidade city, GrafoV grafo, FILE* txt,FILE* svg, double x,double y,double w,double h);    //remove os vertices e suas arestas que estiverem dentro da regiao informada, informas as remocoes no arquivo .txt e desenha um retangulo representando a regiao no .svg

void rv(GrafoV grafo, double x, double y, double w, double h, FILE *txt, FILE *svg,double f,ListaL listaLinha,ListaL listaLinhaRaizes, ListaL listaRetangulos); //gera a arvore geradora minima de acordo com a regiao passada

void cx(GrafoV grafo, FILE* txt, FILE* svg,double limiar,ListaL listaLinha); //realiza a consulta cx atribuindo as regioes dos vertices de acordo com suas conexoes

void p_consulta(ListaL listaLinhas,ListaL listaLinhasTrac,Cidade city, GrafoV grafo,R registro_O, FILE* txt, FILE* svg, char cep[40], char face[40], int num, char cmc[40], char cmr[40]);

void removeRegistrador(R register_O);   //libera a memoria alocada para o registrador r, caso nao tenha sido alocada memoria, só retorna

char* CorRegiao(int region);//retorna uma cor de acordo com o inteiro recebido

#endif
