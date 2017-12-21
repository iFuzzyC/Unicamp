//Metodo de Gauss-Jacobi para resolucao de sistema linear
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//Prototipos de funcoes
double**criaMatriz(int N);
void CalC(int N,double**A,double**C);
void Imprime(int N,double** matriz);
void Calg(int N,double**A,double b[N],double g[N]);
void Jacobi(int N,double**C,double g[N],double X[N],double E);
double Erro(int N, double X[N],double Y[N]);
//Programa principal
int main(){
    int N,i;
    printf("Metodo de Gauss-Seidel:\n");
    printf("Insira a ordem da Matriz:");
    scanf("%d",&N);
    double**A,X[N],b[N],**C,g[N],E;
    //Alocando e criando as matrizes necessarias
    C=(double**)malloc(N*sizeof(double*));
    for (i=0; i<N; i++)
    C[i]=(double*)malloc(N*sizeof(double));
    A = criaMatriz(N);
    //Recebendo os valores das constante
    printf("Insira os valores das constantes em ordem de linha:");
    for (i=0;i<N;i++) scanf("%lf",&b[i]);
    //Calculando C e g
    CalC(N,A,C);
    Calg(N,A,b,g);
    //Imprimindo as matrizes
    printf("\nA matriz C e:\n");
    Imprime(N,C);
    printf("\nA matriz g transposta e:\n");
    for(i=0;i<N;i++) printf("%.2f\t",g[i]);
    //Recebendo as aproximacoes iniciais
    printf("\nInsira agora as aproximacoes iniciais de X1 a Xn:\n");
    for(i=0;i<N;i++) scanf("%lf",&X[i]);
    printf("Insira o erro aceito: ");
    scanf("%lf",&E);
    //Iniciando o metodo
    Jacobi(N,C,g,X,E);
    printf("\nA solucao do sistema de X1 a Xn e:\n");
    for(i=0;i<N;i++) printf("%f\t",X[i]);
    printf("\n");
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
//Calculando a matriz C
void CalC(int N,double**A,double**C){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(j==i) C[i][j] = 0;
            else C[i][j] = -A[i][j]/A[i][i];
        }
    }
}
//Imprimindo a matriz
void Imprime(int N,double** matriz){
	int i,j;
	//Imprimir a matriz
	for(i=0 ; i<N; i++){
		for(j=0;j<N;j++){
            printf("%.2f\t",matriz[i][j]);
		}
		printf("\n");
	}
}
 //Calculando o vetor g
 void Calg(int N,double**A,double b[N],double g[N]){
    int i=0;
    for(i=0;i<N;i++) g[i] = b[i]/A[i][i];
 }
//Calculando o vetor solucao
void Jacobi(int N,double**C,double g[N],double X[N],double E){
    int i,j,k;
    double soma=0,Dr,Y[N];
    for(k=0;k<100;k++){
        for(i=0;i<N;i++) Y[i] = X[i];//Guardando os valores antigos de X;
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                soma = soma + C[i][j]*X[j];
        }
            X[i] = soma + g[i];
            soma = 0;
    }
    Dr = Erro(N,X,Y);
    if (E>Dr) break;
    }
}
//Calculando a precisao da iteracao
double Erro(int N, double X[N],double Y[N]){
    int i;
    double MaiorD=0, MaiorX=0, Dr, Sub,aux=0;
    for(i=0;i<N;i++){
        Sub = X[i] - Y[i];
        if (Sub<0) Sub = Sub*(-1);
        if (MaiorD<Sub) MaiorD = Sub;
        aux = X[i];
        if (aux<0) aux = aux*(-1);
        if (MaiorX<aux) MaiorX = aux;
    }
    Dr = MaiorD/MaiorX;
    return Dr;
}
