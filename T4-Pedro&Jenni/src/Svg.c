#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Svg.h"
#include "ArvoreAVL.h"
#include "Grafo.h"

FILE* iniciarSvg(char filename[]){

    FILE* svg = fopen(filename, "w");
    if(svg == NULL){
        printf("erro ao abrir o arquivo svg\n");
        exit(1);
    }
    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\"\n\txmlns:xlink=\"http://www.w3.org/1999/xlink\">\n");
    fprintf(svg, "Jennifer do Prado da Silva e Pedro Eduardo Garbossa de Almeida\n");
    fprintf(svg, "\t\t<text x=\"0\" y=\"-100\" style=\"stroke:#000000; fill: #000000; font-family:Arial; font-size: 30px;\" >Jennifer do Prado da Silva e Pedro Eduardo Garbossa de Almeida</text>\n");
    return svg;
}

void fecharSvg(FILE* svg){
    fprintf(svg, "</svg>");
    fclose(svg);
}

void CriaSvg(ArvoreAvl arv, char SvgGeo[],GrafoV grafo){
    FILE *svg = iniciarSvg(SvgGeo);
    Imprime_Info_Svg(arv, grafo, svg);
    fecharSvg(svg);
}

void Imprime_Info_Svg(ArvoreAvl arv, GrafoV grafo, FILE* svg){
    PrintSvgArv(getFirstAvl(arv),svg);
    PrintSvgGrafo(grafo,svg,0);
}

void CriaSvgConsulta(ArvoreAvl arv, GrafoV grafo, FILE* svg){
    Imprime_Info_Svg(arv, grafo, svg);
}
