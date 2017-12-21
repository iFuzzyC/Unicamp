#include <stdio.h>
/*estrutura que ira guardar as linhas do labirinto*/
typedef struct Pilha {
	char vLinhas[200];
	struct Pilha *prox;
}Pilha;
/*estrutura que guarda coordenadas de um ponto no labirinto*/
typedef struct Coordenadas{
	//coluna
	int eixoX;
	//linha
	int eixoY;
}Coordenadas;
//aloca espaco para variavel apontador do tipo Pilha
Pilha *createPilha();
//recebe o labirinto do usuario
void receiveMaze(Pilha *maze, const int rows, const int colunms);
//insere um elemento em um vetor de pilha
void inserePilha(Pilha *ap, const int indice, const char C);
//imprime o labirinto
void printMaze(Pilha *ap, const int rows, const int colunms);
//encontrada em quais coordenadas X e Y uma letra em questao se encontra no labirinto
void achaCoordenadaLetra(Coordenadas *pos, Pilha *maze, const int rows, const int colunms, const char letra);
//funcao que percorre o labirinto em busca de um caminho
void andaNoMaze(Pilha *maze, Coordenadas *start, Coordenadas *end, const int rows, const int colunms);
//funcao que atualiza a posicao que estamos no labirinto apos movermos
void atualizaPosicao(Coordenadas *pos, const int moveX, const int moveY, const char letra, Pilha *line);
//checa se atingimos 'e', ou seja, se antigimos o fim do percurso
char checaFim(Pilha *line, Pilha *prevLine, Pilha *nextLine, Coordenadas *pos);
//checa se estamos na posicao inicial e se ha caminhos para seguir, caso nao houve retorna 1 e o programa para, caso houve retorna 0 e o programa continua
int checaS(Pilha *lab, Pilha *labPrev, Pilha *labNext, Coordenadas *myPos);
