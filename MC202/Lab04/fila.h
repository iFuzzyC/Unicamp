#include <stdio.h>

typedef struct Lista{
	int opsInsumos[200];
	int listaLinsumos[200];
	int tamLI; 
}Lista;

/*imprime um vetor*/
void printVetor(int N, int vetor[]);
/*atualiza a lista retirando o primeiro elemento e avançando os restantes*/
void atualizaLista(int N, int vetor[]);
/*checa se o criterio de parada foi atingido*/
int parada(int insumos[], int ops[], int tam, int k);
