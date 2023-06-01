#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "plot.h"

gnuplot * instanciatePlot() {
	gnuplot * ret = (gnuplot *) malloc(sizeof(gnuplot));
	ret->process = popen("gnuplot -persistent 2>/dev/null", "w");
	ret->datas = malloc(0);
	ret->nb_data = 0;
	
	return ret; 
}
void killplot(gnuplot * plt) {
	pclose(plt->process);
	for (int i=0; i<plt->nb_data; i++) {
		free(plt->datas[i].x);
		free(plt->datas[i].y);
		for (int j=0; j<plt->datas[i].nargs; j++) {
			free(plt->datas[i].gplot_args[j]);
		}
		free(plt->datas[i].gplot_args);
	}
	free(plt->datas);
	free(plt);
}


// commands :
// array A[3]
// A[1]=1
// ...
// plot sample [i=1:3] '+' using (B[i]):(A[i]) with linespoints title "testing tester", [i=1:3] '+' using (A[i]):(B[i]) with linespoints title "tester testing"

void set_margins(gnuplot * plt) {
	double xmax = plt->datas[0].x[0];
	double xmin = plt->datas[0].x[0];
	double ymax = plt->datas[0].y[0];
	double ymin = plt->datas[0].y[0];

	// should be done when the points are initialized, but lazyness...
	for (int i=0; i<plt->nb_data; i++) {
		for (int j=0; j<plt->datas[i].dimension; j++) {
			if (plt->datas[i].x[j] > xmax) xmax = plt->datas[i].x[j];
			if (plt->datas[i].x[j] < xmin) xmin = plt->datas[i].x[j];
			if (plt->datas[i].y[j] > ymax) ymax = plt->datas[i].y[j];
			if (plt->datas[i].y[j] < ymin) ymin = plt->datas[i].y[j];
		}
	}
	double margin_x = (xmax - xmin) * (5 / 100.);
	double margin_y = (ymax - ymin) * (5 / 100.);
	fprintf(plt->process, "set xr [%f:%f]\n", xmin - margin_x, xmax + margin_x);
	fprintf(plt->process, "set yr [%f:%f]\n", ymin - margin_y, ymax + margin_y);
}

void concat_args(char ** dest, char ** source, int nsource) {
	char * sep = " ";
	*dest = (char*) malloc(sizeof(char));
	strcpy(*dest, "");
	for (int i=0; i<nsource; i++) {
		*dest = (char*) realloc(*dest, (strlen(*dest) + strlen(source[i]) + 1) * sizeof(char));
		strcat(*dest, source[i]);
		if (i < nsource - 1) {
			*dest = (char*) realloc(*dest, (strlen(*dest) + strlen(sep) + 1) * sizeof(char));
			strcat(*dest, sep);
		}
	}
}

void add_arg(struct data * source, char * arg) {
	int n = ++source->nargs;
	source->gplot_args = realloc(source->gplot_args, n * sizeof(char*));
	source->gplot_args[n-1] = malloc((strlen(arg) + 1) * sizeof(char));
	strcpy(source->gplot_args[n-1], arg);
}

void draw_gnuplot(gnuplot * plt) {
	char * beg = "plot sample ";
	char * sep = ", ";
	char * stri;
	stri = (char*) malloc((strlen(beg) + 1) * sizeof(char));
	strcpy(stri, beg);
	for (int i=0; i<plt->nb_data; i++) {
		int di = plt->datas[i].dimension;
		fprintf(plt->process, "array %c[%d]\n", 'a' + i, di);
		fprintf(plt->process, "array %c[%d]\n", 'A' + i, di);
		for (int j=0; j<di; j++) {
			fprintf(plt->process, "%c[%d]=%f\n", 'a' + i, j + 1, plt->datas[i].x[j]);
			fprintf(plt->process, "%c[%d]=%f\n", 'A' + i, j + 1, plt->datas[i].y[j]);
		}
		char * tocat;
		char * argus;
		concat_args(&argus, plt->datas[i].gplot_args, plt->datas[i].nargs);
		if (0 > asprintf(
				&tocat,
				"[i=1:%d] '+' using (%c[i]):(%c[i]) %s",
				di,
				'a' + i,
				'A' + i,
				argus)
			)
			return;
		stri = (char*) realloc(stri, (strlen(stri) + strlen(tocat) + 1) * sizeof(char));
		strcat(stri, tocat);
		free(tocat);
		if (i < plt->nb_data - 1) {
			stri = (char*) realloc(stri, (strlen(stri) + strlen(sep) + 1) * sizeof(char));
			strcat(stri, sep);
		}

	}
	set_margins(plt);
	// fprintf(plt->process, "set style fill solid\n");
	fprintf(plt->process, "%s\n", stri);
	free(stri);
}

void pplot(gnuplot * plt, double xvals[], double yvals[], int dimension, char * args) {
	scatter(plt, xvals, yvals, dimension, args);
	add_arg(&(plt->datas[plt->nb_data-1]), "with linespoints");
}

void plot(gnuplot * plt, double xvals[], double yvals[], int dimension, char * args) {
	scatter(plt, xvals, yvals, dimension, args);
	add_arg(&(plt->datas[plt->nb_data-1]), "with lines");
}

void scatter(gnuplot * plt, double xvals[], double yvals[], int dimension, char * args) {
	int n = ++plt->nb_data;
	plt->datas = (struct data*) realloc(plt->datas, n * sizeof(struct data));
	// plt->datas[n-1] = (struct data*) malloc(sizeof(struct data*));
	plt->datas[n-1].dimension = dimension;
	plt->datas[n-1].x = malloc(dimension * sizeof(double));
	plt->datas[n-1].y = malloc(dimension * sizeof(double));
	for (int i=0; i<dimension; i++) {
		plt->datas[n-1].y[i] = yvals[i];
		plt->datas[n-1].x[i] = xvals[i];
	}
	plt->datas[n-1].nargs = 0;
	plt->datas[n-1].gplot_args = (char**) malloc(0);
	add_arg(&(plt->datas[n-1]), args);
}

void bar(gnuplot * plt, double xvals[], double yvals[], int dimension, char * args) {
	scatter(plt, xvals, yvals, dimension, args);
	add_arg(&(plt->datas[plt->nb_data-1]), "with boxes");
}
