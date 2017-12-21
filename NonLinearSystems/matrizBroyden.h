#pragma once
#include "bibliotecas.h"
#include "opsMatrixVector.h"
#include "Jacobiana.h"
double** montaMatrizBroyden(double **A, vector<double> xprox, vector<double> xant) {
	double**B = new double*[n];
	for (int i = 0;i < n;i++) B[i] = new double[n];
	vector<double> bprox(n);
	vector<double> bant(n);
	//calcula F1 e F0
	montaMenosF(bprox, xprox);
	for (int i = 0;i < n;i++) bprox[i] = bprox[i] * (-1);
	montaMenosF(bant, xant);
	//
	vector<double> y(n);
	vector<double> s(n);
	vector<double> t(n);
	//x1 - x0
	s = subtraiVetores(xprox, xant);
	//A0s
	t = multMatVec(A, s);
	//F1 - F0 - t
	y = somaVetor(bprox, bant);
	y = subtraiVetores(y, t);
	//norma dois
	double normaDoisX = normaDois(s);
	//divide y pela normaDois
	for (int i = 0;i < n;i++) y[i] = y[i] / normaDoisX;
	//faz matriz y*s^t
	B = vetXvetToMat(y, s);
	//soma A com B
	A = somaMatrizes(A, B);
	return A;
}

double** montaMatrizBroydenSherman(double**A, vector<double> xprox, vector<double> xant) {
	double**B = new double*[n];
	for (int i = 0;i < n;i++) B[i] = new double[n];
	vector<double> bprox(n);
	vector<double> bant(n);
	//calcula F1 e F0
	montaMenosF(bprox, xprox);
	for (int i = 0;i < n;i++) bprox[i] = bprox[i] * (-1);
	montaMenosF(bant, xant);
	//
	vector<double> y(n);
	vector<double> s(n);
	vector<double> t(n);
	//x1 - x0
	s = multMatVec(A, bant);
	//F1 - F0 - t
	y = somaVetor(bprox, bant);
	y = multMatVec(A, y);
	for (int i = 0;i < n;i++) y[i] = y[i] * (-1);
	//calcula p = -s^ty
	double p = (-1)*vetXvetToNumber(y, s);
	//calcula tranposta
	B = calculaTransposta(A);
	//calcula t = Bs
	t = multMatVec(B, s);
	//calcul s+y
	y = somaVetor(s, y);
	for (int i = 0;i < n;i++) y[i] = y[i] / p;
	B = vetXvetToMat(y, t);
	//soma A com B
	A = somaMatrizes(A, B);
	return A;
}