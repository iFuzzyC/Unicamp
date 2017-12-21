//Metodo de Eliminacao de Gauss
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//Prototipo para funcoes
double** criaMatriz(int N);
void Imprime(int N,double **matriz,double b[N]);
double Gauss(int N,double **matriz,double b[N]);
double Solucao(int N,double** matriz,double b[N],double X[N]);
//Programa principal
int main(){
    int N;
    int i,j;
    printf("\nMetodo de Eliminacao de Gauss\nPor favor, tenha certeza de inserir um sistema SPD.\n");
    printf("Insira a ordem da Matriz dos Coeficientes A: ");
    scanf("%d",&N);
    double **matriz,b[N],X[N];
    matriz = criaMatriz(N);
    //Recebendo os valores das constante
    printf("Insira os valores das constantes em ordem de linha:");
    for (i=0;i<N;i++) scanf("%lf",&b[i]);

    printf("O sistema linear dado foi:\n");
    Imprime(N,matriz,b);

    //Iniciando o metodo
    Gauss(N,matriz,b);
    printf("O novo sistema e:\n");
    Imprime(N,matriz,b);
    //Achando a solucao para o novo sistema
    Solucao(N,matriz,b,X);
    printf("\nA solucao para essa equacao e:\n");
    for(i=0;i<N;i++) printf("X%d = %.2f\n",i,X[i]);
}


//Recebe N, entrada: matriz. Retorna a matriz alocada.
double** criaMatriz(int N){
	double **matriz;
	int i,j;
matriz=(double**)malloc(N*sizeof(double*));
for (i=0; i<N; i++)
    matriz[i]=(double*)malloc(N*sizeof(double));

//Recebendo a matriz
	printf ("Digite os valores:\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			scanf("%lf",&matriz[i][j]);
		}
	}
	return matriz;
}
//Imprimindo a matriz
void Imprime(int N,double** matriz,double b[N]){
	int i,j;
	//Imprimir a matriz
	for(i=0 ; i<N; i++){
		for(j=0;j<N;j++){
            printf("%.2f*X%d ",matriz[i][j],j);
		}
		printf("= %.2f",b[i]);
		printf("\n");
	}
}
//Iniciando o metodo da Eliminaçao de Gauss
double Gauss(int N,double **matriz,double b[N]){

    double m;
    int i=0;
    int j,k;
    for(i=0;i<N;i++){
        for(j=i+1;j<N;j++){
            m = -(matriz[j][i]/matriz[i][i]);
            b[j] = b[j] + m*b[i];
            for(k=i;k<N;k++) matriz[j][k] = matriz[j][k] + m*matriz[i][k];
    	}
    }
}
double Solucao(int N,double** matriz,double b[N],double X[N]){
        int i,j;
        double Soma =0;
        X[N-1] = b[N-1]/matriz[N-1][N-1];
        for(i=N-2;i>=0;i--){
            for(j=i+1;j<=N-1;j++){
                Soma = Soma + matriz[i][j]*X[j];
            }
            X[i] = (b[i] - Soma)/matriz[i][i];
            Soma = 0;
        }
}
