//Metodo de Newton para uma funcao qualquer
#include <stdio.h>
#include <math.h>

//Prototipos para funcoes
double Precisao(int E);
double Fx(double x);
double DFx(double x);
double Newton(double x, int E1, int E2);
//Programa principal
int main(){
	double x, raiz;
	int E1, E2;
	//Recebendo os dados iniciais
	printf("Metodo de Newton para uma funcao qualquer previamente dada.\n");
	printf("Estimativa inicial para a raiz:");
	scanf("%lf",&x);
	printf("Precisao E1:");
	scanf("%d",&E1);
	printf("Precisao E2:");
	scanf("%d",&E2);

	//Iniciando o metodo
	raiz = Newton(x,E1,E2);
	printf("\n ==>A raiz aproximada e: %f",raiz);

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

//Calculando a funcao no ponto
double Fx(double x){
	double y;
	//INSIRA A FUNCAO AQUI
	y = exp(-pow(x,2)) - 0.5*pow(x,2) ;
	//
	return y;
}

//Calculando a derivada no ponto
double DFx(double x){
	double dy;
	//INSIRA A DERIVADA AQUI
	dy = -2*x*exp(-pow(x,2)) -x;
	//
	return dy;
}

//Iniciando o metodo
double Newton(double x, int E1, int E2){
	double x0, P1,P2, fx, dfx;
	int i;

	P1 = Precisao(E1);
	P2 = Precisao(E2);
	for(i=0;i<200;i++){
		x0 = x;
		fx = Fx(x);
		dfx = DFx(x);
		x = x - (fx/dfx);
		fx = Fx(x);
		x0 = x - x0;
		if ( fx<0 ) fx = fx*(-1);
		else if ( x0<0 ) x0 = x0*(-1);
		if ( fx<P1 ) break;
	}
	return x;
}
