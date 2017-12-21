#include "bstree.h"
//checa o lado que iremos andar
int ordemAlfabetica(char nome[], Nomes *people){
	int i;
	//checa qual dos nomes tem prioridade alfabetica
	for(i = 0; nome[i] != '\0' || people->name[i] != '\0'; i++){
		if(people->name[i] > nome[i]){
			return 1;
		}
		else if( people->name[i] < nome[i]){
			return 0;
		}
	}
	return 1;
}
//insere novo nome na arvore
Nomes *insereNome(char nome[],Nomes *people, const int data){
	int i;
	//atingiu posicao para novo nome
	if (people == NULL){
		people = (Nomes*)malloc(sizeof(Nomes));
		for(i = 0; nome[i] != '\0'; i++){
			people->name[i] = nome[i];
		}
		people->name[i] = '\0';
		people->pos = data;
		people->right = NULL;
		people->left = NULL;
	}
	//nome com ordem alfabetica superior
	else if( ordemAlfabetica(nome,people) == 1 ){
		people->left = insereNome(nome, people->left,data);
	}
	//nome com ordem alfabetica inferior
	else{
		people->right = insereNome(nome, people->right,data);
	}
	return people;
}
//imprime arvore em preordem
void printaPreOrdem(Nomes *people){
	if(people != NULL){
		printf("\n%s %d",people->name, people->pos);
		printaPreOrdem(people->left);
		printaPreOrdem(people->right);
	}
}
//checa se dois nomes sao iguais
int checaNomeIgual(char nome[], Nomes *people){
	int i;
	for(i = 0;nome[i] != '\0';i++){
		if(nome[i] != people->name[i]){
			return 0;
		}
	}
	if(nome[i] == people->name[i]) return 1;
	else return 0;
}
//atualiza a ordem de prioridade de um cliente
void atualizaPos(char nome[],Nomes *people, const int data){
	if( people == NULL){
		//printf("\nDeu ruim");
		return;
	}
	else if( checaNomeIgual(nome, people) == 1){
		people->pos = data;
		return;
	}
	else{
		if(ordemAlfabetica(nome,people) == 1){
			atualizaPos(nome,people->left,data);
		}
		else{
			atualizaPos(nome,people->right, data);
		}
	}
}
//devolve a ordem de prioridade de alguem na fila
int devolvePos(char nome[],Nomes *people){
	if( people == NULL){
		//printf("\nDeu ruim");
		return;
	}
	else if( checaNomeIgual(nome, people) == 1){
		return people->pos;
	}
	else{
		if(ordemAlfabetica(nome,people) == 1){
			devolvePos(nome,people->left);
		}
		else{
			devolvePos(nome,people->right);
		}
	}
}

