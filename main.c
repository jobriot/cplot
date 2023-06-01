#include <math.h>
#include "plot.h"

int main(void) {
	double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	double y[5] = {5.0 ,3.0, 5.0, 3.0, 5.0};
	double y2[5] = {3.0 ,5.0, 3.0, 5.0, 3.0};
	int dim = 5;

	double x2[100];
	double y3[100];
	// should make a linspace function
	for (int i=0; i<100; i++) {
		x2[i] = (i/100.0) * 2 * 3.14;
		y3[i] = sin(x2[i]);
	}

	gnuplot * plt = instanciatePlot();

	plot(plt, x, y, dim, "title 'W' pointtype 7 dt 2 lw 6");
	scatter(plt, x, y2, dim, "title 'M'");
	plot(plt, x2, y3, 100, "title 'sin'");
	draw_gnuplot(plt);
	killplot(plt);
	return 0;
}
