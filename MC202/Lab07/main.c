#include "pqueue.h"

//estrutura ue ira guardar a ordem e o nome das pessoas com os pedidos ja processados
typedef struct listaNomes{
	char nomeCl[200];
}ListasNomes;
//recebe a fila de prioridade e realiza os processos possiveis no mes - retorna posicao do ultimo elemento em ListasNomes
int processosDoMes(Fila *pr, ListasNomes *lista, const int k,const int n, int bgLista){
	//variaveis
	int soma = 0, i = 0, j = 0, firstMes = 0;
	//encontra e realiza o primeiro processo para o mes
	for(i = 0;i < n;i++){
		if(pr[i].processado == 0){
			firstMes = i;
			pr[i].processado = 1;
			for(j = 0; pr[i].pessoa->name[j] != '\0'; j++){
				lista[bgLista].nomeCl[j] = pr[i].pessoa->name[j];
			}
			lista[bgLista].nomeCl[j] = '\0';
			soma = pr[i].pessoa->quantia;
			bgLista++;
			break;
		}
	}
	//checa e realiza processos que ainda podem ser processados no mes, devido que a quantia maxima nao foi atingida	
	for(i = firstMes;i < n; i++){
		//checa se pode processar o proximo cliente
		if(i + 1 < n){
			if( pr[i+1].pessoa->quantia + soma > k){
				return bgLista;
			}
		}
		else if(pr[i].processado == 0 && pr[i].pessoa->mes == pr[firstMes].pessoa->mes){
			if(soma + pr[i].pessoa->quantia <= k){
				soma = soma + pr[i].pessoa->quantia;
				pr[i].processado = 1;
				for(j = 0; pr[i].pessoa->name[j] != '\0'; j++){
					lista[bgLista].nomeCl[j] = pr[i].pessoa->name[j];
				}
				lista[bgLista].nomeCl[j] = '\0';
				bgLista++;
			}
		}
	}
	return bgLista;
}

int main(){
	//declarando variaveis
	Nomes *people = NULL;
	int n, qMes = 11, k;
	//recebendo quantidade e valor maximo
	scanf("%d %d",&n, &k);
	//criando e alocando espaco para a fila de prioridade
	Request *pedido;
	Fila *pr = (Fila*)malloc(n*sizeof(Fila));
	int i;
	for(i = 0;i < n;i++){
		pr[i].pessoa = (Request*)malloc(sizeof(Request));
	}
	//recebendo as requisicoes
	for(i = 0;i < n;i++){
		pedido = recebePedido();
		people = ordemPrioridade(pedido,pr, i+1, people);
	}
	//printaFila(pr,n);
	//recebendo as atualizacoes de tarifas
	ListasNomes *nomesProntos = (ListasNomes*)malloc(n*sizeof(ListasNomes));
	int atlFlag = 0, j =0, q = 0;
	char flagNome[200];
	//faz os processos do mes
	for(i = 0;i < qMes + 1;i++){
		//processa o mes
		q = processosDoMes(pr, nomesProntos, k,n, q);
		//checagem se alguem ira pagar a taxa
		if(i > 0){
			//recebe quantos vao pagar
			scanf("%d", &atlFlag);
			if (atlFlag > 0 ){
				//recebendo os nomes
				for(j = 0; j < atlFlag;j++){
					scanf("%s",flagNome);
					//atualizando a fila de prioridade
					atualizaFlag(flagNome, pr, people, n);
				}
			}
		}
	}
	//termina os processos ainda nao processados
	for(i = qMes +1 ; i < n;i++){
		q = processosDoMes(pr, nomesProntos, k,n, q);
	}
	//imprime a ordem em que os processos foram feitos
	for(i = 0;i< n;i++){
		printf("\n%s",nomesProntos[i].nomeCl);
	}

}
