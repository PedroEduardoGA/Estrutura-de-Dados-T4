#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ConcatPathName.h"
int main(int argc, char *argv[]){
    int i = 1;
    char *ArqGeo = NULL;
    char *ArqQry = NULL;
    char *ArqV= NULL;
    char *Inpath = NULL;
    char *OutPath = NULL;
    char *aux = NULL;
    while(i<argc){
        if (strcmp("-f",argv[i])==0){
            i++;
            aux=argv[i];
            if (argv[i] == NULL || aux[0]=='-'){
                printf("Erro - Sem parametros em -f\n");
                exit(1);
            }
            ArqGeo = (char *)malloc((strlen(argv[i])+5)*sizeof(char));
            strcpy(ArqGeo,argv[i]);
            printf("Parametro -f: %s\n",ArqGeo);
        }
        else if (strcmp("-e",argv[i])==0){
            i++;
            aux=argv[i];
            if (argv[i] == NULL || aux[0]=='-'){
                printf("Erro - Sem parametros em -e\n");
                exit(1);
            }
            Inpath = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(Inpath,argv[i]);
            printf("Parametro -e: %s\n",Inpath);
        }
        else if (strcmp("-q",argv[i])==0){
            i++;
            aux=argv[i];
            if (argv[i] == NULL || aux[0]=='-'){
                printf("Erro - Sem parametros em -q\n");
                exit(1);
            }
            ArqQry = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(ArqQry,argv[i]);
            printf("Parametro -q: %s\n",ArqQry);
        }
        else if (strcmp("-o",argv[i])==0){
            i++;
            aux=argv[i];
            if (argv[i] == NULL || aux[0]=='-'){
                printf("Erro! - Sem parametros em -o\n");
                exit(1);
            }
            OutPath = (char *)malloc((strlen(argv[i])+5)*sizeof(char));
            strcpy(OutPath,argv[i]);
            printf("Parametro -o: %s\n",OutPath);
        }
        else if (strcmp("-v",argv[i])==0){
            i++;
            aux=argv[i];
            if (argv[i] == NULL || aux[0]=='-'){
                printf("Erro - Sem parametros em -v\n");
                exit(1);
            }
            ArqV = (char *)malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(ArqV,argv[i]);
            printf("Parametro -v: %s\n",ArqV);
        }
        i++;
    }
    if(ArqGeo == NULL || OutPath == NULL){
        printf("\nERRO\nArgumento essencial nao inserido\n");
        exit(1);
    }

    Concat(Inpath,ArqGeo,OutPath,ArqQry,ArqV);

    if(ArqQry != NULL){
	    free(ArqQry);
    }
    free(ArqGeo);
    if(Inpath != NULL){
        free(Inpath);
    }
	free(OutPath);
	if(ArqV != NULL){
        free(ArqV);
    }
    printf("\n\nMémoria desalocada\n");
    return 0;
}
