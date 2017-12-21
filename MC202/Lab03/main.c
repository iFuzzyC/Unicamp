#include "pilha.h"


int main(){
	
	/*recebendo o tamanho do labirinto*/
	int rows, colunms;
	scanf("%d %d ",&rows,&colunms);
	/*criando a variavel do maze*/
	Pilha *maze = createPilha();
	/*recebendo o labirinto*/
	receiveMaze(maze, rows,colunms);
	
	/*encontrando onde esta o inicio e o fim*/
	Coordenadas inicioS, fimE;
	achaCoordenadaLetra(&inicioS, maze, rows, colunms, 's');
	achaCoordenadaLetra(&fimE, maze, rows, colunms, 'e');
	
	/*encontrando o caminho*/
	andaNoMaze(maze, &inicioS, &fimE, rows, colunms);
	
}
