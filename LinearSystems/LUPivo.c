//Resolvendo sistemas lineares pela fatoracao LU
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//Prototipos de funcoes
void Imprime(int N,double** matriz);
double** criaMatriz(int N);
double Gauss(int N,double **matriz,double **P,double b[N]);
double zeraP(int N,double** P);
double SolLyb(int N,double **P,double b[N],double y[N]);
void ImprimeSol(int N, double y[N]);
double SolUxy(int N, double **matriz,double y[N],double X[N]);
double Pivo(int N, double**matriz,double b[N],int i);
//Programa principal -- P sera L e matriz sera U
int main(){
    int N;
    int i,j;
    printf("\nFatoracao LU com Pivoteamento\nPor favor, tenha certeza de inserir um sistema SPD.\n");
    printf("Insira a ordem da Matriz dos Coeficientes A: ");
    scanf("%d",&N);
    double **matriz,b[N],X[N],**P,y[N];
    matriz = criaMatriz(N);

    //Alocando a matriz P
    P=(double**)malloc(N*sizeof(double*));
    for (i=0; i<N; i++)
    P[i]=(double*)malloc(N*sizeof(double));
    //zerando P
    zeraP(N,P);
    //Fim da Alocacao

    //Recebendo os valores das constante
    printf("Insira os valores das constantes em ordem de linha:");
    for (i=0;i<N;i++) scanf("%lf",&b[i]);

    //Iniciando o metodo
    Gauss(N,matriz,P,b);
    //Imprimindo as matrizes
    printf("\nA matriz L e:\n");
    Imprime(N,P);
    printf("\nA matriz U e:\n");
    Imprime(N,matriz);
    //Encontrando as solucoes
    SolLyb(N,P,b,y);
    printf("\nA solucao de Ly = b e:\n");
    ImprimeSol(N,y);
    printf("\nA solucao do sistema, solucao de Ux = y, e:\n");
    SolUxy(N,matriz,y,X);
    ImprimeSol(N,X);
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
//zerando P
double zeraP(int N, double** P){
    int i, j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if ( j==i ) P[i][j]=1;
            else P[i][j]=0;
        }
    }
}
//Iniciando o metodo da Eliminaçao de Gauss
double Gauss(int N,double **matriz,double **P,double b[N]){

    double m;
    int i=0;
    int j,k;
    for(i=0;i<N;i++){
        Pivo(N,matriz,b,i);
        for(j=i+1;j<N;j++){
            m = -(matriz[j][i]/matriz[i][i]);
            P[j][i] = -m;
            for(k=i;k<N;k++) matriz[j][k] = matriz[j][k] + m*matriz[i][k];
    }
    }
    }
//Encontrando a solucao para Ly = b
double SolLyb(int N,double **P,double b[N],double y[N]){
    double soma=0;
    int i,j=0,k;
    y[0] = b[0];
    for(i=1;i<N;i++){
            for(k=0;k<N-1;k++){
                soma = soma + P[i][k]*y[k];
            }
        y[i] = b[i] - soma;
        soma = 0;
    }
}
//Imprimindo as solucoes
void ImprimeSol(int N, double y[N]){
    int i;
    for(i=0;i<N;i++){
        printf("%.2f\t",y[i]);
    }
}
//Encontrando a solucao para Ux = y
double SolUxy(int N, double **matriz,double y[N],double X[N]){
        int i,j;
        double Soma =0;
        X[N-1] = y[N-1]/matriz[N-1][N-1];
        for(i=N-2;i>=0;i--){
            for(j=i+1;j<=N-1;j++){
                Soma = Soma + matriz[i][j]*X[j];
            }
            X[i] = (y[i] - Soma)/matriz[i][i];
            Soma = 0;
        }
}


//Neste caso veremos apenas a primeira coluna
double Pivo(int N, double**matriz,double b[N],int i){
    int j,k;
    double aux,aux1;
        for(j=i;j<N;j++){
            if ( matriz[i][i]<matriz[j][i]){
                //Trocando as linhas
                for(k=0;k<N;k++){
                    aux = matriz[i][k];
                    matriz[i][k] = matriz[j][k];
                    matriz[j][k] = aux;
                }
                //Trocando as constantes
                aux1 = b[i];
                b[i] = b[j];
                b[j] = aux1;
            }
        }
    }

