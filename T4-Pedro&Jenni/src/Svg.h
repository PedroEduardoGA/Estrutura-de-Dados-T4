#ifndef _H_SVG
#define _H_SVG
#include "ArvoreAVL.h"
#include "Grafo.h"

/*Svg.h é o arquivo que contém funções de manipulação dos arquivos svg, inicia/cria o svg, imprime informações e também o fecha*/

FILE* iniciarSvg(char filename[]);                     //cria e inicia o arquivo svg com o nome recebido no parametro e o retorna

void fecharSvg(FILE* svg);                             //fecha o arquivo svg recebido no parametro

void CriaSvg(ArvoreAvl arv, char SvgGeo[],GrafoV grafo);           //cria o svg completo com os dados do geo, inicia o svg, printa os dados no mesmo e fecha logo em seguida

void Imprime_Info_Svg(ArvoreAvl arv, GrafoV grafo, FILE* svg);      //printa o grafo e a as informacoes da arvore no arquivo .svg

void CriaSvgConsulta(ArvoreAvl arv, GrafoV grafo, FILE* svg);  //chama a Imprime_Info_Svg, que imprime as informacoes base do qry, nesse caso, o grafo
#endif
