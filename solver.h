/*
	Feito por Thiago Vieira
*/

#ifndef _solver_h
#define _solver_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include "matrix3d.h"
#include "graph.h"
#include "vector.h"
#include "utility.h"

typedef struct td{
	matrix3d *m;
	graph *g;
	vector *tPesos, *tQualidades;
	int i, j, p, w;
} thread_data;

void solve(FILE *foutput, graph *g, vector *tPesos, vector *tQualidades, int d, int v, int wKnapsack);

/* Método que roda o caso base da dp, ou seja, quando d=0 */
void BaseCase(matrix3d *m, vector *tPesos, vector *tQualidades, int v, int w);

void solveKnapsack(matrix3d *m, graph *g, vector *tPesos, vector *tQualidades, int i, int j, int k, int p);

void* solveKnapsackThread(void *input);

#endif
