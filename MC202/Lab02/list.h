#include <stdio.h>


/* struct que define uma lista simples com char */
typedef struct SinglyLinkedList{
    char nuc;
    struct SinglyLinkedList *prox;
}Lista;

/*recebe lista - iC recebe o char que indicara parada do input*/
void receiveListaSimples(Lista *lista, const char iC);
/*recebendo o valor a ser incluido na lista*/
void insereListaSimples(const char value, Lista *dna);
/*cria a lista complementar do DNA*/
void complementaDNA(Lista *dna, Lista *compDna);
/*retorna o tamanho da lista simples*/
int tamanhoLista(Lista *lista);
/*cria no cabeca para lista simples*/
Lista *createLista();
/*confere a sequencia, se ambas forem iguais, entao retorna 1, caso contrario retorna 0 - contem loop para dna (retorna ao comeco - original - quando acaba)*/
int confereSeq(Lista *dna, Lista *seq, Lista *original);
/*retorna o indice onde o corte deve ser feito*/
int buscaCorte(Lista *dna, Lista *rDna, const int corte, const int dnaTam);
/*cria a parte um da sequencia dividida - parte da esquerda*/
void fazListaUm(Lista *dnapUm, Lista *dna, const int dnaCorte);
/*cria a parte dois da sequencia dividida - parte a direita*/
void fazListaDois(Lista *dnapDois, Lista *dna, const int dnaCorte);
/*imprime a lista simples de chars*/
void imprimeListaSimples(Lista *p);
/*inverte uma lista simples*/
Lista *inverteSeq(Lista *seq);
/*ajuda a inverter uma lista*/
Lista *ajudaInverter(Lista *iSeq, const char iC);
/*deletando elemento adjacente a direita*/
void delAdjListaUm(Lista *lista);
/*deletando adjacentes a esquerda*/
void delAdjListaDois(Lista *lista);
/*junta duas listas simples*/
Lista *juntaLista(Lista *listaUm, Lista *listaDois);
/*confere a sequencia, se ambas forem iguais retorna 1, caso contrario 0 - nao contem loop*/
int confereBase(Lista *lista, Lista *base);
/*procura uma sequencia e devolve sua primeira posicao onde a sequencia, neste caso base, ocorre em lista*/
int procuraBase(Lista *lista, Lista *base);

/*struct que define uma lista simples com int para guardar os indices a serem impressos*/
typedef struct indices{
	int index;
	struct indices *prox;
}Index;
/*cria um no cabeca para lista simples de int*/
Index *createIndex();
/*insere elemento na lista simples de ints*/
void insereIndice(Index *v, const int N);
/*imprime lista simples de ints*/
void printInts(Index *v);
/*ordena de forma crescente uma lista simples de ints*/
void ordenaListaInts(Index *v);




