#include "pqueue.h"

//printa a fila
void printaFila(Fila *p, const int n){
	int i;
	for(i = 0;i < n;i++){
		printf("\n%s %d %d %d - %d",p[i].pessoa->name,p[i].pessoa->mes,p[i].pessoa->flag,p[i].pessoa->quantia,p[i].prioridade);
	}
}
//checa se o novo pedido tem prioridade sobre um ja existente
int checaPrioridade(Request *novo, Request *velho){
	if(novo->mes > velho->mes){
		return 0;
	}
	else if(novo->mes < velho->mes){
		return 1;
	}
	else{
		if(novo->flag > velho->flag){
			return 1;
		}
		else if(novo->flag < velho->flag){
			return 0;
		}
		else{
			if (novo->quantia < velho->quantia){
				return 1;
			}
			else{
				return 0;
			}
		}
		
	}
}
//insere novo pedido na posicao certa da fila
void insereFila(Fila *pr, Request *pedido, const int pos, const int max, Nomes *people){
	//aloca espaco para o novo cliente
	pr[max-1].pessoa = (Request*)malloc(sizeof(Request));
	
	int i;
	//atualizando pedidos antigos
	for(i = max-1; i > pos ; i--){
		pr[i].pessoa = pr[i-1].pessoa;
		pr[i].processado = pr[i-1].processado;
		pr[i].prioridade = i;
		//atualiza a prioridade na arvore
		atualizaPos(pr[i].pessoa->name,people,i);
	}
	//insirindo novo pedido
	pr[pos].pessoa = pedido;
	pr[pos].prioridade = pos;
	pr[pos].processado = 0;
	//insere nome na arvore
	people = insereNome(pedido->name,people,pos);
}
//encontra o local onde o novo pedido deve ser colocado
Nomes *ordemPrioridade(Request *pedido, Fila *pr, const int max, Nomes *people){
	int i;
	if( max > 1 ){
		for(i = 0;i < max; i++){
			//pedido tem prioridade maior
			if (checaPrioridade(pedido, pr[i].pessoa) == 1){
				insereFila(pr, pedido, i,max, people);
				return;
			}
		}
		//pedido com prioridade menor
		pr[max-1].pessoa = pedido;
		pr[max-1].prioridade = max-1;
		pr[max-1].processado = 0;
		people = insereNome(pedido->name,people,max-1);
	}
	else{
		//primeiro pedido
		pr[max-1].pessoa = pedido;
		pr[max-1].prioridade = max-1;
		pr[max-1].processado = 0;
		people = insereNome(pedido->name,people,max-1);
		//printaPreOrdem(people);
	}
	return people;
}
//remove cliente
void removeCliente(Fila *pr, Nomes *people, const int pos,const int max){
	int i;
	//remove o cliente na posicao pos
	for(i = pos; i < max - 1;i++){
		pr[i].pessoa = pr[i+1].pessoa;
		pr[i].processado = pr[i+1].processado;
		pr[i].prioridade = i;
		atualizaPos(pr[i].pessoa->name, people, i);
	}
}
//atualiza prioridade do cliente
void atualizaClientePosicao(Request *pedido, Fila *pr, const int max, Nomes *people){
	int i;
	if( max > 1 ){
		for(i = 0;i < max; i++){
			//pedido tem prioridade maior
			if (checaPrioridade(pedido, pr[i].pessoa) == 1){
				insereFila(pr, pedido, i,max, people);
				return;
			}
		}
		//pedido com prioridade menor
		pr[max-1].pessoa = pedido;
		pr[max-1].prioridade = max-1;
		pr[max-1].processado = 0;
		atualizaPos(pr[max-1].pessoa->name, people, max-1);
	}
	else{
		//primeiro pedido
		pr[max-1].pessoa = pedido;
		pr[max-1].prioridade = max-1;
		pr[max-1].processado = 0;
		atualizaPos(pr[max-1].pessoa->name, people, max-1);
		//printaPreOrdem(people);
	}
}
//atualiza o flag do cliente
void atualizaFlag(char flagNome[], Fila *pr, Nomes *people,const int max){
	int achaPos = devolvePos(flagNome, people);
	Request *cliente;
	//ja pagou a taxa
	if(pr[achaPos].pessoa->flag > 0 || pr[achaPos].processado > 0){
		return;
	}
	//nao pagou a taxa
	else{
		//salva o cliente
		cliente = salvaDadosCliente(pr[achaPos].pessoa->name,pr[achaPos].pessoa->mes,pr[achaPos].pessoa->quantia, 1);
		//remove o cliente
		removeCliente(pr, people, achaPos, max);
		//insere de novo o cliente - a ultima posicao da fila esta errada
		atualizaClientePosicao(cliente,pr,max,people);
	}
}


