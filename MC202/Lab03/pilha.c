#include "pilha.h"

/*aloca espaco para ponteira de Pilha*/
Pilha *createPilha(){
	Pilha *p =(Pilha *)malloc(sizeof(Pilha));
	p->prox = NULL;
	return p;	
}
/*recebe o labirinto*/
void receiveMaze(Pilha *maze, const int rows, const int colunms){
	Pilha *temp;
	temp = maze;
	char C;
	int i = 0, j = 0;
	
	while (i < rows ){
		for(j = 0;j<colunms; j++){
			C = getchar();
			if (C == '\n') C = getchar();
			inserePilha(temp, j, C);
		}
		temp->prox = createPilha();
		temp = temp->prox;
		i++;
	}	
}
/*insere um elemento no vetor de Pilha*/
void inserePilha(Pilha *ap, const int indice, const char C){
	ap->vLinhas[indice] = C;
}
/*imprime o labirinto*/
void printMaze(Pilha *ap, const int rows, const int colunms){
	Pilha *temp;
	temp = ap;
	int i = 0, j = 0;
	while( i < rows ){
		for(j = 0;j < colunms;j++){
			if (temp->vLinhas[j] == 'a') printf("-");
			else printf("%c",temp->vLinhas[j]);
		}
		printf("\n");
		temp = temp->prox;
		i++;
	}
}
/*encontra as coordenadas onde esta o char em questao*/
void achaCoordenadaLetra(Coordenadas *pos, Pilha *maze, const int rows, const int colunms, const char letra){
	Pilha *aux;
	aux = maze;
	int i = 0, j = 0;
	for( i = 0;i < rows;i++){
		for( j = 0;j < colunms;j++){
			if ( aux->vLinhas[j] == letra){
				pos->eixoX = j;
				pos->eixoY = i;
				return;
			}
		}
		aux = aux->prox;
	}
}
/*funcao que percorre o labirinto em busca do caminho de s ate e*/
void andaNoMaze(Pilha *maze, Coordenadas *start, Coordenadas *end, const int rows, const int colunms){
	//variaveis que irao guardar linhas importantes
	Pilha *lab, *labPrev, *labNext;
	lab = maze;
	int i = 0;
	//variavel que ira guardar a posicao que estamos
	Coordenadas myPos;
	myPos.eixoX = start->eixoX;
	myPos.eixoY = start->eixoY;
	/*indo para a posicao inicial*/
	for( i = 0;i < start->eixoY; i++){
		//guardamos a linha anterior
		labPrev = lab;
		//linha em que estamos
		lab = lab->prox;
	}
	//guardamos a proxima linha
	labNext = lab->prox;

	
	while( 1 ){
		//anda para a direita
		if ( lab->vLinhas[myPos.eixoX + 1] == '-' ){
			atualizaPosicao(&myPos, 1, 0,'x',lab);
		}
		//anda para a esquerda
		else if( lab->vLinhas[myPos.eixoX - 1] == '-'){
			atualizaPosicao(&myPos, -1, 0, 'x', lab);
		}
		//anda para cima
		else if (labPrev->vLinhas[myPos.eixoX] == '-'){
			atualizaPosicao(&myPos, 0, -1, 'x',lab);
			lab = labPrev;
			labNext = lab->prox;
			i = 0;
			labPrev = maze;
			for(i = 0;i < myPos.eixoY; i++) labPrev = labPrev->prox;
		}
		//anda para baixo
		else if (labNext->vLinhas[myPos.eixoX] == '-'){
			atualizaPosicao(&myPos, 0, 1, 'x', lab);
			labPrev = lab;
			lab = lab->prox;
			labNext = lab->prox;
		}
		else{
			/*checamos se chegamos ao ponto final*/
			if ( checaFim(lab, labPrev, labNext, &myPos) == 'e' ){
				atualizaPosicao(&myPos, 0,0, 'x',lab);
				printMaze(maze, rows, colunms);
				return;
			}
			/*chegamos a uma parte em que nao ha como continuar, logo voltamos uma casa*/
			else{
				if ( lab->vLinhas[myPos.eixoX + 1] == 'x' || lab->vLinhas[myPos.eixoX + 1] == 's' ){
				atualizaPosicao(&myPos, 1, 0,'a',lab);
				}
				//anda para a esquerda
				else if( lab->vLinhas[myPos.eixoX - 1] == 'x' || lab->vLinhas[myPos.eixoX - 1] == 's'){
				atualizaPosicao(&myPos, -1, 0, 'a', lab);
				}
				//anda para cima
				else if (labPrev->vLinhas[myPos.eixoX] == 'x' || labPrev->vLinhas[myPos.eixoX] == 's'){
				atualizaPosicao(&myPos, 0, -1, 'a',lab);
				lab = labPrev;
				labNext = lab->prox;
				i = 0;
				labPrev = maze;
				for(i = 0;i < myPos.eixoY; i++) labPrev = labPrev->prox;
				}
				//anda para baixo
				else if (labNext->vLinhas[myPos.eixoX] == 'x' || labNext->vLinhas[myPos.eixoX] == 's'){
				atualizaPosicao(&myPos, 0, 1, 'a', lab);
				labPrev = lab;
				lab = lab->prox;
				labNext = lab->prox;
				}	
			}
			/*checa se ainda temos caminho para seguir*/
			//neste caso o caminho voltou para a posicao inicial e agora checamos se ainda ha caminhos para seguir
			//se nao houve paramos de executar
			if ( checaS(lab,labPrev,labNext, &myPos) == 1){
				printf("NE");
				return;
			}
		}
	}
	
}
/*atualiza a posicao em que estou e coloca o char certo*/
void atualizaPosicao(Coordenadas *pos, const int moveX, const int moveY, const char letra, Pilha *line){
	if (line->vLinhas[pos->eixoX] == 's'){
		pos->eixoX = pos->eixoX + moveX;
		pos->eixoY = pos->eixoY + moveY;
	}
	else{
		line->vLinhas[pos->eixoX] = letra;
		pos->eixoX = pos->eixoX + moveX;
		pos->eixoY = pos->eixoY + moveY;
	}	
}
/*checa se chegamos a um fim do algoritmo*/
char checaFim(Pilha *lab, Pilha *labPrev, Pilha *labNext, Coordenadas *pos){
		//checa para a direita
		if ( lab->vLinhas[pos->eixoX + 1] == 'e' ){
			return lab->vLinhas[pos->eixoX + 1];
		}
		//checa para a esquerda
		else if( lab->vLinhas[pos->eixoX - 1] == 'e'){
			return lab->vLinhas[pos->eixoX - 1];
		}
		//checa para cima
		else if (labPrev->vLinhas[pos->eixoX] == 'e'){
			return labPrev->vLinhas[pos->eixoX];
		}
		//checa para baixo
		else if (labNext->vLinhas[pos->eixoX] == 'e'){
			return labNext->vLinhas[pos->eixoX];
		}
		else{
			return 'o';
		}
}
/*checa se ainda tem caminhos para seguir - retorna 0 se tem, 1 caso nao tenha*/
int checaS(Pilha *lab, Pilha *labPrev, Pilha *labNext, Coordenadas *myPos){
	if ( lab->vLinhas[myPos->eixoX] == 's'){
		if ( lab->vLinhas[myPos->eixoX + 1] == '-' ){
			return 0;
		}
		else if ( lab->vLinhas[myPos->eixoX - 1] == '-'){
			return 0;
		}
		else if (labPrev->vLinhas[myPos->eixoX] == '-'){
			return 0;
		}
		else if (labNext->vLinhas[myPos->eixoX] == '-'){
			return 0;
		}
		else{
			return 1;
		}
	}
	else{
		return 0;
	}
}

