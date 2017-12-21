//Vamos escrever codigo para qualquer funcao
//Metodo da Bisseccao
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Prototipo para funcoes
double Precisao(int E);
int NumeroIteracoes (double a, double b, int E);
double Fx(double x);
double Bisseccao(double a, double b, int E);
//Programa Principal
//Insira sua funcao nao funcao Fx
int main(){
	double a, b, raiz;
	int E;
	//Recebendo o intervalo e a precisao. Tenha certeza que f(a)f(b)<0
	printf("Metodo da Bisseccao para uma funcao qualquer previamente dada\n");
	printf("\nInsira os extremos do intervalo [a,b] que contem a raiz e a precisao 10^-E:\n");
	printf("a = ");
	scanf("%lf",&a);
	printf("b = ");
	scanf("%lf",&b);
	printf("E = ");
	scanf("%d",&E);
	printf("O intervalo e [%.2f,%.2f] com precisao 10^-%d",a,b,E);

	//Acionando o Metodo
	raiz = Bisseccao(a,b,E);
	printf("\n==>Raiz aproximada e: %.5f",raiz);
}

//Calculando 10^-E
double Precisao(int E){
	int i;
	double P=1.000;
	for (i = 0; i<E; i++){
		P = P/10;
	}
	return P;
}

//Escrevendo a funcao para Numero de Iteracoes
int NumeroIteracoes (double a, double b, int E){
	int k = 0;
	double aux;
	double sub;
	sub = b - a;
	aux = log(sub);
	sub = Precisao(E);
	aux = aux - log(sub);
	aux = aux/log(2);
	for ( k=0; k<aux ; k++);
	return k;
}

//Calculando a funcao no ponto
double Fx(double x){
	double y;
	//INSIRA AQUI A FUNCAO EM X
	y = -pow(x,3) + 6*pow(x,2) + 11*x + 6;
	//
	return y;
}

double Bisseccao(double a, double b, int E){
	int k,i;
	double P,fx,fa,fb,x;
	//Ativando outras funcoes
	k = NumeroIteracoes(a,b,E);
	P = Precisao(E);
	//Calculando a raiz
	for ( i=0; i<=k;i++){
		x = (a + b)/2;
		fx = Fx(x);
		fa = Fx(a);
		fb = Fx(b);
		if ( fa<0 && fb>0){
			if( fx<0 ) a = x;
			else if( fx>0 ) b = x;
		}
		else if ( fa>0 && fb<0 ){
			if ( fx<0 ) b = x;
			else if ( fx>0 ) a = x;
		}
		else if ( ( b-a)<P ) break;
	}
	return x;
}

