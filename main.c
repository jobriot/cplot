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

int main(void) {
	double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	double y[5] = {5.0 ,3.0, 5.0, 3.0, 5.0};
	double y2[5] = {3.0 ,5.0, 3.0, 5.0, 3.0};
	int dim = 5;

	int dimr = 50;

	double * xr = linspace(-3, 3, dimr);
	double * yr = apply_func(xr, dimr, normal_cr);

	gnuplot * plt = instanciatePlot();

	// plot(plt, x, y, dim, "title 'W' pointtype 7 dt 2 lw 6");
	// scatter(plt, x, y2, dim, "title 'M'");
	// pplot(plt, xr, yr, dimr, "title 'gauss' pointtype 7");
	plot(plt, xr, yr, dimr, "title 'gauss' dt 2 lc 'red' lw 2");

	// wrong use of apply_func, the pointer should be freed, no way to do it here
	pplot(plt, xr, apply_func(xr, dimr, nor), dimr, "title 'cgauss' pointtype 7 lc 6");
	plot(plt, xr, apply_func(xr, dimr, nor2), dimr, "title 'rgauss'");

	free(xr);
	free(yr);
	draw_gnuplot(plt);
	killplot(plt);
	return 0;
}
