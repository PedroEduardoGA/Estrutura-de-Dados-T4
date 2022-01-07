#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ConcatPathName.h"
#include "Leitura.h"

char *FileName(char namegeo[]) {
    char *aux = strrchr(namegeo,'/');
    if (aux == NULL) {
        return strtok(namegeo,".");
    }
	return strtok(&aux[1],".");
}

void Concat(char *Inpath, char *ArqGeo, char *OutPath, char *ArqQry, char *ArqV){
    char *EntryPathGeo = NULL;
    char *EntryPathQry = NULL;
    char *EntryPathV = NULL;
    char *filename = NULL;
    char *ExitPath = NULL;
    char *SvgGeo = NULL;
    char *QryName = NULL;
    char *qryNoExtention = NULL;

    if (Inpath) {
        ArqGeo= FileName(ArqGeo);
        strcat(ArqGeo, ".geo");

        if (Inpath[strlen(Inpath) - 1] != '/') {
            EntryPathGeo = (char*) malloc((strlen(Inpath) + strlen(ArqGeo) + 2) * sizeof(char));
            sprintf(EntryPathGeo, "%s/%s", Inpath, ArqGeo);
        } else {
            EntryPathGeo = (char*) malloc((strlen(Inpath) + strlen(ArqGeo) + 1) * sizeof(char));
            sprintf(EntryPathGeo, "%s%s", Inpath,ArqGeo);
        }
        if (ArqQry) {
            ArqQry = strtok(ArqQry,".");
            if (Inpath[strlen(Inpath) - 1] != '/') {
                EntryPathQry = (char*) malloc((strlen(Inpath) + strlen(ArqQry) + 6) * sizeof(char));
                sprintf(EntryPathQry, "%s/%s.qry", Inpath, ArqQry);
            }else{
                EntryPathQry = (char*) malloc((strlen(Inpath) + strlen(ArqQry) + 5) * sizeof(char));
                sprintf(EntryPathQry, "%s%s.qry", Inpath,ArqQry);
            }
        }
        if (ArqV) {
            ArqV = strtok(ArqV,".");
            if (Inpath[strlen(Inpath) - 1] != '/') {
                EntryPathV = (char*) malloc((strlen(Inpath) + strlen(ArqV) + 6) * sizeof(char));
                sprintf(EntryPathV, "%s/%s.via", Inpath, ArqV);
            }else{
                EntryPathV = (char*) malloc((strlen(Inpath) + strlen(ArqV) + 5) * sizeof(char));
                sprintf(EntryPathV, "%s%s.via", Inpath,ArqV);
            }
        }
    } else {
        EntryPathGeo = (char*) malloc((strlen(ArqGeo) + 1) * sizeof(char));
        strcpy(EntryPathGeo, ArqGeo);
        if (ArqQry) {
            EntryPathQry = (char*) malloc((strlen(ArqQry) + 5) * sizeof(char));
            sprintf(EntryPathQry, "%s.qry",ArqQry);
        }
        if (ArqV) {
            EntryPathV = (char*) malloc((strlen(ArqV) + 5) * sizeof(char));
            sprintf(EntryPathV, "%s.via",ArqV);
        }
    }

    filename = FileName(ArqGeo);

    if (OutPath[strlen(OutPath) - 1] != '/') {  //diretorio de saida recebe o nome do arquivo geo sem extensão
        ExitPath = (char*) malloc((strlen(OutPath) + strlen(filename) + 2) * sizeof(char));
        sprintf(ExitPath, "%s/%s",OutPath, filename);
    } else {
        ExitPath = (char*) malloc((strlen(OutPath) + strlen(filename) + 1) * sizeof(char));
        sprintf(ExitPath, "%s%s",OutPath, filename);
    }

    SvgGeo = (char*) malloc((strlen(ExitPath) + 5) * sizeof(char));
    sprintf(SvgGeo, "%s.svg", ExitPath);


    if (EntryPathQry) {
        QryName = FileName(ArqQry);
        qryNoExtention = (char*) malloc((strlen(ExitPath) + strlen(QryName) + 2) * sizeof(char));
        sprintf(qryNoExtention, "%s-%s", ExitPath, QryName);
    }
    Leitura_Geo(EntryPathGeo, SvgGeo,EntryPathQry,qryNoExtention,EntryPathV);

    if (EntryPathQry) {
        free(qryNoExtention);
        free(EntryPathQry);
    }
    if(EntryPathV){
        free(EntryPathV);
    }
    free(EntryPathGeo);
    free(ExitPath);
    free(SvgGeo);
}
