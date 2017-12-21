#include "fila.h"


int main(){
	int i, aux;
	/*variaveis importantes*/
	Lista ops;
	int n, k, m;
	scanf("%d %d %d",&n,&k,&m);
	int tempos[n];
	for(i = 0;i < n;i++) scanf("%d",&tempos[i]);
	
	/*colocando o estado incial*/
	//tempos dos operarios
	for(i = 0;i < k; i++){
		ops.opsInsumos[i] = tempos[i];
	}
	//lista de insumos
	ops.tamLI = n-k;
	for(i = k;i < n;i++){
		ops.listaLinsumos[i-k] = tempos[i];
	}
	//tempos
	int temOp[k];
	for(i = 0;i < k;i++) temOp[i] = 0;
	/*fim*/
	
	while( parada(ops.listaLinsumos,ops.opsInsumos,ops.tamLI,k) == 1){
		/*atualiza tempo*/
		for(i = 0;i < k; i++){
			if (ops.opsInsumos[i] != 0){
				ops.opsInsumos[i]--;
				temOp[i]++;
			}
		}
		/*colocando na fila*/
		for(i = 0;i < k; i++){
			/*coloca na fila devido fim do tempo*/
			if( temOp[i] == m && ops.opsInsumos[i] != 0 ){
				ops.listaLinsumos[ops.tamLI] = ops.opsInsumos[i];
				ops.tamLI++;
			}
		}
		/*colocando para os operarios*/
		aux = 0;
		for(i = 0;i < k;i++){
			//terminou peça ou atingiu o tempo maximo
			if(ops.opsInsumos[i] == 0 || temOp[i] == m){
				//coloca a nova peça para o funcionario
				ops.opsInsumos[i] = ops.listaLinsumos[0];
				atualizaLista(ops.tamLI,ops.listaLinsumos);
				ops.tamLI--;
				temOp[i] = 0;
			}
		}	
	}
	/*imprimindo aqueles que terminaram*/
	for(i = 0;i < k;i++){
		if(ops.opsInsumos[i] == 0) printf("%d ", i);
	}
}
