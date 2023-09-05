#ifndef NUMH
#define NUMH

double * linspace(double, double, int);
double * apply_func(double *, int, double ());
double normal(double, double, double);
double normal_cr(double);
double uniform_random(void);
double erfinv(double);
double normal_random(void);

typedef struct _BIN {
	double * bins; // n + 1
	double * centered_bins; // n
	double * values;
	int nb_bins; // n
	int nb_values;
} BIN;

BIN bin(double *, int, int);
void norm_bin(BIN *);

#endif
