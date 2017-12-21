#include <stdio.h>
//estrutura que monta arvore binaria em ordem alfabetica dos clientes
typedef struct Nomes{
	char name[200];
	int pos;
	struct Nomes *right;
	struct Nomes *left;
}Nomes;
//checa lado que ira andar
int ordemAlfabetica(char nome[], Nomes *people);
//insere novo nome na arvore
Nomes *insereNome(char nome[],Nomes *people, const int data);
//imprime arvore em preOrdem
void printaPreOrdem(Nomes *people);
//checa se dois nomes sao iguais
int checaNomeIgual(char nome[], Nomes *people);
//atualiza a pos de um nome
void atualizaPos(char nome[],Nomes *people, const int data);
//devolve a pos na fila de alguem
int devolvePos(char nome[],Nomes *people);
