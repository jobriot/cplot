#include <stdlib.h>
#include <math.h>
#include "plot.h"
#include "num.h"

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
	plot(plt, xr, yr, dimr, "title 'gauss'");
	free(xr);
	free(yr);
	draw_gnuplot(plt);
	killplot(plt);
	return 0;
}
