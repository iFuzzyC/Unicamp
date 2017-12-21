#include "bstree.h"

/*define a struct para a arvore*/
typedef struct BinTree{
	int ano;
	int mes;
	int dia;
	int hora;
	int minuto;
	int latitude;
	int longitude;
	int area;
	struct BinTree *proxDir;
	struct BinTree *proxEsq;
}Btree;

/*recebe o char e a arvore e a partir do char decide qual comando fazer*/
void whatToDo(const char com,Btree *arv);
/*decide qual o lado para o qual o no deve ir*/
int checaLado(const int year,const int month, const int day,const int hour,const int minute,Btree *arv);
/*encontra o no a ser atualizado e o atualiza*/
void procuraNo(const int year,const int month,const int day,const int hour,const int minute,Btree* arv,const int lat,const int log,const int ar);
