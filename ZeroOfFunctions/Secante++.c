//Metodo da Secante para um funcao qualquer
#include <stdio.h>
#include <math.h>

//Prototipos de funcoes
double Precisao(int E);
double Fx(double);
double Secante(double x0, double x1, int E1, int E2);
//programa principal
int main(){
	double x0,x1, raiz;
	int E1,E2;
	printf("Metodo da Secante para uma funcao qualquer previamente dada.\n");
	printf("Aproximacoes iniciais:\n");
	printf("x0 = ");
	scanf("%lf",&x0);
	printf("x1 = ");
	scanf("%lf",&x1);
	printf("Insira agora as precisoes iniciais - 10^-E:\n");
	printf("E1 = ");
	scanf("%d",&E1);
	printf("E2 = ");
	scanf("%d",&E2);

	//Iniciando o metodo
	raiz = Secante(x0,x1,E1,E2);
	printf("\n==>A raiz aproximada e: %f",raiz);
}

//Calculando 10^-E:
double Precisao(int E){
	double P=1.000;
	int i;
	for (i=0;i<E;i++) P = P/10;
	return P;
}

//Calculando a funcao no ponto
double Fx(double x){
	double y;
	//INISIRA A FUNCAO AQUI
	y =  exp(-pow(x,2)) - 0.5*pow(x,2);
	//
	return y;
}

//Calculando a raiz
double Secante(double x0,double x1, int E1, int E2){
	double P1, P2, fx0, fx1, aux;
	int i;

	P1 = Precisao(E1);
	P2 = Precisao(E2);

	for(i=0;i<200;i++){
		aux = x1;
		fx0 = Fx(x0);
		fx1 = Fx(x1);
		x1 = x1 - ((x1 - x0)*fx1)/(fx1 - fx0);
		fx1 = Fx(x1);
		x0 = aux;
		if ( fx1<0 ) fx1 = fx1*(-1);
		if ( fx1<P1 ) break;
	}
	return x1;
}
