/*
	Feito por Thiago Vieira
*/

#ifndef _pair_h
#define _pair_h

typedef struct{
	int first, second;
} int_pair;

typedef struct{
	void *first, *second;
} void_pair;

typedef struct{
	int first;
	double second;
} intDouble_pair;

/* Função que monta um pair do tipo intDouble_pair */
intDouble_pair make_intDoublePair(int a, double b);

/* Função que monta um pair do tipo int_pair */
int_pair make_intpair(int a, int b);

/* Função que monta um pair do tipo void_pair */
void_pair make_voidpair(void *a, void *b);

#endif
