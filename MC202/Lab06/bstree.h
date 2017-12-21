#include "row.h"
#include <stdio.h>



/*coloca recusirvamente um novo no na arvore*/
Btree *colocaArvore(const int year, const int month, const int day, const int hour, const int minute, Btree *arv, const int lat,const int log, const int ar);
/*imprime os elementos da arvore em pre ordem*/
void printPreOrdem(Btree *no);
/*encontra o no que deve ser apagado e o apaga*/
void achaNo(const int year, const int month, const int day, const int hour, const int minute, Btree *arv, const int pors,Btree *noAnt, const int dir);
/*apaga um no com o seu predecessor*/
void trocaComPredecessor(Btree *root, Btree *temp);
/*apaga no com o seu sucessor*/
void trocaComSucessor(Btree* root, Btree *temp);

