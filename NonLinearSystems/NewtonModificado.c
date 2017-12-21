//Programa para Metodo de Newton Modificado
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
//prototipos para funcoes
double** criaMatriz(int N);
double F1(double x[3]);
double F2(double x[3]);
double zeraP(int N, double** P);
double Gauss(int N,double **matriz,double **P);
double Newton(double x[3],double**matriz,double**P, double E);
double SolLyF(double **P,double x[3],double y[3]);
double SolUsY(double**matriz,double s[3],double y[3]);
double Parada(double x[3],double aux[3]);
double Parada2(double x[3],double aux[3]);
//Programa principal
int main(){
    int N=2,i;
    printf("Metodo de Newton Modificado para sistemas nao lineares 2x2.\n");
    double**matriz,x[3],E,**P;
    matriz = criaMatriz(N);
    printf("Chute incial:");
    for(i=0;i<2;i++) scanf("%lf",&x[i]);
    printf("Insira a precisao aceita: ");
    scanf("%lf",&E);

    //Alocando a matriz P
    P=(double**)malloc(N*sizeof(double*));
    for (i=0; i<N; i++)
    P[i]=(double*)malloc(N*sizeof(double));
    //zerando P
    zeraP(N,P);
    //Fim da Alocacao

    //Inciando o metodo da fatoracao LU
    Gauss(N,matriz,P);
    //O metodo
    Newton(x,matriz,P,E);

}
//Recebe N, entrada: matriz. Retorna a matriz alocada.
double** criaMatriz(int N){
	double **matriz;
	int i,j;
	matriz=(double**)malloc(N*sizeof(double*));
	for (i=0; i<N; i++)
    	matriz[i]=(double*)malloc(N*sizeof(double));

//Recebendo a matriz
	printf ("Digite a Jacobiana avaliada no chute inicial:\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			scanf("%lf",&matriz[i][j]);
		}
	}
	return matriz;
}
//Retornando a equacao 1 avaliada nos pontos
double F1(double x[3]){
    double y;
    //Coloque a primeira equacao aqui
    y = 2 - 2*x[0] + pow(x[0],3) - 3*x[0]*pow(x[1],2);
    return y;
}
//Retornando a equacao 2 avaliada nos pontos
double F2(double x[3]){
    double y;
    //Coloque a segunda equacao aqui
    y = -2*x[1] + 3*pow(x[0],2)*x[1] - pow(x[1],3);
    return y;
}

//Separando a jacobiana em LU
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
double Gauss(int N,double **matriz,double **P){

    double m;
    int i=0;
    int j,k;
    for(i=0;i<N;i++){
        for(j=i+1;j<N;j++){
            m = -(matriz[j][i]/matriz[i][i]);
            P[j][i] = -m;
            for(k=i;k<N;k++) matriz[j][k] = matriz[j][k] + m*matriz[i][k];
    	}
    }
}

//Encontrando a solucao para Ly = -F
double SolLyF(double **P,double x[3],double y[3]){
  y[0] = (-1)*F1(x);
  y[1] = (-1)*F2(x) - P[1][0]*y[0];
}
//Solucao para Us = y
double SolUsY(double**matriz,double s[3],double y[3]){
    s[1] = y[1]/matriz[1][1];
    s[0] = (y[0] - matriz[0][1]*s[1])/matriz[0][0];
}

double Newton(double x[3],double**matriz,double**P, double E){
    int i;
    double aux[3],y[3],s[3],d,r;
    for(i=0;i<200;i++){
        SolLyF(P,x,y);
        SolUsY(matriz,s,y);
        d = Parada(x,aux);
        r = Parada2(x,aux);
        if( d < E) break;
        aux[0] = x[0];
        aux[1] = x[1];
        x[0] = s[0] + x[0];
        x[1] = s[1] + x[1];
    }
    printf("\nA solucao e: %f e %f",x[0],x[1]);
}

double Parada(double x[3],double aux[3]){
    double d,r;
    d = F1(x);
    if (d < 0) d = -1*d;
    r = F2(x);
    if (r<0) r = -1*r;
    if (d<r) d = r;
    return d;
}
double Parada2(double x[3],double aux[3]){
    double d,r;
    d = x[0] - aux[0];
    r = x[1] - aux[1];
    if (d<0) d = -1*d;
    if (r<0) r = -1*r;
    if (d<r) d = r;
    return d;
}

