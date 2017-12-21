#include <stdio.h>

typedef struct Arvore{
	int price;
	int wayPrice;//guarda o valor gasto ate o no
	struct Arvore *proxEsq;
	struct Arvore *proxDir;
}Arvore;

/*aloca a arvore*/
Arvore *alocaArvore();
/*coloca o preco no nó*/
void colocaArvore(const int preco, Arvore *road);
/*calculo do valor pago*/
int firstRoad(Arvore *road);
/*retorna o menor valor que poderia ser pago*/
int bestRoad(const int MAX, Arvore *road);


