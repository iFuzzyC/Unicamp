#include "btree.h"

/*aloca a arvore*/
Arvore *alocaArvore(){
	Arvore *p = (Arvore *)malloc(sizeof(Arvore));
	p->price = 0;
	p->wayPrice = 0;
	p->proxEsq = NULL;
	p->proxDir = NULL;
	return p;
}
/*coloca o preco no nó*/
void colocaArvore(const int preco, Arvore *road){
	Arvore *temp = road;
	//printf("\n>> %d",preco);
	while(temp != NULL){
		//vai pra esquerda
		road = temp;
		if(preco <= temp->price){
			if(temp->proxEsq != NULL){
				road = temp;
				temp = temp->proxEsq;
			}
			else{
				temp->proxEsq = (Arvore *)malloc(sizeof(Arvore));
				temp = temp->proxEsq;
				temp->price = preco;
				temp->wayPrice = temp->price + road->wayPrice;
				temp->proxDir = NULL;
				temp->proxEsq = NULL;
				return;
			}
		}
		//vai para a direita
		else{
			if(temp->proxDir != NULL){
				temp = temp->proxDir;
			}
			else{
				temp->proxDir = (Arvore *)malloc(sizeof(Arvore));
				temp = temp->proxDir;
				temp->price = preco;
				temp->wayPrice = temp->price + road->wayPrice;
				temp->proxDir = NULL;
				temp->proxEsq = NULL;
				return;
			}
		}
	}

}
/*calculo do valor pago*/
int firstRoad(Arvore *road){
	int soma = 0;
	Arvore *esquerda, *direita;
	soma = road->price;
	while(road != NULL){
		//checa em quais direcoes e possivel ir
		if(road->proxEsq != NULL){
			esquerda = road->proxEsq;
		}
		else if (road->proxDir != NULL){
			direita = road->proxDir;
		}
		//checa qual direcao tem o menor preco
		if(road->proxEsq != NULL && road->proxDir != NULL && esquerda->price <= direita->price){
			road = road->proxEsq;
		}
		else if(road->proxEsq != NULL && road->proxDir != NULL && esquerda->price > direita->price){
			road = road->proxDir;
		}
		else if(road->proxEsq != NULL && road->proxDir == NULL){
			road = road->proxEsq;
		}
		else if(road->proxEsq == NULL && road->proxDir != NULL){
			road = road->proxDir;
		}
		soma = soma + road->price;
		if(road->proxDir == NULL && road->proxEsq == NULL){
			return soma;
		}
	}
	return soma;
}
/*retorna o menor valor que poderia ser pago*/
int bestRoad(const int MAX, Arvore *road){
	Arvore *temp = road, *inicio = road;
	int cheap = MAX;

	/*checa se o no inicial possui ramos em ambas direcoes*/
	if(inicio->proxDir == NULL){
		inicio->proxDir = (Arvore*)malloc(sizeof(Arvore));
		inicio->wayPrice = -1;
		inicio->price = 0;
		inicio->proxDir->proxEsq = NULL;
		inicio->proxDir->proxDir = NULL;
	}
	if(inicio->proxEsq == NULL){
		inicio->proxEsq = (Arvore*)malloc(sizeof(Arvore));
		inicio->wayPrice = -1;
		inicio->price = 0;
		inicio->proxEsq->proxEsq = NULL;
		inicio->proxEsq->proxDir = NULL;
	}
	/*procura a folha com o menor wayPrice*/
	while(inicio->proxDir->wayPrice != -1 || inicio->proxEsq->wayPrice != -1){
		//da preferencia a esquerda
		if( temp->proxEsq != NULL){
			//nao pode ir pra esquerda
			if (temp->proxEsq->wayPrice == -1){
				//ve se pode ir para direita
				if(temp->proxDir != NULL){
					if (temp->proxDir->wayPrice != -1){
						temp = temp->proxDir;
					}
					else{
						temp->wayPrice = -1;
						temp = inicio;
					}
				}
				//nao pode ir para a direita
				else{
					temp->wayPrice = -1;
					temp = inicio;
				}
			}
			//pode ir para a esquerda
			else{
				temp = temp->proxEsq;
			}
		}
		//checa a direita
		else if (temp->proxDir != NULL){
			//ve se pode continuar
			if(temp->proxDir->wayPrice == -1){
				temp->wayPrice = -1;
				temp = inicio;
			}
			//vai para a direita
			else{
				temp = temp->proxDir;
			}
		}
		//chegou em folha -- checa o wayPrice da folha
		else if(temp->proxDir == NULL && temp->proxEsq == NULL){
			if(temp->wayPrice < cheap && temp->wayPrice != 0){
				cheap = temp->wayPrice;
			}
			temp->wayPrice = -1;
			temp = inicio;
		}
	}
	return cheap;
}


