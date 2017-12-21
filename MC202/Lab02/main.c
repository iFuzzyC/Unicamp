#include <stdio.h>
#include "list.h"


int main(){
	
	/*criando a lista que ira receber e guardar o dna*/
	Lista *dna = createLista();
	//recebendo o dna
	receiveListaSimples(dna,'\n');
	/*criando a lista complementar*/
	Lista *compDna = createLista();
	complementaDNA(dna,compDna);
	
	/*recebendo sequencia a ser econtrada*/
	Lista *rDna = createLista();
	receiveListaSimples(rDna, ' ');
	/*recebendo a posicao de corte*/
	int corte;
	scanf("%d",&corte);
	/*recebendo se o adjacente sera deletado*/
	int delAdj;
	scanf("%d",&delAdj);
	/*recebendo a sequencia que devera ser procurada ao final*/
	Lista *base = createLista();
	receiveListaSimples(base,'\n');
	
	/*recebendo o tamanho do DNA e da sequencia*/
	int dnaTam = tamanhoLista(dna);
	int rdnaTam = tamanhoLista(rDna);
	
	/*criando duas listas do DNA, usadas apos o corte no DNA*/
	Lista *dnapUm = createLista();
	Lista *dnapDois = createLista();
	//encontrando o indice de corte no dna
	int dnaCorte = buscaCorte(dna,rDna,corte, dnaTam);
	//separando o DNA em duas listas
	fazListaUm(dnapUm, dna, dnaCorte);
	fazListaDois(dnapDois, dna, dnaCorte);
	
	
	
	/*criando duas lista do compDna, usadas apos o corte no complemento do DNA*/
	Lista *compUm = createLista();
	Lista *compDois = createLista();
	//invertendo rDna para procurar a partir do comeco em compDna
	Lista *rDnaInverse = createLista();
	rDnaInverse->prox = inverteSeq(rDna);
	//encontrando indice do corte no compDna (complemento do dna)
	int compdnaCorte = buscaCorte(compDna,rDnaInverse, rdnaTam - corte, dnaTam);
	//separando o complemento em duas listas
	fazListaUm(compUm, compDna, compdnaCorte);
	fazListaDois(compDois, compDna, compdnaCorte);
	
	/*Deletando os adjacentes - se necessario*/
	if ( delAdj == 1 ){
		//fazendo para aqueles de listaUm
		delAdjListaUm(dnapUm);
		delAdjListaUm(compUm);
		//fazendo para aqueles da listaDois
		delAdjListaDois(dnapDois);
		delAdjListaDois(compDois);
	}
	
	/*recebendo tamanho das listas*/
	int tamDnapUm = tamanhoLista(dnapUm);
	int tamDnapDois = tamanhoLista(dnapDois);
	int tamCompUm = tamanhoLista(compUm);
	int tamCompDois = tamanhoLista(compDois);
	/*juntando listas da forma correta - dnapDois com dnapUm e  compDois com compUm*/
	Lista *seqUm, *seqDois;
	seqUm = juntaLista(dnapDois, dnapUm);
	seqDois = juntaLista(compDois, compUm);
	/*definindo os limites superiores e inferiores, ou seja, onde e possivel ficar a base nitrogenada*/
	int limInf, limSup, limTotal;
	if ( tamDnapDois >= tamCompDois ){
		limInf = tamDnapDois - tamCompDois + 1;
		limSup = tamanhoLista(seqUm);
		limTotal = tamDnapDois + tamCompUm;
	}
	else {
		limInf = tamCompUm + tamDnapDois + 1;
		limSup = tamanhoLista(seqUm);
		limTotal  = tamDnapUm + tamCompDois;
	}
	limInf = limInf - 1;
	limSup = limSup - 1;
	limTotal = limTotal -1;
	
	//recebendo o tamanho da base
	int tamBase = tamanhoLista(base);
	
	/*criando um variavel que ira guardar os indices dos cortes finais*/
	Index *valores = createIndex();
	//variavies auxiliares - conta guarda en qual nucleotideo do dna estamos
	int Num, conta = 0;
	//procurando na cadeia de cima
	seqUm = seqUm->prox;
	//enviamos para procuraBase o nucleotideo de seqUm->nuc e verificamos se e o mesmo que o primeiro de base->nuc
	//caso seja, entao verificamos o resto, se ainda for verdade, entao verificamos se a posicao e valida
	//caso ainda seja verdade, entao guardamos o indice na lista de valores
	while(seqUm != NULL){
		Num = procuraBase(seqUm, base);
		//printf(" ---Num %d",Num);
		if( Num > -1 && conta >= limInf && conta + (tamBase-1) <= limSup){
			//printf("aqui");
			insereIndice(valores,conta);
		}
		seqUm = seqUm->prox;
		conta++;
	}
	//zerando conta
	conta = 0;
	//invertendo a seqDois para procurar na direcao correta e fazendo para seqDois o mesmo que para seqUm
	Lista *seqDoisIv = createLista();
	seqDoisIv -> prox = inverteSeq(seqDois);
	seqDoisIv = seqDoisIv->prox;
	int aux = 0;
	while(seqDoisIv != NULL){
		Num = procuraBase(seqDoisIv, base);
		aux = tamanhoLista(seqDois) - conta - tamBase + 1;
		aux = limTotal - tamanhoLista(seqDois) + aux;
		if( Num > -1 && aux + tamBase - 1 <= limSup){
			insereIndice(valores, aux);
		}
		seqDoisIv = seqDoisIv->prox;
		conta++;
	}
	//se a lista dos indices estiver vazia imprimimos NE
	if (valores -> prox == NULL) printf("NE");
	//se conter valores, os imprimimos
	else{
		ordenaListaInts(valores);
		printInts(valores);
	}
	
}
