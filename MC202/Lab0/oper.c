#include <stdio.h>
#include <stdlib.h>
int**AlocaMatriz(int linhas, int colunas){
	int i=0;
	int **Matriz = (int**)malloc(linhas*sizeof(int*));
	for (i = 0; i < linhas; i++) {
		Matriz[i] = (int*)malloc(colunas*sizeof(int));
	}
	return Matriz;
}

void printMatriz(int **Matriz, int linhas, int colunas){
	int i = 0,j=0;
	for(i = 0;i<linhas;i++){
		for(j=0;j<colunas;j++){
			printf("%d ",Matriz[i][j]);
		}
		printf("\n");
	}

}

void recebeMatriz(int**Matriz,int linhas,int colunas){
	int i=0,j=0;
	for(i = 0;i<linhas;i++){
		for(j=0;j<colunas;j++){
			scanf("%d",&Matriz[i][j]);
		}
	}
}

int **soma(int **A, int l_A, int c_A, int **B, int l_B, int c_B){
    //caso em que a soma nao e possivel
    if ( l_A != l_B || c_A != c_B) return NULL;

    //caso em que a soma e possivel
    int **Soma = AlocaMatriz(l_A,c_A);

    int i=0,j=0;
    for(i=0;i<l_A;i++){
        for(j=0;j<c_A;j++){
            Soma[i][j] = A[i][j] + B[i][j];
        }
    }
    return Soma;
}

void zeraMatriz(int**Matriz,int linhas, int colunas){
    int i=0,j=0;
    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            Matriz[i][j] = 0;
        }
    }

}

int **multiplicacao(int **A, int l_A, int c_A, int **B, int l_B, int c_B){
    //caso em que a multiplicacao nao e possivel
    if ( c_A != l_B) return NULL;
    //caso em que a multiplicacao e possivel
    int **Mult = AlocaMatriz(l_A,c_B);
    zeraMatriz(Mult,l_A,c_B);
    int i=0,j=0,p=0,elemento = 0;
    for(i=0;i<l_A;i++){
        for(j=0;j<c_B;j++){
            elemento = 0;
            for(p=0;p<c_A;p++){
                elemento = elemento + A[i][p]*B[p][j];
            }
            Mult[i][j] = elemento;
        }
    }
    return Mult;
}

int **transposta(int ** A, int l_A, int c_A){
    int i=0,j=0;
    int **transp = AlocaMatriz(c_A,l_A);
    for(i=0;i<c_A;i++){
        for(j=0;j<l_A;j++){
            transp[i][j] = A[j][i];
        }
    }
    return transp;
}

void ponto_sela(int **A, int l_A, int c_A, int *linha, int *coluna){
    int testeMaior = 1;//verdade por definicao
    int i=0,j=0;
    const int max = 99999999;
    int mElemento = max;
    //temos que analisar todas linhas
    for(i=0;i<l_A;i++){
        mElemento = max;
        //guarda o menor elemento da linha i - andamos nas colunas
        for(j=0;j<c_A;j++){
            if ( A[i][j] < mElemento ){
                mElemento = A[i][j];
                *coluna = j;
                *linha = i;
            }
        }
        //verifica se o menor elemento da linha i e o maior elemento da coluna j - andamos nas linhas
        testeMaior = 1;
        for(j=0;j<l_A;j++){
            if ( A[j][*coluna] > mElemento && A[j][*coluna] != mElemento){
                *linha = -1;
                *coluna = -1;
                testeMaior = 0;
            }
        }
        //verifica o resultado
        if ( testeMaior == 1 ){
            //printf("%d %d",*linha,*coluna);
            return;
        }
    }
    //printf("NE");
    return;
}
