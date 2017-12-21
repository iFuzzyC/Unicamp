#include "fila.h"

void printVetor(int N, int vetor[]){
	int i;
	for(i = 0;i < N; i++){
		printf(" - %d",vetor[i]);
	}
}
void atualizaLista(int N, int vetor[]){
	int t[N], i;
	for(i=1;i<N;i++){
		t[i-1] = vetor[i];
	}
	t[N-1] = 0;
	
	for(i = 0;i<N;i++){
		vetor[i] = t[i];
	}
}
int parada(int insumos[], int ops[], int tam, int k){
	int i;
	/*checa se ainda tem elemento na fila*/
	for(i = 0;i < tam;i++){
		if(insumos[i] != 0 ) return 1;
	}
	for(i = 0;i < k;i++){
		if(ops[i] == 0 ) return 0;
	}
	return 1;
}

