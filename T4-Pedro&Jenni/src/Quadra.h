#ifndef _H_QUADRA
#define _H_QUADRA

/*Quadras.h possui funcoes para criar um no quadra com determinadas informacoes, funcoes que retornam informacoes especificas e uma funcao que ira realizar
a liberacao do no quadra*/


typedef void* Quadra;

Quadra Cria_Quadra(double x, double y, double w, double h, char cep[40], char espessura[], char corPreen[], char corBorda[]);  //cria um novo no quadra que guardará as informacoes de uma quadra com os dados do parametro
char *getCFILL(Quadra Quad);        //retorna a cor de preenchimento da quadra no nó do parametro
char *getCSTRK(Quadra Quad);        //retorna a cor de borda da quadra no nó do parametro
char *getSW(Quadra Quad);           //retorna a espessura da borda da quadra no nó do parametro
char* getCEP(Quadra Quad);          //retorna o cep da quadra no nó do parametro
double getXQuad(Quadra Quad);       //retorna o x da quadra no nó do parametro
double getYQuad(Quadra Quad);       //retorna o y da quadra no nó do parametro
double getWQuad(Quadra Quad);       //retorna o w da quadra no nó do parametro
double getHQuad(Quadra Quad);       //retorna o h da quadra no nó do parametro
void libera_QUADRA(Quadra Quad);    //libera o no quadra recebido no parametro

#endif
