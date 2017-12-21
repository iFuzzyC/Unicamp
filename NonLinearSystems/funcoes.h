#pragma once
#include "bibliotecas.h"
/*funcoes*/
double F1(vector<double> x) {
	double y = 3 * x[0] - cos(x[1] * x[2]) - 0.5;
	return y;
}
double F2(vector<double> x) {
	double y = x[0] * x[0] - 625 * x[1] * x[1] - 0.25;
	return y;
}
double F3(vector<double> x) {
	double y = exp(-x[0] * x[1]) + 20 * x[2] + (10 * pi - 3) / 3;
	return y;
}
/*derivadas parciais*/
double f1x1(vector<double> x) {
	return 3;
}
double f1x2(vector<double> x) {
	double y = x[2] * sin(x[1] * x[2]);
	return y;
}
double f1x3(vector<double> x) {
	double y = x[1] * sin(x[1] * x[2]);
	return y;
}
double f2x1(vector<double> x) {
	return 2 * x[0];
}
double f2x2(vector<double> x) {
	return (-1250)*x[1];
}
double f2x3(vector<double> x) {
	return 0;
}
double f3x1(vector<double> x) {
	double y = (-x[1])*exp(-x[0] * x[1]);
	return y;
}
double f3x2(vector<double> x) {
	double y = (-x[0])*exp(-x[0] * x[1]);
	return y;
}
double f3x3(vector<double> x) {
	return 20;
}
