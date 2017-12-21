#include "list.h"

/*criando lista*/
Lista *createLista(){
	Lista *temp;
	temp =  (Lista *)malloc(sizeof(Lista));
	temp->nuc = 'u';
	temp->prox = NULL;
	return temp;
}
/*recebe lista - iC recebe o char que indicara parada do input*/
void receiveListaSimples(Lista *lista, const char iC){
	int index = 1;
	char base = 'p';
	while( 1 ){
		base = getchar();
		if ( index == 1 && base == iC) base = getchar();
		if ( base == iC) break;
		else insereListaSimples(base, lista);
		index++;
	}
}
/*recebendo o valor a ser incluido na lista*/
void insereListaSimples(const char value, Lista *lista){
	Lista *temp, *aux;
	aux = lista;
	while (aux->prox != NULL) aux = aux->prox;
	
	aux->prox = (Lista *)malloc(sizeof(Lista));
	
	temp = aux->prox;
	temp->nuc = value;
	temp->prox = NULL;
}
/*cria a lista complementar do DNA*/
void complementaDNA(Lista *dna, Lista *compDna){
	Lista *temp;
	temp = dna;
	while(temp != NULL){
		switch(temp->nuc){
			case 'a':
				insereListaSimples('t',compDna);
				break;
			case 't':
				insereListaSimples('a',compDna);
				break;
			case 'c':
				insereListaSimples('g',compDna);
				break;
			case 'g':
				insereListaSimples('c',compDna);
				break;
		}
		temp = temp->prox;
	}	
}
/*retorna o tamanho da lista*/
int tamanhoLista(Lista *lista){
	int i = 0;
	Lista *temp;
	temp = lista->prox;
	while(temp != NULL){
		i++;
		temp = temp->prox;
	}
	return i;
}
/*confere a sequencia*/
int confereSeq(Lista *dna, Lista *seq, Lista *original){
	Lista *temp;
	temp = dna;
	while( seq != NULL ){
		if (dna == NULL) dna = original->prox;
		else if ( seq->nuc != dna->nuc) return 0;
		dna = dna->prox;
		seq = seq->prox;
	}
	return 1;
}
/*encontra o indice onde o corte deve ser feito*/
int buscaCorte(Lista *dna, Lista *rDna, const int corte, const int dnaTam){
	Lista *auxD, *auxR, *temp;
	auxD = dna->prox;
	auxR = rDna->prox;
	
	char iC = auxR->nuc;
	
	int aTrue = 0;
	
	int i = 0;
	while(auxD != NULL ){
		temp = auxD;
		//encontrou char inicial igual
		if ( temp->nuc == iC ){
			aTrue = confereSeq(temp, auxR, dna);
			auxR = rDna->prox;
		}
		if (aTrue == 1){
			if( i + corte > dnaTam) return (i + corte) - dnaTam;
			else return i + corte;
		}
		auxD = auxD->prox;
		i++;
	}
	return -1;
}
/*cria a parte um da sequencia dividida*/
void fazListaUm(Lista *dnapUm, Lista *dna, const int dnaCorte){
	int i = 0;
	Lista *temp;
	//ha no cabeça
	temp = dna -> prox;;
	while(i < dnaCorte ){
		insereListaSimples(temp->nuc,dnapUm);
		temp = temp->prox;
		i++;
	}
}
/*cria a parte dois da sequencia dividida*/
void fazListaDois(Lista *dnapDois, Lista *dna, const int dnaCorte){
	int i = 0;
	Lista *temp;
	temp = dna ->prox;
	while( i < dnaCorte){
		temp = temp->prox;
		i++;
	}
	while( temp != NULL ){
		insereListaSimples(temp->nuc, dnapDois);
		dnapDois = dnapDois->prox;
		temp = temp->prox;
	}
}

/*imprime a lista simples*/
void imprimeListaSimples(Lista *p){
	Lista *temp;
	temp = p->prox;
	while(temp!=NULL){
		printf("%c",temp->nuc);
		temp = temp->prox;
	}
}
/*ajuda a inverter uma lista*/
Lista *ajudaInverter(Lista *iSeq, const char iC){
	Lista *temp = (Lista *)malloc(sizeof(Lista));
	temp->nuc = iC;
	temp->prox = iSeq;
	return temp;
}
/*inverte uma lista*/
Lista *inverteSeq(Lista *seq){
	Lista *temp, *invSeq;
	invSeq = NULL;
	temp = seq ->prox;
	
	while( temp != NULL ){
		invSeq = ajudaInverter(invSeq, temp->nuc);
		temp = temp->prox;
	}	
	return invSeq;
}
/*deletando elemento adjacente a direita*/
void delAdjListaUm(Lista *lista){
	Lista *temp, *aux;
	temp = lista->prox;
	aux = lista;
	while(temp->prox != NULL) {
		temp = temp->prox;
		aux = aux->prox;
	}
	aux->prox = NULL;
}
/*deletando adjacentes a esquerda*/
void delAdjListaDois(Lista *lista){
	Lista *aux;
	aux = lista->prox;
	aux = aux ->prox;
	lista ->prox = aux;
}
/*junta duas listas*/
Lista *juntaLista(Lista *listaUm, Lista *listaDois){
	Lista *temp, *aux;
	temp = listaUm;
	aux = listaDois->prox;
	while( aux != NULL ){
		insereListaSimples(aux->nuc,temp);
		aux = aux->prox;
	}
	return temp;
}

/*confere a sequencia*/
int confereBase(Lista *lista, Lista *base){
	Lista *temp;
	temp = lista;
	while( base != NULL ){
		if (lista == NULL) return 0;
		else if ( base->nuc != lista->nuc) return 0;
		lista = lista->prox;
		base = base->prox;
	}
	return 1;
}
/*procura uma sequencia e devolve sua primeira posicao*/
int procuraBase(Lista *lista, Lista *base){
	Lista *temp, *aux;
	temp = lista;
	aux = base->prox;
	
	int aTrue = 0;
	char first = temp->nuc, second = aux->nuc;
	if (first == second){
		//printf("\n\n -- %c  %c",first, second);
		aTrue = confereBase(temp,aux);
	}
	else{
		return -1;
	}
	
	if ( aTrue == 1) return 1;
	else return -1;
	
}

/*cria um no cabeca para lista simples de int*/
Index *createIndex(){
	Index *temp;
	temp = (Index *)malloc(sizeof(Index));
	temp->index = -1;
	temp->prox = NULL;
	return temp;
}
/*insere elemento na lista simples de ints*/
void insereIndice(Index *v, const int N){
	Index *temp;
	temp = v;
	while(temp->prox != NULL) temp = temp->prox;
	temp->prox = (Index *)malloc(sizeof(Index));
	
	temp = temp->prox;
	temp->index = N;
	temp->prox = NULL;
}
/*imprime lista simples de ints*/
void printInts(Index *v){
	Index *temp;
	temp = v->prox;
	while(temp != NULL){
		printf("%d ",temp->index);
		temp = temp->prox;
	}
}
/*ordena de forma crescente uma lista simples de ints*/
void ordenaListaInts(Index *v){
	Index *temp, *aux, *swap = createIndex();
	temp = v->prox;
	aux = temp->prox;
	while( aux != NULL){
		temp = aux ->prox;
		while( temp != NULL ){
			if ( aux->index > temp->index){
				swap->index = temp->index;
				temp->index = aux->index;
				aux->index = swap->index;
			}
			temp = temp->prox;
		}
		aux = aux->prox;
	}
}




