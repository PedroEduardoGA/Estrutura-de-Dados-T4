#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Cidade.h"
#include "ArvoreAVL.h"
#include "Quadra.h"
#include "Svg.h"
#include "ConsultaQry.h"

typedef struct registrador
{
    double x, y;
} r;

R o_consulta(Cidade city, FILE *svg, char cep[40], char face[40], int num)
{
    r *register_O = (r *)malloc(sizeof(r));

    Quadra quad = procuraQuadra(getFirstAvl(getArvAvl(city)), cep);
    if(quad == NULL){
        removeRegistrador(register_O);
        return NULL;
    }

    LocalizacaoEndereco(register_O, quad, face, num);

    fprintf(svg, "\t\t\t<line x1=\"%lf\"  y1=\"%lf\"   x2=\"%lf\"  y2=\"%lf\" stroke=\"black\"/>\n", register_O->x, register_O->y, register_O->x, 0.0);
    fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\" style=\"stroke:#000000; stroke-width: 0.5; fill: black; font-family:Arial; font-weight:bold;\" >Cep: %s  -  Face: %s  -  Num: %d</text>\n", register_O->x, 0.0, cep, face, num);

    return register_O;
}

void LocalizacaoEndereco(R register_O, Quadra quad, char face[40], int num)
{
    r *Registrador = (r *)register_O;

    if (strcmp(face, "N") == 0)
    {
        Registrador->x = getXQuad(quad) + num;
        Registrador->y = getYQuad(quad) + getHQuad(quad);
    }
    else if (strcmp(face, "O") == 0)
    {
        Registrador->x = getXQuad(quad) + getWQuad(quad);
        Registrador->y = getYQuad(quad) + num;
    }
    else if (strcmp(face, "S") == 0)
    {
        Registrador->x = getXQuad(quad) + num;
        Registrador->y = getYQuad(quad);
    }
    else if (strcmp(face, "L") == 0)
    {
        Registrador->x = getXQuad(quad);
        Registrador->y = getYQuad(quad) + num;
    }
}

void catac(Cidade city, GrafoV grafo, FILE *txt, FILE *svg, double x, double y, double w, double h)
{
    fprintf(txt, "\n\n\n\t\t\t\t\t\t-------- catac --------\n");

    int i = 0;
    double X, Y;

    Lista listaQuadras = createListDin();

    ProcuraQuadPodando(getFirstAvl(getArvAvl(city)), listaQuadras, x, y, w, h);
    No noListQ = getFirstDin(listaQuadras);
    No noListQ1;
    Quadra quad;

    while (noListQ != NULL)
    {
        quad = getQuadraList(noListQ);
        if(quad == NULL)
            break;

        fprintf(txt, "\n\nQuadra Removida  -  CEP: %s  X: %lf  Y: %lf  W: %lf  H: %lf", getCEP(quad), getXQuad(quad), getYQuad(quad), getWQuad(quad), getHQuad(quad));

        noListQ1 = getNextDin(noListQ);
        remove_ArvAVL(getArvAvl(city), getFirstAvl(getArvAvl(city)), getQuadraList(noListQ));
        noListQ = noListQ1;
    }

    while (i < getTamanho_Grafo(grafo))
    {
        X = getX_Vertice(getVertice_Grafo(grafo, i));
        Y = getY_Vertice(getVertice_Grafo(grafo, i));

        if (X >= x && Y >= y && X <= x + w && Y <= y + h)
        {
            fprintf(txt, "\n\nVertice Removido  -  ID: %s  X: %lf  Y: %lf", getID_Vertice(getVertice_Grafo(grafo, i)), X, Y);
            removeVertice(grafo, 0, getVertice_Grafo(grafo, i), txt);
        }

        i++;
    }

    removeListDinConsultas(listaQuadras);
}

void rv(GrafoV grafo, double x, double y, double w, double h, FILE *txt, FILE *svg,double f,ListaL listaLinha,ListaL listaLinhaRaizes,ListaL listaRetangulos)
{
     fprintf(txt, "\n\n\n\t\t\t\t\t\t-------- rv --------\n");
    ListaAr listArestas = createListAresta();

    int i = 0, j = 0;
    double X, Y;
    Vertice *vert;
    Aresta *aresta;

    while (i < getTamanho_Grafo(grafo))
    {
        vert = getVertice_Grafo(grafo, i);

        X = getX_Vertice(vert);
        Y = getY_Vertice(vert);

        if (X >= x && Y >= y && X <= x + w && Y <= y + h)
        { //se verdade vertice esta dentro da regiao
            aresta = getListaArestas(vert);

            while(aresta != NULL){
                X = getX_Vertice(getVertice_Aresta(aresta,0));
                Y = getY_Vertice(getVertice_Aresta(aresta,0));

                if (X >= x && Y >= y && X <= x + w && Y <= y + h){//v2 tambem esta dentro da regiao
                    InsertAresta(listArestas,aresta,NULL,getFirstAresta(listArestas),0);//insere a aresta na lista

                    if(getVisitado_Vertice(getVertice_Aresta(aresta,0)) == 0){
                        j++;
                        setVisitado_Vertice(getVertice_Aresta(aresta,0),1);

                    }
                    if(getVisitado_Vertice(getVertice_Aresta(aresta,1)) == 0){
                        j++;
                        setVisitado_Vertice(getVertice_Aresta(aresta,1),1);
                    }

                }
                aresta = getNextAresta(aresta);
            }
        }

        i++;
    }
    ZerarVisitado(getFirstAresta(listArestas));
    NoAr NoAresta = getFirstAresta(listArestas);
    NoAr aux;
    i = 1;

    while(i <= j-1){
        aux = NoAresta;
        if(aux == NULL)
            break;

        NoAresta = getNextArestaList(NoAresta);

        if(getVisitado_Vertice(getVertice_Aresta(getAresta(aux),1)) == 0){
            setVisitado_Vertice(getVertice_Aresta(getAresta(aux),1),1);

        }else{
            if(getVisitado_Vertice(getVertice_Aresta(getAresta(aux),0)) == 1){
                if((contaArestasSaida(getFirstAresta(listArestas),getVertice_Aresta(getAresta(aux),1),0) == 2 && contaArestasEntrada(getFirstAresta(listArestas),getVertice_Aresta(getAresta(aux),1),0) == 1)){
                    if(verificaArestasEntrada_Saida(getFirstAresta(listArestas),getVertice_Aresta(getAresta(aux),1),getY_Vertice(getVertice_Aresta(getAresta(aux),0))) == 0){
                        Libera_NO_ListAresta(listArestas,aux);
                        i++;
                    }
                }else if(contaArestasEntrada(getFirstAresta(listArestas),getVertice_Aresta(getAresta(aux),1),0) != 0){
                    Libera_NO_ListAresta(listArestas,aux);
                    i++;
                }
            }
            else{
                setVisitado_Vertice(getVertice_Aresta(getAresta(aux),0),1);
            }

        }

    }

    buscaEmLargura(listArestas,svg,txt,f,listaLinha,listaLinhaRaizes);
    InsertLine(listaRetangulos,x,y,w,h,0,"yellow","7,4");
    removeListAresta(listArestas);
}

void cx(GrafoV grafo, FILE* txt, FILE* svg,double limiar,ListaL listaLinha){//novidade
    fprintf(txt, "\n\n\n\t\t\t\t\t\t-------- cx --------\n");
    double vm;
    int i=0,regiao=1;//regiao novidade - FuncaoCx
    Vertice *vert;
    Aresta *aresta;

    zeraArestasVertices(grafo);//FuncaoCx - Zera o inteiro que representa a quantidade de arestas que chegam e saem de todos vertices
    atualizaArestasVertices(grafo);//FuncaoCx - Atualiza a quantidade de arestas que saem e chegam nos vertices

    while (i < getTamanho_Grafo(grafo))
    {
        vert = getVertice_Grafo(grafo, i);
        if(getQtdChegam(vert) == 0)//se o vertice n tem aresta de chegada ele esta em uma regiao desconexa, novidade - FuncaoCx
            setRegiao(vert,-1);

        if(getRegiao(vert)==0)//FuncaoCx
            setRegiao(vert,regiao);

        aresta = getListaArestas(vert);
        while(aresta != NULL){

            vm = getVm_Aresta(aresta);
            if(vm < limiar)
            {
                setArestachegam(getVertice_Aresta(aresta,0),0);//o v2 passa a ser desconexo, novidade - FuncaoCx
                setRegiao(getVertice_Aresta(aresta,0),-1);//regiao do v2 passa a ser -1 pois é desconexa, novidade - FuncaoCx
                setRegiao(getVertice_Aresta(aresta,1),-1);//regiao do v1 passa a ser -1 pois é desconexa, novidade - FuncaoCx
                if(getQtdChegam(vert) != 0){//FuncaoCx
                    regiao++;
                    setRegiao(getVertice_Aresta(aresta,0),regiao);//vertice 2 da aresta recebe outra regiao
                }

                InsertLine(listaLinha,getX_Vertice(getVertice_Aresta(aresta,1)),getY_Vertice(getVertice_Aresta(aresta,1)),getX_Vertice(getVertice_Aresta(aresta,0)),getY_Vertice(getVertice_Aresta(aresta,0)),7,"red","");
            }else{//FuncaoCx
                if(getRegiao(getVertice_Aresta(aresta,1)) != -1)//FuncaoCx
                    setRegiao(getVertice_Aresta(aresta,1),getRegiao(getVertice_Aresta(aresta,1)));//FuncaoCx
                else
                    setRegiao(getVertice_Aresta(aresta,1),regiao);//FuncaoCx
            }

            aresta = getNextAresta(aresta);
        }

        i++;

        fprintf(txt, "\nVertice X: %lf Y: %lf regiao: %d",getX_Vertice(vert),getY_Vertice(vert),getRegiao(vert));
    }
}

void p_consulta(ListaL listaLinhas,ListaL listaLinhasTrac,Cidade city, GrafoV grafo,R registro_O, FILE* txt, FILE* svg, char cep[40], char face[40], int num, char cmc[40], char cmr[40]){
    fprintf(txt, "\n\n\n\t\t\t\t\t\t-------- p? --------\n");
    r *register_O = (r *)registro_O;
    r *register_P = (r *)malloc(sizeof(r));
    Quadra quad = procuraQuadra(getFirstAvl(getArvAvl(city)), cep);

    if(quad == NULL){
        fprintf(txt, "\n\nQuadra Inexistente!\n");
        return;
    }else{
        LocalizacaoEndereco(register_P, quad, face, num);//atribui as coordenadas do endereco de destino
    }

    double xO,yO,xP,yP;
    xO=register_O->x;
    yO=register_O->y;
    xP=register_P->x;
    yP=register_P->y;

    fprintf(svg, "\t\t\t<line x1=\"%lf\"  y1=\"%lf\"   x2=\"%lf\"  y2=\"%lf\" stroke=\"black\"/>\n", register_P->x, register_P->y, register_P->x, 0.0);
    fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\" style=\"stroke:#000000; stroke-width: 0.5; fill: black; font-family:Arial; font-weight:bold;\" >Cep: %s  -  Face: %s  -  Num: %d</text>\n", register_P->x, 0.0, cep, face, num);


    int iInicial=getI_VerticeProx(grafo,xO,yO);//pega o i do vertice mais proximo ao ponto de origem
    int iFinal=getI_VerticeProx(grafo,xP,yP);//pega o i do vertice mais proximo ao ponto de origem

    dijkstra(listaLinhas,listaLinhasTrac,grafo, iInicial, iFinal,svg,txt, cmc, cmr, 1,xO,yO,xP,yP);//caminho mais curto
    dijkstra(listaLinhas,listaLinhasTrac,grafo,iInicial, iFinal,svg,txt, cmc, cmr, 2,xO,yO,xP,yP);//caminho mais rapido
}

ListaAr criaArvoreGeradoraMinima(GrafoV grafo, int cmc){
    ListaAr listArestas = createListAresta();

    int i = 0, j = 0;
    Vertice *vert;
    Aresta *aresta;

    while (i < getTamanho_Grafo(grafo))
    {
        vert = getVertice_Grafo(grafo, i);
        aresta = getListaArestas(vert);

        while(aresta != NULL){
            InsertAresta(listArestas,aresta,NULL,getFirstAresta(listArestas),cmc);//insere a aresta na lista

            if(getVisitado_Vertice(getVertice_Aresta(aresta,0)) == 0){
                j++;
                setVisitado_Vertice(getVertice_Aresta(aresta,0),1);

            }
            if(getVisitado_Vertice(getVertice_Aresta(aresta,1)) == 0){
                j++;
                setVisitado_Vertice(getVertice_Aresta(aresta,1),1);
            }
            aresta = getNextAresta(aresta);
        }
        i++;
    }

    ZerarVisitado(getFirstAresta(listArestas));
    NoAr NoAresta = getFirstAresta(listArestas);
    NoAr aux;
    i = 1;

    while(i <= j-1){
        aux = NoAresta;

        if(aux == NULL)
            break;

        NoAresta = getNextArestaList(NoAresta);

        if(getVisitado_Vertice(getVertice_Aresta(getAresta(aux),1)) == 0){
            setVisitado_Vertice(getVertice_Aresta(getAresta(aux),1),1);

        }else{
            if(getVisitado_Vertice(getVertice_Aresta(getAresta(aux),0)) == 1){
                if((contaArestasSaida(getFirstAresta(listArestas),getVertice_Aresta(getAresta(aux),1),0) == 2 && contaArestasEntrada(getFirstAresta(listArestas),getVertice_Aresta(getAresta(aux),1),0) == 1)){
                    if(verificaArestasEntrada_Saida(getFirstAresta(listArestas),getVertice_Aresta(getAresta(aux),1),getY_Vertice(getVertice_Aresta(getAresta(aux),0))) == 0){
                        Libera_NO_ListAresta(listArestas,aux);
                        i++;
                    }
                }else if(contaArestasEntrada(getFirstAresta(listArestas),getVertice_Aresta(getAresta(aux),1),0) != 0){
                    Libera_NO_ListAresta(listArestas,aux);
                    i++;
                }
            }
            else{
                setVisitado_Vertice(getVertice_Aresta(getAresta(aux),0),1);
            }

        }

    }

    return listArestas;
}

void removeRegistrador(R register_O)
{
    r *Registrador = (r *)register_O;

    if (Registrador == NULL)
        return;

    free(Registrador);
}

char* CorRegiao(int region)//FuncaoCx
{
    if(region){//vai atribuir uma cor pra cada inteiro recebido
        if(region >= 1 && region <= 3)
            return "green";

        if(region >= 4 && region <= 6)
            return "purple";

        if(region >= 7 && region <= 9)
            return "orange";

        if(region >= 10 && region <= 12)
            return "blue";

        if(region >= 13 && region <= 14)
            return "yellow";

        if(region >= 15 && region <= 17)
            return "brown";

        if(region >= 18 && region <= 19)
            return "magenta";

        if(region >= 20 && region <= 22)
            return "olivedrab";

        if(region >= 23 && region <= 24)
            return "orchid";

        if(region >= 25 && region <= 28)
            return "turquoise";

        if(region >= 29 && region <= 34)
            return "burlywood";

        if(region >= 35 && region <= 38)
            return "darkseagreen";

        if(region >= 39 && region <= 42)
            return "tan";

        if(region >= 43 && region <= 46)
            return "mediumslateblue";

        if(region >= 47 && region <= 50)
            return "wheat";

        }
    return "black";

}
