#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreAVL.h"
#include "Quadra.h"
#include "ListaDin.h"

typedef struct NOAVL{
    Quadra quadra;
    Lista lista;
    int altura,fb, qtdQuadraList;
    double min, max;
    struct NOAVL *esq;
    struct NOAVL *dir;
    struct NOAVL *pai;
}NoAvl;

typedef struct arvore{
    NoAvl *raiz;
}Arv_Avl;

ArvoreAvl cria_ArvAVL(){
    Arv_Avl* Arvore = (Arv_Avl*) malloc(sizeof(Arv_Avl));
    Arvore->raiz = NULL;
    return Arvore;
}

NOAVL getFirstAvl(ArvoreAvl arv){
    Arv_Avl* A = (Arv_Avl*) arv;
    return A->raiz;
}

int getAltura(NOAVL A){
    NoAvl* no = (NoAvl*) A;
    return no->altura;
}

int getFb(NOAVL A){
    NoAvl* no = (NoAvl*) A;
    return no->fb;
}

int altura_NO(NOAVL A){
    NoAvl* no = (NoAvl*) A;
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(NOAVL A){
    NoAvl* no = (NoAvl*) A;
    return (altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

void RotacaoLL(ArvoreAvl arv, NOAVL no){//LL
    Arv_Avl* Arvore = (Arv_Avl*) arv;
    NoAvl* A = (NoAvl*) no;

    NoAvl *B;
    B = A->esq;
    A->esq = B->dir;
    if(B->dir != NULL){
        B->dir->pai = A;
        A->min = B->dir->min;
    }else
        A->min = getXQuad(A->quadra);
    B->dir = A;
    B->max = A->max;
    A->altura = maior(altura_NO(A->esq),altura_NO(A->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),A->altura) + 1;

    if(Arvore->raiz == A){
        Arvore->raiz = B;
        B->pai = NULL;
    }else{
        if(A == A->pai->dir){
            A->pai->dir = B;
        }else{
            A->pai->esq = B;
        }
        B->pai = A->pai;
    }

    A->pai = B;
}

void RotacaoRR(ArvoreAvl arv, NOAVL no){//RR
    Arv_Avl* Arvore = (Arv_Avl*) arv;
    NoAvl* A = (NoAvl*) no;

    NoAvl* B;
    B = A->dir;
    A->dir = B->esq;
    if(B->esq != NULL){
        B->esq->pai = A;
        A->max = B->esq->max;
    }else
        A->max = getXQuad(A->quadra) + getWQuad(A->quadra);
    B->esq = A;
    B->min = A->min;
    A->altura = maior(altura_NO(A->esq),altura_NO(A->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),A->altura) + 1;
    if(Arvore->raiz == A){
        Arvore->raiz = B;
        B->pai = NULL;
    }else{
        if(A == A->pai->dir)
            A->pai->dir = B;
        else
            A->pai->esq = B;
        B->pai = A->pai;
    }

    A->pai = B;
}

void RotacaoLR(ArvoreAvl arv, NOAVL no){ //LR
    NoAvl* A = (NoAvl*) no;
    RotacaoRR(arv,A->esq);
    RotacaoLL(arv,A);
}

void RotacaoRL(ArvoreAvl arv, NOAVL no){//RL
    NoAvl* A = (NoAvl*) no;
    RotacaoLL(arv,A->dir);
    RotacaoRR(arv,A);
}

NOAVL insere_ArvAVL(ArvoreAvl arv, NOAVL NoR, Quadra Quad){
    NoAvl* res = NULL;
    Arv_Avl* A = (Arv_Avl*) arv;

    NoAvl* NoRaiz = (NoAvl*)NoR;

    if(A->raiz == NULL || NoRaiz == NULL){//árvore vazia ou nó folha
        NoAvl *novo;
        novo = (NoAvl*)malloc(sizeof(NoAvl));

        novo->lista = createListDin();
        novo->quadra = Quad;
        novo->fb = 0;
        novo->altura = 0;
        novo->qtdQuadraList = 0;
        novo->min = getXQuad(Quad);
        novo->max = getXQuad(Quad)+getWQuad(Quad);
        novo->esq = NULL;
        novo->dir = NULL;
        if(A->raiz == NULL){
            novo->pai = NULL;
            A->raiz = novo;
        }
        return novo;
    }

    if(getXQuad(Quad) < getXQuad(NoRaiz->quadra)){
        res = insere_ArvAVL(A, NoRaiz->esq, Quad);
        if(res != NULL){
            res->pai = NoRaiz;
            NoRaiz->esq = res;
            res = NULL;
        }
        if(NoRaiz->dir != NULL && NoRaiz->min > NoRaiz->esq->min)
            NoRaiz->min = NoRaiz->esq->min;
        if(NoRaiz->esq != NULL && NoRaiz->max < NoRaiz->esq->max)
            NoRaiz->max = NoRaiz->esq->max;

        if(res == NULL){
            NoRaiz->fb = fatorBalanceamento_NO(NoRaiz);
            if((NoRaiz->fb >= 2) || (NoRaiz->fb <= -2)){
                if(getXQuad(NoRaiz->esq->quadra) > getXQuad(Quad)){
                    RotacaoLL(A,NoRaiz);
                }else{
                    RotacaoLR(A,NoRaiz);
                }
                NoRaiz->fb = fatorBalanceamento_NO(NoRaiz);
            }
        }
    }else{
        if(getXQuad(Quad) > getXQuad(NoRaiz->quadra)){
            res = insere_ArvAVL(A, NoRaiz->dir, Quad);
            if(res != NULL){
                res->pai = NoRaiz;
                NoRaiz->dir = res;
                res = NULL;
            }
            if(NoRaiz->dir != NULL && NoRaiz->max < NoRaiz->dir->max)
                NoRaiz->max = NoRaiz->dir->max;
            if(NoRaiz->esq != NULL && NoRaiz->max < NoRaiz->esq->max)
                NoRaiz->max = NoRaiz->esq->max;

            if(res == NULL){
                NoRaiz->fb = fatorBalanceamento_NO(NoRaiz);
                if((NoRaiz->fb >= 2) || (NoRaiz->fb <= -2)){
                    if(getXQuad(NoRaiz->dir->quadra) < getXQuad(Quad)){
                        RotacaoRR(A,NoRaiz);
                    }else{
                        RotacaoRL(A,NoRaiz);
                    }
                    NoRaiz->fb = fatorBalanceamento_NO(NoRaiz);
                }
            }
        }else{
            InsertDin(NoRaiz->lista,Quad);
            if(getXQuad(Quad) + getWQuad(Quad) > NoRaiz->max)
                NoRaiz->max = getXQuad(Quad) + getWQuad(Quad);

            NoRaiz->qtdQuadraList += 1;
        }
    }

    NoRaiz->altura = maior(altura_NO(NoRaiz->esq),altura_NO(NoRaiz->dir)) + 1;

    return res;
}

void PrintSvgArv(NOAVL NoR, FILE* svg){
    NoAvl* raiz = (NoAvl*) NoR;
    if(raiz == NULL)
        return;

    fprintf(svg, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\"/>\n",getXQuad(raiz->quadra),getYQuad(raiz->quadra),getWQuad(raiz->quadra),getHQuad(raiz->quadra),getCFILL(raiz->quadra),getCSTRK(raiz->quadra),getSW(raiz->quadra));
    fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\" style=\"stroke:#000000; fill: #000000; font-family:Arial; font-size: 15px;\" >%s</text>\n",getXQuad(raiz->quadra),getYQuad(raiz->quadra)+15,getCEP(raiz->quadra));

    PrintSvgLista(getFirstDin(raiz->lista),svg);
    PrintSvgArv(raiz->esq,svg);
    PrintSvgArv(raiz->dir,svg);
}

void IniciaDot(NOAVL NoR, FILE* dot){
    NoAvl* raiz = (NoAvl*) NoR;
    fprintf(dot, "digraph Arvorezinha {\n\t size=\"10000\";\n\tnode [fillcolor=\"violet:white\", style=filled];\n");
    ImprimeArvore(raiz,dot);
    fprintf(dot, "}");
}

void ImprimeArvore(NOAVL NoR, FILE* dot){
    NoAvl* raiz = (NoAvl*) NoR;
    NoAvl* atual = raiz;
    if(raiz == NULL)
        return;

    if(raiz != NULL){
        if(raiz->pai == NULL && raiz->esq == NULL && raiz->dir == NULL)
            fprintf(dot,"\"X: %.2lf \\nCEP: %s   FB: %d\\nQtdQuadrasList: %d \\nCEP 1 Lista: %s \\nCEP 2 Lista: %s \\nMin: %.2lf  Max: %.2lf\";\n",getXQuad(raiz->quadra),getCEP(raiz->quadra),raiz->fb,raiz->qtdQuadraList,AnalizaCEP_NULL(getFirstDin(raiz->lista)),AnalizaCEP_NULL(getNextDin(getFirstDin(raiz->lista))),raiz->min,raiz->max);
        if(raiz->esq != NULL || raiz->dir != NULL){
            if(raiz->esq != NULL)
                fprintf(dot,"\"X: %.2lf \\nCEP: %s   FB: %d\\nQtdQuadrasList: %d \\nCEP 1 Lista: %s \\nCEP 2 Lista: %s \\nMin: %.2lf  Max: %.2lf\"->\"X: %.2lf \\nCEP: %s   FB: %d\\nQtdQuadrasList: %d \\nCEP 1 Lista: %s \\nCEP 2 Lista: %s \\nMin: %.2lf  Max: %.2lf\";\n",getXQuad(raiz->quadra),getCEP(raiz->quadra),raiz->fb,raiz->qtdQuadraList,AnalizaCEP_NULL(getFirstDin(raiz->lista)),AnalizaCEP_NULL(getNextDin(getFirstDin(raiz->lista))),raiz->min,raiz->max,getXQuad(raiz->esq->quadra),getCEP(raiz->esq->quadra),raiz->esq->fb,raiz->esq->qtdQuadraList,AnalizaCEP_NULL(getFirstDin(raiz->esq->lista)),AnalizaCEP_NULL(getNextDin(getFirstDin(raiz->esq->lista))),raiz->esq->min,raiz->esq->max);  //ou em vez de (*raiz)->esq->info posso usar a função getInfo(&((*raiz)->esq))
            else
                fprintf(dot,"\"X: %.2lf \\nCEP: %s   FB: %d\\nQtdQuadrasList: %d \\nCEP 1 Lista: %s \\nCEP 2 Lista: %s \\nMin: %.2lf  Max: %.2lf\"->\"\\n\tX: %.2lf Left NULL\\n\\n ---------\\n------\\n---\\n\"[style=\"invis\"];\n",getXQuad(raiz->quadra),getCEP(raiz->quadra),raiz->fb,raiz->qtdQuadraList,AnalizaCEP_NULL(getFirstDin(raiz->lista)),AnalizaCEP_NULL(getNextDin(getFirstDin(raiz->lista))),raiz->min,raiz->max,getXQuad(raiz->quadra));

            if(raiz->dir != NULL)
                fprintf(dot,"\"X: %.2lf \\nCEP: %s   FB: %d\\nQtdQuadrasList: %d \\nCEP 1 Lista: %s \\nCEP 2 Lista: %s \\nMin: %.2lf  Max: %.2lf\"->\"X: %.2lf \\nCEP: %s   FB: %d\\nQtdQuadrasList: %d \\nCEP 1 Lista: %s \\nCEP 2 Lista: %s \\nMin: %.2lf  Max: %.2lf\";\n",getXQuad(raiz->quadra),getCEP(raiz->quadra),raiz->fb,raiz->qtdQuadraList,AnalizaCEP_NULL(getFirstDin(raiz->lista)),AnalizaCEP_NULL(getNextDin(getFirstDin(raiz->lista))),raiz->min,raiz->max,getXQuad(raiz->dir->quadra),getCEP(raiz->dir->quadra),raiz->dir->fb,raiz->dir->qtdQuadraList,AnalizaCEP_NULL(getFirstDin(raiz->dir->lista)),AnalizaCEP_NULL(getNextDin(getFirstDin(raiz->dir->lista))),raiz->dir->min,raiz->dir->max);
            else
                fprintf(dot,"\"X: %.2lf \\nCEP: %s   FB: %d\\nQtdQuadrasList: %d \\nCEP 1 Lista: %s \\nCEP 2 Lista: %s \\nMin: %.2lf  Max: %.2lf\"->\"\\n\tX: %.2lf Right NULL\\n\\n ---------\\n------\\n---\\n\"[style=\"invis\"];\n",getXQuad(raiz->quadra),getCEP(raiz->quadra),raiz->fb,raiz->qtdQuadraList,AnalizaCEP_NULL(getFirstDin(raiz->lista)),AnalizaCEP_NULL(getNextDin(getFirstDin(raiz->lista))),raiz->min,raiz->max,getXQuad(raiz->quadra));
        }

        ImprimeArvore(atual->esq,dot);  //caso
        ImprimeArvore(atual->dir,dot);

    }
}

char* AnalizaCEP_NULL(No elemento){

    if(elemento == NULL)
        return "-";
    else
        return getCEP(getQuadraList(elemento));
}

NOAVL procuraMenor(NOAVL no){
    NoAvl* atual = (NoAvl*)no;
    NoAvl* no1 = atual;
    NoAvl* no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

Quadra procuraQuadra(NOAVL no, char cep[]){
    NoAvl* noavl = (NoAvl*)no;
    Quadra aux = NULL;

    if(noavl == NULL)
        return NULL;

    if((strcmp(getCEP(noavl->quadra),cep)) == 0)
        return noavl->quadra;

    No noL = ProcuraQuadCEPList(getFirstDin(noavl->lista),cep);
    aux = getQuadraList(noL);
    if(aux != NULL && (strcmp(getCEP(aux),cep)) == 0)
        return aux;

    aux = procuraQuadra(noavl->esq, cep);
    if(aux == NULL)
        aux = procuraQuadra(noavl->dir, cep);

    return aux;
}

void ProcuraQuadPodando(NOAVL no,Lista L, double x, double y, double w, double h){
    NoAvl* noavl = (NoAvl*)no;

    if(noavl == NULL)
        return;

    if(getXQuad(noavl->quadra) >= x  &&  getYQuad(noavl->quadra) >= y  &&  getXQuad(noavl->quadra) + getWQuad(noavl->quadra) <= x+w  &&  getYQuad(noavl->quadra) + getHQuad(noavl->quadra) <= y+h)
        InsertDin(L, noavl->quadra);

    ProcuraQuadPodandoList(getFirstDin(noavl->lista),L,x,y,w,h);

    if(noavl->esq != NULL && noavl->esq->max >= x && noavl->esq->min <= x+w)
        ProcuraQuadPodando(noavl->esq,L,x,y,w,h);

    if(noavl->dir != NULL && noavl->dir->max >= x && noavl->dir->min <= x+w)
        ProcuraQuadPodando(noavl->dir,L,x,y,w,h);
}

NOAVL Troca_No(ArvoreAvl arv,NOAVL antigo,NOAVL novo){
    Arv_Avl* A = (Arv_Avl*) arv;
    NoAvl* NoAntigo = (NoAvl*)antigo;
    NoAvl* NoNovo = (NoAvl*)novo;
    NoAvl* aux = NoNovo->pai;
    NoAvl* esq = NoNovo->esq;
    NoAvl* dir = NoNovo->dir;
    int i;

    if(A->raiz == NoAntigo){
        A->raiz = NoNovo;
        NoNovo->pai = NULL;
    }else{
        if(NoAntigo->pai->esq == NoAntigo)
            NoAntigo->pai->esq = NoNovo;
        else
            NoAntigo->pai->dir = NoNovo;
        NoNovo->pai = NoAntigo->pai;
    }
    NoNovo->esq = NoAntigo->esq;
    NoNovo->esq->pai = NoNovo;
    if(NoAntigo->dir != NoNovo){
        NoNovo->dir = NoAntigo->dir;
        aux->esq = NoAntigo;
        NoAntigo->pai = aux;
    }else{
        NoNovo->dir = NoAntigo;
        NoAntigo->pai = NoNovo;
    }
    NoNovo->dir->pai = NoNovo;
    NoAntigo->esq = esq; NoAntigo->dir = dir;
    if(esq != NULL) esq->pai = NoAntigo;
    if(dir != NULL) dir->pai = NoAntigo;

    i = NoNovo->altura;
    NoNovo->altura = NoAntigo->altura;
    NoAntigo->altura = i;

    return NoNovo;
}

int remove_ArvAVL(ArvoreAvl arv, NOAVL NoR, Quadra Quad){
    Arv_Avl* A = (Arv_Avl*) arv;
    NoAvl* NoRaiz = (NoAvl*)NoR;
    int maxDir,maxEsq;

	if(NoRaiz == NULL){// valor não existe
	    return 0;
	}

    int res;
	if(getXQuad(Quad) < getXQuad(NoRaiz->quadra)){
	    if((res = remove_ArvAVL(arv,NoRaiz->esq,Quad)) == 1){
            if(NoRaiz->esq != NULL)
                NoRaiz->min = NoRaiz->esq->min;
            if(fatorBalanceamento_NO(NoRaiz) >= 2){
                if(altura_NO(NoRaiz->dir->esq) <= altura_NO(NoRaiz->dir->dir))
                    RotacaoRR(arv,NoRaiz);
                else
                    RotacaoRL(arv,NoRaiz);
            }
	    }
	}

	if(getXQuad(Quad) > getXQuad(NoRaiz->quadra)){
	    if((res = remove_ArvAVL(arv,NoRaiz->dir, Quad)) == 1){
            if(NoRaiz->dir != NULL)
                NoRaiz->max = NoRaiz->dir->max;
            if(fatorBalanceamento_NO(NoRaiz) >= 2){
                if(altura_NO(NoRaiz->esq->dir) <= altura_NO(NoRaiz->esq->esq) )
                    RotacaoLL(arv,NoRaiz);
                else
                    RotacaoLR(arv,NoRaiz);
            }
	    }
	}

	if(getXQuad(Quad) == getXQuad(NoRaiz->quadra)){
        if((strcmp(getCEP(Quad),getCEP(NoRaiz->quadra))) == 0){
            if(getFirstDin(NoRaiz->lista) == NULL){
                if(NoRaiz->esq == NULL || NoRaiz->dir == NULL){// nó tem 1 filho ou nenhum
                    NoAvl* oldNode = NoRaiz;
                    if(NoRaiz->esq != NULL){
                        if(A->raiz == NoRaiz){
                            A->raiz = NoRaiz->esq;
                            NoRaiz->esq->pai = NULL;
                        }else{
                            if(NoRaiz->pai->esq == NoRaiz)
                                NoRaiz->pai->esq = NoRaiz->esq;
                            else
                                NoRaiz->pai->dir = NoRaiz->esq;
                            NoRaiz->esq->pai = NoRaiz->pai;
                        }
                        NoRaiz = NoRaiz->esq;
                    }else if(NoRaiz->dir != NULL){
                        if(A->raiz == NoRaiz){
                            A->raiz = NoRaiz->dir;
                            NoRaiz->dir->pai = NULL;
                        }else{
                            if(NoRaiz->pai->esq == NoRaiz)
                                NoRaiz->pai->esq = NoRaiz->dir;
                            else
                                NoRaiz->pai->dir = NoRaiz->dir;
                            NoRaiz->dir->pai = NoRaiz->pai;
                        }
                        NoRaiz = NoRaiz->dir;
                    }else{
                        if(NoRaiz->pai->esq == NoRaiz){
                            NoRaiz->pai->esq = NULL;
                            NoRaiz->pai->min = getXQuad(NoRaiz->pai->quadra);
                        }
                        else{
                            NoRaiz->pai->dir = NULL;
                        }
                        NoRaiz = NoRaiz->pai;
                    }
                    libera_QUADRA(oldNode->quadra);
                    removeListDin(oldNode->lista);
                    free(oldNode);
                }else { // nó tem 2 filhos
                    NoAvl* temp = (NoAvl*) procuraMenor(NoRaiz->dir);
                    temp->min = NoRaiz->min;     temp->max = NoRaiz->max;
                    temp = Troca_No(arv,NoRaiz,temp);
                    remove_ArvAVL(arv, temp->dir, NoRaiz->quadra);
                    temp->altura = maior(altura_NO(NoRaiz->esq),altura_NO(NoRaiz->dir)) + 1;
                    temp->fb = fatorBalanceamento_NO(temp);
                    if(temp->fb >= 2){
                        if(altura_NO(temp->esq->dir) <= altura_NO(temp->esq->esq))
                            RotacaoLL(arv,temp);
                        else
                            RotacaoLR(arv,temp);
                    }
                    NoRaiz = temp;
                }
                NoRaiz->max = getXQuad(NoRaiz->quadra) + getWQuad(NoRaiz->quadra);
                if(NoRaiz->dir != NULL && NoRaiz->max < NoRaiz->dir->max)
                    NoRaiz->max = NoRaiz->dir->max;
                if(NoRaiz->esq != NULL && NoRaiz->max < NoRaiz->esq->max)
                    NoRaiz->max = NoRaiz->esq->max;
                if (NoRaiz != NULL){
                    NoRaiz->altura = maior(altura_NO(NoRaiz->esq),altura_NO(NoRaiz->dir)) + 1;
                    NoRaiz->fb = fatorBalanceamento_NO(NoRaiz);
                }
            }else{
                libera_QUADRA(NoRaiz->quadra);
                NoRaiz->quadra = getQuadraList(getFirstDin(NoRaiz->lista));
                proximoNoList(NoRaiz->lista);
                maxDir = 0;
                maxEsq = 0;
                if(NoRaiz->dir != NULL)
                    maxDir = NoRaiz->dir->max;
                if(NoRaiz->esq != NULL)
                    maxEsq = NoRaiz->esq->max;
                NoRaiz->max = ProcuraMaxList(getFirstDin(NoRaiz->lista), getXQuad(NoRaiz->quadra) + getWQuad(NoRaiz->quadra),maxDir,maxEsq);
                NoRaiz->qtdQuadraList -= 1;
            }
        }else{
            No noList = ProcuraQuadCEPList(getFirstDin(NoRaiz->lista),getCEP(Quad));
            Libera_NO_List(NoRaiz->lista,noList);
            maxDir = 0;
            maxEsq = 0;
            if(NoRaiz->dir != NULL)
                maxDir = NoRaiz->dir->max;
            if(NoRaiz->esq != NULL)
                maxEsq = NoRaiz->esq->max;
            NoRaiz->max = ProcuraMaxList(getFirstDin(NoRaiz->lista), getXQuad(NoRaiz->quadra) + getWQuad(NoRaiz->quadra),maxDir,maxEsq);
            NoRaiz->qtdQuadraList -= 1;
        }
		return 1;
	}

	NoRaiz->altura = maior(altura_NO(NoRaiz->esq),altura_NO(NoRaiz->dir)) + 1;

	return res;
}

void libera_NO(NOAVL A){
    NoAvl* no = (NoAvl*) A;
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    libera_QUADRA(no->quadra);
    removeListDin(no->lista);
    free(no);
    no = NULL;
}
//
void libera_ArvAVL(ArvoreAvl arv){
    Arv_Avl* A = (Arv_Avl*) arv;

    if(A->raiz != NULL)
        libera_NO(A->raiz);  //libera cada nó
    free(A);
}
