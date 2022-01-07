#ifndef _H_CONCATPATHNAME
#define _H_CONCATPATHNAME

//ConcatPathName.h é reservado para concatenar os nomes dos arquivo com os caminhos de entrada e saída recebidos

char *FileName(char namegeo[]); //recebe o nome do geo com extensao e retorna somente seu nome sem extensão

void Concat(char *Inpath, char *ArqGeo, char *OutPath, char *ArqQry, char *ArqV); //concatena o nome de um arquivo qry, geo, via, svg, txt com seus devidos caminhos de entrada(ou saída se for svg ou txt)

#endif
