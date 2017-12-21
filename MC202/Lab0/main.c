#include <stdio.h>
#include <stdlib.h>
#include "oper.h"


int main(){

	/*recebendo o char*/
	char operation;
	scanf("%c",&operation);
	//recebendo dimensoes da matriz A
	int lA,cA;
	scanf("%d",&lA);
	scanf("%d",&cA);
	//alocando a matriz A
	int **A = AlocaMatriz(lA,cA);
	//recebe a matriz A
	recebeMatriz(A,lA,cA);
	//imprime a matriz A
	//printMatriz(A,lA,cA);

	//verificando se precisa de matriz B
	int lB,cB;
	int **B;
	if (operation == 'a' || operation == 'm'){
        //recebe dimensoes de B
        scanf("%d",&lB);
        scanf("%d",&cB);
        //alocando B
        B = AlocaMatriz(lB,cB);
        recebeMatriz(B,lB,cB);
        //printMatriz(B,lB,cB);
	}

	//verificando que tipo de operacao fazer
	int **C;
    int lC, cC;
	switch(operation){
    //caso de soma
    case 'a':
        //possivel dimensao da matriz
        lC = lA; cC = cA;
        //recebendo a matriz
        C = soma(A,lA,cA,B,lB,cB);
        break;
    case 'm':
        //possivel dimensao da matriz
        lC = lA; cC = cB;
        //recebendo a matriz
        C = multiplicacao(A,lA,cA,B,lB,cB);
        break;
    case 't':
        //dimensao da matriz
        lC = cA; cC = lA;
        //recebendo a matriz
        C = transposta(A,lA,cA);
        break;
    case 's':
        ponto_sela(A,lA,cA,&lC,&cC);
        if ( lC != -1) printf("%d %d",lC,cC);
        else printf("NE");
        return 0;
        break;
	}

	//imprimindo a matriz
	if(C == NULL){
        printf("NE");
	}
	else{
        printMatriz(C,lC,cC);
	}

}
