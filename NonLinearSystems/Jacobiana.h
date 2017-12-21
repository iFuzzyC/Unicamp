#pragma once
#include "bibliotecas.h"
#include "funcoes.h"
/*monta a matriz jacobiana*/
void montaJacobiana(vector<double> x, double **J) {
	J[0][0] = f1x1(x); J[0][1] = f1x2(x); J[0][2] = f1x3(x);
	J[1][0] = f2x1(x); J[1][1] = f2x2(x); J[1][2] = f2x3(x);
	J[2][0] = f3x1(x); J[2][1] = f3x2(x); J[2][2] = f3x3(x);
}
/*monta o vetor -F*/
void montaMenosF(vector<double> &b, vector<double> x) {
	b[0] = -F1(x);
	b[1] = -F2(x);
	b[2] = -F3(x);
}

