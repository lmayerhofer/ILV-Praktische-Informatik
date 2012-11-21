#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Anzahl der Elemente einer Matrix
#define N 1000

// Für Matrix(...)
#define SM (CLS / sizeof (double))

int i, j, k, i2, j2, k2;
double res[N][N] __attribute__ ((aligned (64)));
double mul1[N][N] __attribute__ ((aligned (64)));
double mul2[N][N] __attribute__ ((aligned (64)));
double tmp[N][N] __attribute__ ((aligned (64)));
double *restrict rres;
double *restrict rmul1;
double *restrict rmul2;

void matrix1() {
	//Matrix berechnen
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			for (k = 0; k < N; ++k)
      			res[i][j] += mul1[i][k] * mul2[k][j];
}

void matrix2() {
	// Matrix transponieren
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
    		tmp[i][j] = mul2[j][i];

	// Matrix berechnen
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			for (k = 0; k < N; ++k)
				res[i][j] += mul1[i][k] * tmp[j][k];
}

void matrix3() {
	for (i = 0; i < N; i += SM)
		for (j = 0; j < N; j += SM)
			for (k = 0; k < N; k += SM)
				for (i2 = 0, rres = &res[i][j], rmul1 = &mul1[i][k]; i2 < SM; ++i2, rres += N, rmul1 += N)
					for (k2 = 0, rmul2 = &mul2[k][j]; k2 < SM; ++k2, rmul2 += N)
						for (j2 = 0; j2 < SM; ++j2)
							rres[j2] += rmul1[k2] * rmul2[j2];
}

double calcTime(struct timeval time) {
	//return time.tv_sec + (time.tv_usec / 1000000.0); // n seconds
	return (time.tv_sec * 1000000.0) + time.tv_usec;
}

int main() {
	struct timeval t1, t2;
	
	// Matrix mit Zahlen (random bzw. 0) füllen
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			//mul1[i][j] = (double)(rand() % 10) + 1.0;
			//mul2[i][j] = (double)(rand() % 10) + 1.0;
			mul1[i][j] = 0.0;
			mul1[i][j] = 0.0;
			res[i][j] = 0.0;
		}
	}
	
	// normal
	printf("\nNormal:\n");

    gettimeofday(&t1, NULL);
    matrix1();
    gettimeofday(&t2, NULL);

    printf("%.1lf microseconds\n\n", calcTime(t2) - calcTime(t1));

    // transponiert
    printf("Transponiert:\n");

    gettimeofday(&t1, NULL);
    matrix2();
    gettimeofday(&t2, NULL);

    printf("%.1lf microseconds\n\n", calcTime(t2) - calcTime(t1));

    // transponiert
    printf("Transponiert:\n");

    gettimeofday(&t1, NULL);
    matrix3();
    gettimeofday(&t2, NULL);

    printf("%.1lf microseconds\n\n", calcTime(t2) - calcTime(t1));

	return 0;
}