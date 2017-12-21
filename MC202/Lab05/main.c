#include "btree.h"

int main(){
	Arvore *road = alocaArvore();
	//recebendo a quantidade de nos
	int n;
	scanf("%d",&n);
	//recebendo os nos
	int i, preco;
	for(i = 0;i < n;i++){
		scanf(" %d",&preco);
		colocaArvore(preco,road);
	}

	/*calculando quanto ele pagou*/
	int pagou = firstRoad(road);

	/*calculando a rota com menor valor*/
	road = road->proxDir;
	int cheaper = bestRoad(pagou, road);
	int t = pagou - cheaper;
	printf("%d",t);
	/*calculando a economia*/
}
