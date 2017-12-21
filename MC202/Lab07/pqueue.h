#include "bstree.h"
#include "request.h"
//estrutura que guarda os clientes em ordem de prioridade
typedef struct fila{
	Request *pessoa;
	int prioridade;
	int processado;
}Fila;
//imprime a fila de prioridade
void printaFila(Fila *p, const int n);
//checa qual dos dois clientes possue maior prioridade
int checaPrioridade(Request *novo, Request *velho);
//insere novo cliente na fila de prioridade
void insereFila(Fila *pr, Request *pedido, const int pos, const int max, Nomes *people);
//auxilia a criar a fila de prioridade e a construir a arvore binaria
Nomes *ordemPrioridade(Request *pedido, Fila *pr, const int max, Nomes *people);
//remove cliente - coloca-o em ultimo para ser substituido
void removeCliente(Fila *pr, Nomes *people, const int pos,const int max);
//atualiza a posicao de prioridade numa fila de prioridade
void atualizaClientePosicao(Request *pedido, Fila *pr, const int max, Nomes *people);
//atualiza o flag do cliente, aumentando assim a prioridade do mesmo
void atualizaFlag(char flagNome[], Fila *pr, Nomes *people,const int max);
