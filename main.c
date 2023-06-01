#include <stdlib.h>
#include <math.h>
#include "plot.h"
#include "num.h"

double nor(double x) {
	return 3 * normal_cr(x);
}
double nor2(double x) {
	return 2 * normal_cr(x);
}

double cons(double x) {
	return 2;
}

int main(void) {
	int dimr = 50;

	double * xr = linspace(-3, 3, dimr);
	double * yr = apply_func(xr, dimr, normal_cr);

	gnuplot * plt = instanciatePlot();

	plot(plt, xr, yr, dimr, "title 'gauss' dt 2 lc 'red' lw 2");

	// wrong use of apply_func, the pointer should be freed, no way to do it here
	pplot(plt, xr, apply_func(xr, dimr, nor), dimr, "title 'cgauss' pointtype 7 lc 6");
	plot(plt, xr, apply_func(xr, dimr, nor2), dimr, "title 'rgauss'");

	free(xr);
	free(yr);

	int d = 500;
	int b = 20;
	double * no = malloc(d * sizeof(double));
	for (int i=0; i<d; i++)
		no[i] = normal_random();
	BIN nob = bin(no, d, b);
	norm_bin(&nob);
	// scatter(plt, nob.centered_bins, nob.values, nob.nb_bins, "title 'test' with boxes fill solid boxwidth 0.2");
	// scatter(plt, nob.centered_bins, nob.values, nob.nb_bins, "title 'normal random' with boxes");
	bar(plt, nob.centered_bins, nob.values, nob.nb_bins, "title 'normal random'");


	double * xu = malloc(d * sizeof(double));
	double * yu = malloc(d * sizeof(double));
	for (int i=0; i<d; i++) {
		xu[i] = 2 + normal_random() / 4;
		yu[i] = 1.5 + normal_random() / 4;
	}
	scatter(plt, xu, yu, d, "title 'scattered normal random' pointtype 6 lc 9");


	draw_gnuplot(plt);
	killplot(plt);
	return 0;
}
