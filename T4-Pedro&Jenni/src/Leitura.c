#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Leitura.h"
#include "Quadra.h"
#include "Grafo.h"
#include "Svg.h"
#include "ConsultaQry.h"
#include "ListaLinhas.h"

void Leitura_Geo(char EntryPathGeo[], char SvgGeo[],char EntryPathQry[],char qryNoExtention[],char EntryPathV[]) {
    int nx;
    char tipo[5], sw[10], cfill[40], cstrk[40], cep[40];
    double x=0, y=0, w=0, h=0;

    FILE* geo = fopen(EntryPathGeo, "r");
    if (geo == NULL) {
        printf("Um erro ocorreu ao abrir o arquivo GEO.\n");
        exit(1);
    }
    Cidade city = cria_Cidade("Bitnópolis");
    Quadra PontQuad;

     while(fscanf(geo,"%s", tipo) != EOF){
        if (strcmp(tipo,"nx") == 0){
            fscanf(geo,"%d\n",&nx);

        }else if(strcmp(tipo,"cq") == 0){
            fscanf(geo,"%s %s %s",sw,cfill,cstrk);

        }else if(strcmp(tipo,"q") == 0){
            fscanf(geo,"%s %lf %lf %lf %lf",cep,&x,&y,&w,&h);

            if(cfill[0]=='\0'){
                strcpy(cfill,getCFILL(PontQuad));
            }
            if(cstrk[0]=='\0'){
                strcpy(cstrk,getCSTRK(PontQuad));
            }
            if(sw[0]=='\0'){
                strcpy(sw,getSW(PontQuad));
            }

            PontQuad = Cria_Quadra(x,y,w,h,cep,sw,cfill,cstrk);
            insere_ArvAVL(getArvAvl(city),getFirstAvl(getArvAvl(city)),PontQuad);
            cfill[0]='\0';   cstrk[0]='\0';   sw[0]='\0';
        }
    }

    fclose(geo);

    if (EntryPathV)
        Leitura_Via(city, EntryPathV,EntryPathQry, qryNoExtention, SvgGeo);
    else{
        printf("\n -------- Excluindo Cidade -------- \n\n");
        Libera_Cidade(city);
    }
}

void Leitura_Via(Cidade city, char EntryPathV[], char EntryPathQry[], char qryNoExtention[], char SvgGeo[]) {
    char tipo[5], id[40], ldir[40], lesq[40], nome[40], i[40], j[40];
    double x,y,cmp,vm;
    int nv,cont;
    Quadra PontQuad1,PontQuad2;
    Vertice V1,V2;

    FILE* via = fopen(EntryPathV, "r");
    if (via == NULL) {
        printf("Um erro ocorreu ao abrir o arquivo VIA.\n");
        exit(1);
    }

    fscanf(via,"%d\n",&nv);
    GrafoV grafo = criaGrafo(nv);

    while(fscanf(via,"%s", tipo) != EOF){
        if (strcmp(tipo,"v") == 0){
            fscanf(via,"%s %lf %lf",id,&x,&y);
            insereVertice(grafo,id,x,y);

        }else if(strcmp(tipo,"e") == 0){
            fscanf(via,"%s %s %s %s %lf %lf %s",i,j,ldir,lesq,&cmp,&vm,nome);
            PontQuad1 = procuraQuadra(getFirstAvl(getArvAvl(city)),ldir);
            PontQuad2 = procuraQuadra(getFirstAvl(getArvAvl(city)),lesq);
            V1 = procuraVertice(grafo,i,0,&cont);
            V2 = procuraVertice(grafo,j,0,&cont);

            insereAresta(V1,V2,PontQuad1,PontQuad2,vm,cmp,nome,getIndiceVertice(grafo,j));
        }
    }

    fclose(via);

    CriaSvg(getArvAvl(city),SvgGeo,grafo);

    if (EntryPathQry)
        Leitura_Qry(city, EntryPathQry, qryNoExtention, grafo);
    else{
        printf("\n -------- Excluindo Cidade -------- \n\n");
        Libera_Cidade(city);

        printf("\n -------- Excluindo Grafo -------- \n\n");
        removeGrafo(grafo);
    }
}

void Leitura_Qry(Cidade city, char EntryPathQry[], char qryNoExtention[], GrafoV grafo){
    char tipo[5], cep[40], face[5], cmc[40], cmr[40];
    int num;
    double x, y, w, h, limiar, f;

    char *pathSvg = (char*) malloc((strlen(qryNoExtention) + 5) * sizeof(char));
    sprintf(pathSvg, "%s.svg", qryNoExtention);
    char *pathTxt = (char*) malloc((strlen(qryNoExtention) + 5) * sizeof(char));
    sprintf(pathTxt, "%s.txt", qryNoExtention);

    FILE* qry = fopen(EntryPathQry, "r");
    FILE* txt = fopen(pathTxt, "w");     fprintf(txt,"Jennifer do Prado da Silva e Pedro Eduardo Garbossa de Almeida\n");
    FILE* svg = iniciarSvg(pathSvg);

    if (qry == NULL){
        printf("Ocorreu um erro ao abrir o arquivo QRY.\n"); exit(1);
    }
    if (txt == NULL){
        printf("Ocorreu um erro ao abrir o arquivo TXT.\n"); exit(1);
    }

    R register_O = NULL;
    ListaL listaRetangulos = createListLine();
    ListaL listaLinha = createListLine();
    ListaL listaLinhaTrac = createListLine();
    ListaL listaLinhaRaizes = createListLine();

    while (fscanf(qry, "%s", tipo) != EOF) {

        if (strcmp(tipo, "@o?") == 0) {
            fscanf(qry, "%s %s %d",cep,face,&num);

            register_O = o_consulta(city,svg,cep,face,num);

        }else if (strcmp(tipo, "rv") == 0) {
            fscanf(qry, "%lf %lf %lf %lf %lf",&x,&y,&w,&h,&f);
            rv(grafo,x,y,w,h,txt,svg,f,listaLinha,listaLinhaRaizes,listaRetangulos);

        }else if (strcmp(tipo, "cx") == 0) {
            fscanf(qry, "%lf",&limiar);
            cx(grafo,txt,svg,limiar,listaLinha);

        }else if (strcmp(tipo, "p?") == 0) {
            fscanf(qry, "%s %s %d %s %s",cep,face,&num,cmc,cmr);
            p_consulta(listaLinha,listaLinhaTrac,city,grafo,register_O,txt,svg,cep,face,num,cmc,cmr);

        }else if (strcmp(tipo, "catac") == 0) {
            fscanf(qry, "%lf %lf %lf %lf",&x,&y,&w,&h);
            catac(city,grafo,txt,svg,x,y,w,h);
            InsertLine(listaRetangulos,x,y,w,h,0.5,"#AA0044","0,0");
        }
    }

    CriaSvgConsulta(getArvAvl(city),grafo,svg);
    PrintSvgLineTracejado(getFirstLine(listaLinhaTrac),svg);
    PrintSvgLine(getFirstLine(listaLinha),svg);
    PrintSvgLine(getFirstLine(listaLinhaRaizes),svg);
    PrintSvgRect(getFirstLine(listaRetangulos),svg);

    fecharSvg(svg);
    fclose(qry);
    fclose(txt);
    free(pathSvg);
    free(pathTxt);

            /////////////////     REMOVENDO A CIDADE    ////////////////

        printf("\n\n\n -------- Excluindo Cidade -------- \n\n");
        Libera_Cidade(city);

            /////////////////     REMOVENDO A LISTA DE LINHAS    ////////////////

        printf("\n -------- Excluindo Grafo -------- \n\n");
        removeGrafo(grafo);

            /////////////////     REMOVENDO O REGISTRADOR    ////////////////

        printf("\n -------- Excluindo Registrador -------- \n\n");
        removeRegistrador(register_O);

            /////////////////     REMOVENDO A LISTA DE RETANGULOS   ////////////////

        printf("\n -------- Excluindo Lista de Retangulos -------- \n\n");
        removeListLine(listaRetangulos);

            /////////////////     REMOVENDO A LISTA DE LINHAS   ////////////////

        printf("\n -------- Excluindo Lista de Linhas -------- \n\n");
        removeListLine(listaLinha);

             /////////////////     REMOVENDO A LISTA DE LINHAS TRACEJADAS   ////////////////

        printf("\n -------- Excluindo Lista de Linhas Tracejadas -------- \n\n");
        removeListLine(listaLinhaTrac);

            /////////////////     REMOVENDO A LISTA DE LINHAS DE RAIZES  ////////////////

        printf("\n -------- Excluindo Lista de Linhas de Raizes -------- \n\n");
        removeListLine(listaLinhaRaizes);

}
