#include "funcoes.h"
#include "opsMatrixVector.h"
#include "sistemaLU.h"
#include "Jacobiana.h"

/*funcao principal*/
int main() {
    cout << "Metodo de Newton" << endl;
	vector<double> x(n);
	vector<double> b(n);
	vector<double> y(n);
	//cria jacobiana
	double **J = new double*[n];
	for (int i = 0;i < n;i++) J[i] = new double[n];
	//recebendo chute inicial
	cout << "Chute Inicial" << endl;
	for (int i = 0;i < n;i++) {
		cin >> x[i];
	}
	/*faz a primeira iteracao para iniciar vetores*/
	montaJacobiana(x, J);
	montaMenosF(b, x);
	resolveSistemaLinear(J, b, y);
	x = somaVetor(x, y);
	/*termina primeiro iteracao*/
	int k = 0;

	while (k < N && normaInf(y) > E && normaInf(b) > E) {
		montaJacobiana(x, J);
		montaMenosF(b, x);
		resolveSistemaLinear(J, b, y);
		x = somaVetor(x, y);
		k++;
	}
	cout << "Numero de iteracoes  " << k << endl;
	cout << "Tolerancia de " << E << " atingida" << endl;
	cout << "Vetor final solucao " << endl;
	printaVetor(x);
	cout << "Equacoes avaliadas em x final " << endl;
	cout << "f1 = " << F1(x) << " \nf2 = " << F2(x) << "\nf3 =  " << F3(x) << endl;

}

