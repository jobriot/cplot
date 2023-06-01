#include <stdio.h>

struct data {
	double * x;
	double * y;
	int dimension;
	char ** gplot_args;
	int nargs;
};

typedef struct _GNUPLOT_ {
	FILE * process;
	struct data * datas;
	int nb_data;
} gnuplot;

gnuplot * instanciatePlot();
void killplot(gnuplot *);
void draw_gnuplot(gnuplot *);
void pplot(gnuplot *, double[], double[], int, char*);
void plot(gnuplot *, double[], double[], int, char*);
void scatter(gnuplot *, double[], double[], int, char*);
