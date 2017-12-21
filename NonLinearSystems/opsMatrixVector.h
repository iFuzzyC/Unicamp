#pragma once
#include "bibliotecas.h"
/*imprime vetor*/
void printaVetor(vector<double> x) {
	for (int i = 0;i < n;i++) {
		cout << " -> " << x[i];
	}
	cout << endl;
}
/*imprime matriz*/
void printaMatriz(double **J) {
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			cout << J[i][j] << " ";
		}
		cout << endl;
	}
}
/*soma dois vetores*/
vector<double> somaVetor(vector<double> xant, vector<double> y) {
	vector<double> xprox(n);
	for (int i = 0;i < n;i++) {
		xprox[i] = xant[i] + y[i];
	}
	return xprox;
}
/*subtrai dois vetores*/
vector<double> subtraiVetores(vector<double> xant, vector<double> y) {
	vector<double> xprox(n);
	for (int i = 0;i < n;i++) {
		xprox[i] = xant[i] - y[i];
	}
	return xprox;
}
/*calcula norma infinito de um vetor*/
double normaInf(vector<double> y) {
	double norma = abs(y[0]);
	for (int i = 1;i < n;i++) {
		if (abs(y[i]) > norma) {
			norma = abs(y[i]);
		}
	}
	return norma;
}
/*multiplica matriz e vetor*/
vector<double> multMatVec(double**A, vector<double> x) {
	vector<double> y(n);
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			y[i] = y[i] + A[i][j] * x[j];
		}
	}
	return y;
}
/*multiplica vetor e vetor para matriz*/
double** vetXvetToMat(vector<double> x, vector<double> y) {
	double**A = new double*[n];
	for (int i = 0;i < n;i++) A[i] = new double[n];
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			A[i][j] = x[i] * y[j];
		}
	}
	return A;
}
/*calcula norma dois de vetor*/
double normaDois(vector<double> x) {
	double soma = 0;
	for (int i = 0;i < n;i++) {
		soma = soma + x[i] * x[i];
	}
	return soma;
}
/*soma duas matrizes*/
double**somaMatrizes(double**A, double**B) {
	double**C = new double*[n];
	for (int i = 0;i < n;i++) C[i] = new double[n];
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	return C;
}
/*checa se matriz é identicamente nula*/
int checaNulidade(double**A) {
	const double E = 0.0001;
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			if (abs(A[i][j]) > E) return 1;
		}
	}
	return 0;
}
/*retorna matriz identidade de ordem n*/
double** criaIdentidade() {
	double**I = new double*[n];
	for (int i = 0;i<n;i++) I[i] = new double[n];

	for (int i = 0;i<n;i++) {
		for (int j = 0;j<n;j++) {
			if (i == j) I[i][j] = 1;
			else I[i][j] = 0;
		}
	}
	return I;
}
/*soma a linha j de uma matriz com a linha i da mesma*/
void somaLinhasMatrizes(const double m, const int lineI, const int lineJ, double**A) {
	for (int i = lineI; i<n; i++) {
		A[lineJ][i] = A[lineJ][i] + m*A[lineI][i];
	}
}
/*retorna a inversa de uma matriz*/
double** calculaInversa(double**A) {
	double **I = criaIdentidade();
	double m = 0;
	//calcula para triangular inferior
	for (int i = 0;i < n;i++) {
		for (int j = i + 1;j<n;j++) {
			m = -(A[j][i] / A[i][i]);
			somaLinhasMatrizes(m, i, j, A);
			somaLinhasMatrizes(m, i, j, I);
		}
	}
	//calcula para triangular superior
	for (int i = n - 1; i >= 0; i--) {
		for (int j = i - 1;j >= 0;j--) {
			m = -(A[j][i] / A[i][i]);
			somaLinhasMatrizes(m, i, j, A);
			somaLinhasMatrizes(m, i, j, I);
		}
	}
	//normaliza
	for (int i = 0;i<n;i++) {
		for (int j = 0;j < n; j++)	I[i][j] = I[i][j] / A[i][i];
		A[i][i] = A[i][i] / A[i][i];
	}
	return I;
}
/*faz produto escalar entre dois vetores*/
double vetXvetToNumber(vector<double> x, vector<double> y) {
	double soma = 0;
	for (int i = 0;i < n;i++) {
		soma = soma + x[i] * y[i];
	}
	return soma;
}
/*retorna transposta de matriz*/
double**calculaTransposta(double**A) {
	double**B = new double*[n];
	for (int i = 0;i < n;i++) B[i] = new double[n];

	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			B[i][j] = A[j][i];
		}
	}
	return B;
}