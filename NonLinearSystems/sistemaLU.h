#pragma once
#include "bibliotecas.h"

/*encontra o pivo parcial da iteracao*/
void encontraPivo(double **U, vector<double> &b, const int line) {
	double aux;
	//procura por pivo
	for (int j = line;j < n;j++) {
		if (U[line][line] < U[j][line]) {
			//troca linhas
			for (int k = 0;k < n;k++) {
				aux = U[line][k];
				U[line][k] = U[j][k];
				U[j][k] = aux;
			}
			//troca no vetor b
			aux = b[line];
			b[line] = b[j];
			b[j] = aux;
		}
	}
}
/*resolve o sistema triangular inferior Ly = b*/
void resolveLyb(double **L, vector<double> b, vector<double> &y) {
	double soma = 0;
	y[0] = b[0];
	for (int i = 1;i < n;i++) {
		for (int k = 0;k < n - 1;k++) {
			soma = soma + L[i][k] * y[k];
		}
		y[i] = b[i] - soma;
		soma = 0;
	}
}
/*resolve o sistema triangular superior Ux = y*/
void resolveUxy(double **U, vector<double> y, vector<double> &x) {
	double soma = 0;
	x[n - 1] = y[n - 1] / U[n - 1][n - 1];
	for (int i = n - 2;i >= 0;i--) {
		for (int j = i + 1;j <= n - 1;j++) {
			soma = soma + U[i][j] * x[j];
		}
		x[i] = (y[i] - soma) / U[i][i];
		soma = 0;
	}
}
/*resolve sistema linear*/
void resolveSistemaLinear(double **J, vector<double> b, vector<double> &y) {
	//criando novo vetor de b - 
	vector<double> duploB(b);
	//prepara U
	double **U = new double*[n];
	for (int i = 0;i < n;i++) U[i] = new double[n];
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) U[i][j] = J[i][j];
	}
	//prepara L
	double**L = new double*[n];
	for (int i = 0;i < n;i++) L[i] = new double[n];
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) L[i][j] = 0;
	}
	//fator multiplicador
	double m;
	//eliminacao de gauss
	for (int i = 0;i < n;i++) {
		encontraPivo(U, duploB, i);
		for (int j = i + 1;j < n;j++) {
			m = -(U[j][i] / U[i][i]);
			L[j][i] = -m;
			for (int k = i;k < n;k++) {
				U[j][k] = U[j][k] + m*U[i][k];
			}
		}
	}
	//solucao Lz = duploB
	vector<double> z(n);
	resolveLyb(L, duploB, z);
	//resolve Uy = z
	resolveUxy(U, z, y);
}
