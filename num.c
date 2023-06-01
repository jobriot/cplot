#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "num.h"

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

double uniform_random(void) {
	return ((double)rand() / (double)RAND_MAX);
}

// to redo, using taylor would be cleaner
double erfinv(double x) {
	double tt1, tt2, lnx, sgn;
	sgn = (x < 0) ? -1.0f : 1.0f;

	x = (1 - x)*(1 + x);
	lnx = log(x);

	tt1 = 2/(M_PI*0.147) + 0.5f * lnx;
	tt2 = 1/(0.147) * lnx;

	return (sgn*sqrt(-tt1 + sqrt(tt1*tt1 - tt2)));
}

double normal_random(void) {
	return (double) sqrt(2) * erfinv(2*uniform_random() - 1);
}

BIN bin(double * x, int dimension, int nb_bins) {
	BIN toret;
	double min = x[0], max = x[0];
	for (int i=1; i<dimension; i++) {
		if (x[i] > max)
			max = x[i];
		if (x[i] < min)
			min = x[i];
	}

	toret.bins = linspace(min, max, nb_bins+1);
	toret.centered_bins = malloc(nb_bins * sizeof(double));
	toret.values = calloc(nb_bins, sizeof(double));
	for (int i=0; i<nb_bins; i++)
		toret.centered_bins[i] = (toret.bins[i] + toret.bins[i+1]) / 2.;

	for (int i=0; i<dimension; i++) {
		for (int j=1; j<nb_bins+1; j++) {
			if (x[i] <= toret.bins[j]) {
				toret.values[j-1]++;
				break;
			}
		}
	}

	toret.nb_bins = nb_bins;
	toret.nb_values = dimension;

	return toret;
}

void norm_bin(BIN * b) {
	double inter = b->bins[1] - b->bins[0];
	for (int i=0; i<b->nb_bins; i++)
		b->values[i] /= (b->nb_values * inter);
}
