#include "bibliotecas.h"
#include "funcoes.h"
#include "opsMatrixVector.h"
#include "Jacobiana.h"
#include "sistemaLU.h"
#include "matrizBroyden.h"
int main() {
    cout << "Metodo de Broyden-Sherman e Morrison" << endl;
	//vetor solucao
	vector<double> xprox(n); //x mais novo
	vector<double> xant(n); //x da iteracao passada
							//guarda solucao de sistema
	vector<double> y(n);
	//guarda
	vector<double> s(n);
	//guarda -F(x)
	vector<double> b(n);
	//cria matriz A
	double**A = new double*[n];
	for (int i = 0;i < n;i++) A[i] = new double[n];
	//recebe chute inicial
	cout << "Chute inicial" << endl;
	for (int i = 0;i < n;i++) {
		cin >> xant[i];
	}
	/*iniciando o metodo*/
	//fazendo A0 = jacobiana de x0
	montaJacobiana(xant, A);
	//monta b = F(x)
	montaMenosF(b, xant);
	//calculando a inversa de A
	A = calculaInversa(A);
	//calculando Ab
	y = multMatVec(A, b);
	//calculando novo x
	xprox = somaVetor(xant, y);
	//realizando as proximas iteracoes
	int k = 0;
	while (normaInf(b) > E && k < N && normaInf(y) > E) {
		//calcula prox matriz de Broyden
		A = montaMatrizBroydenSherman(A, xprox, xant);
		//monta menos F
		montaMenosF(b, xprox);
		//calcula Ab
		y = multMatVec(A, b);
		//atualiza vetores
		for (int i = 0; i < n;i++) {
			s[i] = xprox[i];
		}
		//proximo passo
		xprox = somaVetor(xprox, y);
		for (int i = 0;i < n;i++) {
			xant[i] = s[i];
		}
		k++;
	}
	cout << "Numero de iteracoes  " << k << endl;
	cout << "Tolerancia de " << E << " atingida" << endl;
	cout << "Vetor final solucao " << endl;
	printaVetor(xprox);
	cout << "Equacoes avaliadas em x final " << endl;
	cout << "f1 = " << F1(xprox) << " \nf2 = " << F2(xprox) << "\nf3 =  " << F3(xprox) << endl;
}
