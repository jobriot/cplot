#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

double * linspace(double start, double end, int num) {
	double * toret = malloc(num * sizeof(double));
	for (int i=0; i<num; i++)
		toret[i] = start + i*((end - start)/(num-1));
	return toret;
}

double * apply_func(double * x, int dim, double func()) {
	double * toret = malloc(dim * sizeof(double));
	for (int i=0; i<dim; i++)
		toret[i] = func(x[i]);
	return toret;
}

double normal(double x, double mu, double sigma) {
	return (1/(sigma*sqrt(2*M_PI)))*exp(-(1/2.)*(pow(x-mu, 2)/pow(sigma, 2)));
}

double normal_cr(double x) {
	return normal(x, 0, 1);
}
